#include <iostream>
#include <ctime>
#include <vector>

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>
#include <sys/stat.h>

#include "trusted_comp.h"
#include "Block.h"
#include "Blockchain.h"


void connect_with_server (const char * filename){
      int sock = socket(AF_INET, SOCK_STREAM, 0);
      if (sock == -1) {
            std::cerr<< "creation socket failed" <<std::endl;
            return void();
      }

      int port = 50632;
      std::string ipAddress = "127.0.0.1";

      sockaddr_in sin;
      sin.sin_family = AF_INET;
      sin.sin_port = htons(port);
      inet_pton(AF_INET, ipAddress.c_str(), &sin.sin_addr);

      //	Connect to the server on the socket
      int connectRes = connect(sock, (sockaddr*)&sin, sizeof(sin));
      if (connectRes == -1)
      {
            std::cerr<< "connection failed" <<std::endl;
            return void();
      }
      else {
            std::cout << "coonsection to port : "<< port << std::endl;
      }

      if(!fork()) {
            char sdbuf[512];
            std::cout<<" Sending  to the Server."<<std::endl;
            FILE *fs = fopen(filename, "r");
            bzero(sdbuf, 512);
            int fs_block_sz;
            while ((fs_block_sz = fread(sdbuf, sizeof(char), 512, fs)) > 0) {
                  if (send(sock, sdbuf, fs_block_sz, 0) < 0) {
                        std::cout<< "failed to dens file" << std::endl;
                        break;
                  }
                  bzero(sdbuf, 512);
            }
            fclose ( fs);
            std::cout<< "was sent " << std::endl;
      }
      close(sock);
}

int main() {

      Blockchain volkovCoin(0); //создаем монету и генерим гениз блок

      volkovCoin.get_latest_block().print_trans();
      std::cout << std::endl;
      volkovCoin.print_chain();

      transaction tr1 = {1 , "olya" , "masha"};
      std::vector < transaction > arr;
      arr.push_back(tr1);

      std::cout << std::endl;

      volkovCoin.adding_new_block(arr);

      volkovCoin.get_latest_block().print_trans();
      std::cout << std::endl;
      volkovCoin.print_chain();


      const char * filename1 = volkovCoin.chain_to_file();

      //connect_with_server(filename1);


      transaction tr3 = {4 , "pasha" , "dima"};
      transaction tr2 = {2 , "olya" , "nikita"};
      std::vector < transaction > arr1;
      arr1.push_back(tr2);
      arr1.push_back(tr3);

      volkovCoin.adding_new_block(arr1);

      transaction tr4 = {3 , "gena" , "kate"};
      transaction tr5 = {6 , "alina" , "sonya"};
      transaction tr6 = {10 , "gudgf" , "regeg"};
      std::vector < transaction > arr2;
      arr2.push_back(tr4);
      arr2.push_back(tr5);
      arr2.push_back (tr6);

      volkovCoin.adding_new_block(arr2);

      std::cout << std::endl;
      volkovCoin.print_chain();

      if (volkovCoin.valid_chain()){
             std::cout << " valid" << std::endl ;
      }
      else {
            std::cout << " unvalid" << std::endl;
      }

      volkovCoin.checking_signature();

//      if (volkovCoin.checking_signature()){
//          std::cout << " valid" << std::endl ;
//      }
//      else {
//          std::cout << " unvalid" << std::endl;
//      }


      Block hackBlock = volkovCoin.get_latest_block();

      std::vector <transaction> hackArr;
      transaction hacktr = {10 , "grfv" , "drg"};
      hackArr.push_back(hacktr);
    return 0;
}
