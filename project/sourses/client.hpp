#ifndef BLOCKCHAIN_KURS_CLIENT_H
#define BLOCKCHAIN_KURS_CLIENT_H

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

#include <iostream>

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

#endif //BLOCKCHAIN_KURS_CLIENT_H
