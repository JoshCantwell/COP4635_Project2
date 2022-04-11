// Created by: Josh Cantwell 02-28-22
// cop4635 - Systems and Networks II
// This C++ file is made for Client side communication

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>

#define PORT 60000

int main(int argc, char const *argv[])
{
    int sock = 0; long valread;
    struct sockaddr_in serv_addr;
    char* prompt;
    std::string message;
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
    
    memset(&serv_addr, '0', sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    while(message != "exit") {
   
        message = "";
        prompt = "";
    
        char buffer[1024] = {0};
        valread = read( sock , buffer, 1024);
        printf("%s  ",buffer );
       


        if(message != "6"){ 
            std::getline(std::cin, message);
        }
        prompt = const_cast<char*>(message.c_str()); 
        send(sock , prompt , strlen(prompt) , 0 );
    }
    
    return 0;
}
