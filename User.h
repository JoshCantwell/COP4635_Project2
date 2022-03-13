#ifndef _USER_H_
#define _USER_H_

#include <iostream>
#include <vector>
#include <fstream> 

class User {

    public:

        
        bool findUser(std::string userName, std::string password);
        std::string getUsername();
        std::string getLocations();
        std::string getMessagesRecieved();
        int getSocketNumber();
        void setUserName(std::string UserName);
        void setLocations(std::string Location);
        void setMessagesRecieved(std::string MessagesRecieved);
        void setSocketNumber(int SocketNumber);


    private:

        std::string userName;
        std::vector <std::string> locations;
        std::vector <std::string> messagesRecieved;
        int socketNumber;

};


#endif
