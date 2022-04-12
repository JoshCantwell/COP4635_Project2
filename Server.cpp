// Created by: Josh Cantwell 02-28-22
// COP4635 - Systems and Networks II
// This C++ file is used for server side of communication


#include "User.cpp"
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <iostream>
#include <vector>

#define PORT 60000


// Functions used throughout the code
void * Handle_Connection(void * new_socket);
void UserLogin();
void UserRegister();
void LogUserOut(std::string userName);
std::string OnlineUsers();
std::string MessageToLocation(std::string location);
// Users logged in
std::vector <User*> users;    
std::vector <User*> usersInLocation;



int main(int argc, char const *argv[])
{
    // Variables for TCP socket creation
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
 
    // Variables for multithreading
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
    std::cout << "bind done" << std::endl;
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    std::cout << "Waiting for incoming connections..." << std::endl; 
    while(1)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        std::cout << "Connection accepted\nHandler assigned" << std::endl;

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

    User *user = new User();    
    int new_socket = *((int*)p_new_socket);
    free(p_new_socket);
    long valread;
    char *LoginRegisterPrompt = "Welcome!\n  Press 1 to login\n  Press 2 to register\n  Type 'exit' to Quit\n\n";
    char *UserSelectionPrompt = "\n  Select an option\n  1 Subscribe to a location\n  2 Unsubscribe from a location\n  3 Send message to a location\n  4 Send a private message\n  5 See all the locations you are subscribed to\n  6 See all online users\n  7 See last 10 messages\n  8 Change password\n  Type 'exit' to quit\n";

    bool loggedIn = false;
    user->setSocketNumber(new_socket);
    std::string stringBuffer;
    std::string username, password;
    std::string location;

    std::string locations;

    while(stringBuffer != "exit") {

    
        char buffer[30000] = {0}; 

        if(loggedIn == false) {
        
        
            stringBuffer = "";

            write(new_socket , LoginRegisterPrompt , strlen(LoginRegisterPrompt));
            valread = read( new_socket , buffer, 30000);
            stringBuffer = buffer;

       
            if(stringBuffer == "1"){
                write(new_socket, "  Username:", 12);
                valread = read(new_socket, buffer, 30000);
                username = buffer;
                write(new_socket, "  Password:", 13);
                valread = read(new_socket, buffer, 30000);
                password = buffer;


                if(user->findUser(username, password) == true){                
                    user->setUserName(username);
                    users.push_back(user);
                    loggedIn = true;
                } else {
        
                    write(new_socket, "\n  Invalid username or password\n", 32);
                }

            } else if(stringBuffer == "2") {
                write(new_socket, "  Username:", 12);
                valread = read(new_socket, buffer, 30000);
                username = buffer;
                write(new_socket, "  Password:", 13);
                valread = read(new_socket, buffer, 30000);
                password = buffer;

                
                if(user->checkUserName(username) == true) {

                    write(new_socket, "\nUsername already taken!\n", 24);
            
                } else {

                    user->registerUser(username, password);
                    write(new_socket, "\nUser registered!\n", 18);
                }
            
        
            }
        }else if (loggedIn == true) {

            write(new_socket , UserSelectionPrompt , strlen(UserSelectionPrompt));
            valread = read( new_socket , buffer, 30000);
            stringBuffer = buffer;

            if(stringBuffer == "1") {

                write(new_socket, "  Select a location to subscribe to:\n", 37);
                valread = read(new_socket, buffer, 30000);
                location = buffer;
                user->subscribeToLocation(location);

            } else if(stringBuffer == "2") {

                write(new_socket, "  Select a location to unsubscribe from:\n", 43);
                valread = read(new_socket, buffer, 30000);
                location = buffer;
                user->unsubscribeToLocation(location);
                
            } else if(stringBuffer == "3") {

                    

                std::string message;
                std::string chosenLocation;    
                std::string chooseLocation = "  Select location you'd like to choose\n";

                if(user->subscribedToLocations() == true) {
                
                
                    chooseLocation = chooseLocation + user->subscribedLocations();
                    char* chooseLocationC =  const_cast<char*>(chooseLocation.c_str());
                    write(new_socket, chooseLocationC, strlen(chooseLocationC));
                    valread = read( new_socket, buffer, 30000);
                    chosenLocation = buffer;
                    MessageToLocation(chosenLocation);

                    chooseLocation = "Please type the message you'd like to send: \n";
                    chooseLocationC = const_cast<char*>(chooseLocation.c_str());
                    write(new_socket, chooseLocationC, strlen(chooseLocationC));
                    valread = read( new_socket, buffer, 30000);
                    message = buffer;
                    char* messageC = const_cast<char*>(message.c_str());
                    for(int i=0; i<usersInLocation.size(); i++) {


                  
                        write(usersInLocation.at(i)->getSocketNumber(), messageC, strlen(messageC));

                    }


                } else {

                    chosenLocation = "Must be subscribed to atleast one location to do this, Subscribe to a location and try again.";
                    char* chosenLocationC =  const_cast<char*>(chosenLocation.c_str());
                    write(new_socket, chosenLocationC, strlen(chosenLocationC));

                }

            }else if(stringBuffer == "5") {

                
                std::string subbedLocations  = user->subscribedLocations();
                char* subbedLocationsChar = const_cast<char*>(subbedLocations.c_str());
                write(new_socket, subbedLocationsChar, strlen(subbedLocationsChar));

            } else if(stringBuffer == "6") {
       
                std::string usersOnline;
                usersOnline = usersOnline + "  All online users:\n";
                usersOnline = usersOnline + OnlineUsers();
                char* usersOnlineC = const_cast<char*>(usersOnline.c_str());
                write(new_socket, usersOnlineC, strlen(usersOnlineC));

            }else if(stringBuffer == "8") {

                username = user->getUsername();
                write(new_socket, "\n  Select new password:\n", 23);
                valread = read(new_socket, buffer, 30000);
                password = buffer;
                user->changePassword(username, password);

                rename("temp.txt", "Users.txt");

    
            } // Testing
            else if (stringBuffer == "d") {

                std::cout << OnlineUsers() << std::endl; 
            }


        }

        if(stringBuffer == "exit") {

            LogUserOut(user->getUsername());
        }

    }

    close(new_socket);
       
    std::cout << "Client disconnected" << std::endl;
    return NULL;


}

void LogUserOut(std::string userName){

    for(int i=0; i < users.size();i++) {

        if(users.at(i)->getUsername() == userName) {
               
            users.erase(users.begin() + i);
        }

    }

}

std::string OnlineUsers() {

    std::string Users;

    for(int i=0; i <users.size();i++) {

        Users = Users + std::to_string(i+1) + ".) ";  
        Users = Users +  users.at(i)->getUsername();
        Users = Users + "\n";
    }

    return Users;

}

std::string MessageToLocation(std::string location) {
    

    for(int i=0; i<users.size();i++) {

        if(users.at(i)->findLocation(location) == true) {

            usersInLocation.push_back(users.at(i));
        }
        

    }

    std::cout << usersInLocation.size() << std::endl;
}











