// Created by: Josh Cantwell 02-28-22
// COP4635 - Systems and Networks II
// This C++ file is used for server side of communication


#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <iostream>

#define PORT 8080

void * Handle_Connection(void * new_socket);

int main(int argc, char const *argv[])
{
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
 
    pthread_t t;
    
    void *ret;
    
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }

        std::cout << new_socket << std::endl;
//        Handle_Connection(new_socket);
       int *pclient = (int*)malloc(sizeof(int));
        *pclient = new_socket;
        if(pthread_create(&t, NULL, Handle_Connection, pclient) != 0) {
            perror("pthread_create() error");
            exit(1);
        }


    }


    if(pthread_join(t, &ret) != 0) {
        perror("pthread_create() error");
        exit(3);    
    }

    return 0;
}


void * Handle_Connection(void * p_new_socket) {

       
    int new_socket = *((int*)p_new_socket);
    free(p_new_socket);
    long valread;
    char *hello = "Hello from server";
    char buffer[30000] = {0};
    valread = read( new_socket , buffer, 30000);
    printf("%s\n",buffer );
    write(new_socket , hello , strlen(hello));
    printf("------------------Hello message sent-------------------\n");
    close(new_socket);

    return NULL;


}
