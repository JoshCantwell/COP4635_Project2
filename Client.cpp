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
#include <pthread.h>

#define PORT 60000

void *recvMessage(void *p_sock);    
char msg[500];


int main(int argc, char const *argv[])
{
    int sock = 0; long valread;
    struct sockaddr_in serv_addr;
    char* prompt;
    std::string message;
    pthread_t t;

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

    int *pclient = (int*)malloc(sizeof(int));
    *pclient = sock;

    if(pthread_create(&t, NULL, recvMessage, pclient) != 0) {

        perror("pthread_create() error");
        exit(1);
    }

/*
    while(message != "exit") {
   
        message = "";
        prompt;
    
        //char buffer[1024] = {0};
   //     valread = read( sock , buffer, 1024);
        //printf("%s  ",buffer );
       


        if(message != "6"){ 
            std::getline(std::cin, message);
        }
        prompt = const_cast<char*>(message.c_str()); 
        send(sock , prompt , strlen(prompt) , 0 );
    }
  */

    do{
        memset(msg, 0, sizeof(msg));
        if(fgets(msg,500, stdin) > 0) {

            int len = write(sock, msg, strlen(msg)-1);
            if(len < 0) {

                perror("message not sent... ");
                exit(1);

            }
        }

    } while(strcmp(msg,"exit\n") != 0);



    return 0;
}

void *recvMessage(void * p_sock) {

    int sock = *((int*)p_sock);
    free(p_sock);

       
    int len;

    while((len = read(sock, msg, 500 )) > 0) {

        puts(msg);
        memset(msg, 0, 500);

    }

}
