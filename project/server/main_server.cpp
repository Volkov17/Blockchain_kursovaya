#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>


int main() {

    char filename[] = "blockchain.txt";

    int listening  = socket(AF_INET , SOCK_STREAM , 0 );
    if ( listening == -1){
        std::cerr<<" we cannt create socket" ;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(50632) ;
    std::string ip_adr = "127.0.0.1";
    inet_pton(AF_INET ,ip_adr.c_str(), &address.sin_addr);

  //  address.sin_addr.s_addr = htonl(INADDR_ANY);
    std::cout << htonl(INADDR_ANY) <<std::endl;
    int a = bind(listening,(sockaddr*)&address, sizeof(address));
    if ( a == -1){
        std::cerr<< "bind filed";

    }
    else { std::cout<< "bind good" <<std::endl; }

    listen(listening,SOMAXCONN);
    if ( listen(listening,SOMAXCONN) == -1){
        std::cerr << "listening failed";
    }

    std::cout << "waiting for client" << std::endl;


    int success = 0;
    sockaddr_in addr_remote;
    unsigned int sin_size ;
    char revbuf[512];
    while(success == 0) {

        sin_size = sizeof(addr_remote);

        /* Wait a connection, and obtain a new socket file despriptor for single connection */
        int nsockfd;
        if ((nsockfd = accept (listening, ( sockaddr *) &addr_remote, &sin_size)) == -1) {
            std::cerr<<" error "<<std::endl;
            exit(1);
        } else
            std::cout<< " Server has got connected from" <<  inet_ntoa(addr_remote.sin_addr)<<std::endl;

        /*Receive File from Client */
        FILE *fr = fopen(filename, "a");
        if (fr == NULL)
            std::cout << "file cannot be open " << filename << std::endl;
        else {
            bzero(revbuf, 512);
            int fr_block_sz = 0;
            while ((fr_block_sz = recv(nsockfd, revbuf, 512, 0)) > 0) {
                int write_sz = fwrite(revbuf, sizeof(char), fr_block_sz, fr);
                if (write_sz < fr_block_sz) {
                    std::cerr << "writing falied " <<std::endl;
                }
                bzero(revbuf, 512);
                if (fr_block_sz == 0 || fr_block_sz != 512) {
                    break;
                }
            }
            if (fr_block_sz < 0) {
                if (errno == EAGAIN) {
                   std::cout<< "recv() timed out." << std::endl;
                } else {
                    std::cerr << "recv() failed" << std::endl;
                    exit(1);
                }
            }
            std::cout<< "recieved from client " <<std::endl;
            fclose(fr);
        }
        success = 1;
        close (listening);
        close (nsockfd);
    }


    //sendfile()

    return 0;
}
