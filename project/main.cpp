#include <iostream>
#include <fstream>
#include <vector>

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <sstream>
#include <arpa/inet.h>


#include "sourses/trusted_comp.hpp"
#include "sourses/Block.hpp"
#include "sourses/Blockchain.hpp"





std::vector <transaction> from_file_to_struct_trans (const char * filename_serv ){
    std::ifstream in(filename_serv);

    std::string amount_s, sender, recipient;
    double amount;
    std::vector <transaction> arr;

    if ( in.is_open()){
        std::getline(in, amount_s, ' ');
        std::getline(in, sender, ' ');
        std::getline(in, recipient, ' ');
    }

    amount = std::stod(amount_s);
    transaction tr = {amount , sender , recipient};
    arr.push_back(tr);
    return arr;
}


int main() {

    std::cout << " if you wanna closes server please write 1 after (transaction added) " << std::endl;


    Blockchain volkovCoin(0);

    char filename[] = "blockchain_trans_server.txt";


    int listening  = socket(AF_INET, SOCK_STREAM, 0 ); // создание сокета
    if ( listening == -1){
        std::cerr << " we cannt create socket";
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(50632);
    std::string ip_adr = "127.0.0.1";
    inet_pton(AF_INET, ip_adr.c_str(), &address.sin_addr); //ip_adr в AF_INET а это в  &address.sin_addr

    int a = bind(listening,(sockaddr*)&address,sizeof(address));

    //int a = bind(listening, (sockaddr*)&address, sizeof(address));// присоединение сокета к адресу и порту
    if ( a == -1){
        std::cerr << "bind filed";
    }
    else {
        std::cout << "bind good" << std::endl;
    }

    listen(listening, SOMAXCONN); // создаем очередь для соединений
    if ( listen(listening, SOMAXCONN) == -1){
        std::cerr << "listening failed";
    }

    std::cout << "waiting for client" << std::endl;

    int success = 0;
    sockaddr_in addr_remote;
    int sin_size;
    char revbuf[512];

    while (success == 0) {

        unsigned int sin_size = sizeof(addr_remote);
        int nsockfd;
        if ((nsockfd = accept(listening, (sockaddr *) &addr_remote, &sin_size)) == -1) { // принятие соеденений
            std::cerr << " error " << std::endl;
            exit(1);
        } else
            std::cout << "server has got connected from " << inet_ntoa(addr_remote.sin_addr) << std::endl;

        //получение файла от клиента

        FILE *fr = fopen(filename, "a");
        if (fr == NULL)
            std::cout << "file cannot be open " << filename << std::endl;
        else {
            bzero(revbuf, 512);
            int fr_block_sz = 0;
            while ((fr_block_sz = recv(nsockfd, revbuf, 512, 0)) > 0) { // чтение данных , которые отправил клиент
                int write_sz = fwrite(revbuf, sizeof(char), fr_block_sz, fr); //запись в найш файл фр
                if (write_sz < fr_block_sz) {
                    std::cerr << "writing falied " << std::endl;
                }
                bzero(revbuf, 512);
                if (fr_block_sz == 0 || fr_block_sz != 512) {
                    break;
                }
            }
            if (fr_block_sz < 0) {
                if (errno == EAGAIN) {
                    std::cout << "recv() timed out." << std::endl;
                } else {
                    std::cerr << "recv() failed" << std::endl;
                    exit(1);
                }
            }
            std::cout << "recieved from client " << std::endl;
            fclose(fr);
            std::vector <transaction> arr = from_file_to_struct_trans(filename);
            remove(filename);
            volkovCoin.adding_new_block(arr);
            sleep(1);
        }
        std:: cin >> success;

        if (success == 1) {
            close(listening);
            close(nsockfd);
        }
    }


    volkovCoin.chain_to_file();

    if (volkovCoin.valid_chain()){
             std::cout << " chain is valid" << std::endl ;
    }
    else {
        std::cout << " unvalid" << std::endl;
    }

    volkovCoin.checking_signature();

    if (volkovCoin.checking_signature()){
        std::cout << " signarures are valid" << std::endl ;
    }
    else {
        std::cout << " unvalid" << std::endl;
    }
    return 0;
}


// int main() {

//       Blockchain volkovCoin(0); //создаем монету и генерим гениз блок

//       volkovCoin.get_latest_block().print_trans();
//       std::cout << std::endl;
//       volkovCoin.print_chain();

//       transaction tr1 = {1 , "olya" , "masha"};
//       std::vector < transaction > arr;
//       arr.push_back(tr1);

//       std::cout << std::endl;

//       volkovCoin.adding_new_block(arr);

//       volkovCoin.get_latest_block().print_trans();
//       std::cout << std::endl;
//       volkovCoin.print_chain();


//       const char * filename1 = volkovCoin.chain_to_file();

     


//       transaction tr3 = {4 , "pasha" , "dima"};
//       transaction tr2 = {2 , "olya" , "nikita"};
//       std::vector < transaction > arr1;
//       arr1.push_back(tr2);
//       arr1.push_back(tr3);

//       volkovCoin.adding_new_block(arr1);

//       transaction tr4 = {3 , "gena" , "kate"};
//       transaction tr5 = {6 , "alina" , "sonya"};
//       transaction tr6 = {10 , "gudgf" , "regeg"};
//       std::vector < transaction > arr2;
//       arr2.push_back(tr4);
//       arr2.push_back(tr5);
//       arr2.push_back (tr6);

//       volkovCoin.adding_new_block(arr2);

//       std::cout << std::endl;
//       volkovCoin.print_chain();

//       if (volkovCoin.valid_chain()){
//              std::cout << " valid" << std::endl ;
//       }
//       else {
//             std::cout << " unvalid" << std::endl;
//       }

//       volkovCoin.checking_signature();
      
//       connect_with_server(filename1);

//      if (volkovCoin.checking_signature()){
//          std::cout << " valid" << std::endl ;
//      }
//      else {
//          std::cout << " unvalid" << std::endl;
//      }


//       Block hackBlock = volkovCoin.get_latest_block();

//       std::vector <transaction> hackArr;
//       transaction hacktr = {10 , "grfv" , "drg"};
//       hackArr.push_back(hacktr);
//     return 0;
// }
