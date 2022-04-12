#ifndef _USER_H_
#define _USER_H_

#include <iostream>
#include <vector>
#include <fstream> 
#include <string>

class User {

    public:



        bool findUser(std::string userName, std::string password);
        bool checkUserName(std::string username);
        bool findLocation(std::string location);
        bool getInLocation();
        bool subscribedToLocations();

        std::string getUsername();
        std::string getMessagesRecieved();
        std::string subscribedLocations();
        std::string streamMessage(std::string message);

        int getSocketNumber();
        
        void setInLocation(bool inLocation);
        void changePassword(std::string username, std::string password);
        void setUserName(std::string UserName);
        void setLocations(std::string Location);
        void setMessagesRecieved(std::string MessagesRecieved);
        void setSocketNumber(int SocketNumber);
        void subscribeToLocation(std::string location);
        void unsubscribeToLocation(std::string location);
        void registerUser(std::string username, std::string password);

    private:

        bool inLocation;
        std::string userName;
        std::vector <std::string> locations;
        std::vector <std::string> messagesRecieved;
        int socketNumber;

};


#endif
