// Created by: Josh Cantwell 02-28-22
// COP4635 - Systems and Networks II
// This C++ file is used to aid the server for keep track of users in the program



#include "User.h"

void User::setLastMessages(std::string message) {

    if(LastTenMessages.size() < 10) {

        LastTenMessages.push_back(message);

    } else {

        LastTenMessages.push_back(message);
        for(int i=1;i<LastTenMessages.size();i++){

            LastTenMessages.at(i-1) = LastTenMessages.at(i);
        }
       

    }


}

void User::changePassword(std::string username, std::string password) {

                
    std::ifstream userFileOut;
    std::ofstream userFileIn;
    std::string user;
    std::string pass;

    userFileOut.open("Users.txt");
    userFileIn.open("temp.txt");


    if(!userFileOut){
        std::cerr;
        exit(1);
    }

    if(!userFileIn){
        std::cerr;
        exit(1);
    }

    while(!userFileOut.eof()) {
        
        userFileOut >> user;    
        userFileOut >> pass;

        if(user != username){
            if(userFileOut.eof()) break;
            userFileIn << user << " " << pass << std::endl;
        }  
        
    }

    userFileIn << username << " " << password << std::endl;

    userFileOut.close();
    userFileIn.close();



}

std::string User::getLastMessages(){

    std::string lastTen = "  Last ten messages:\n";
    for(int i=0; i<LastTenMessages.size(); i++) {

        lastTen = lastTen + "\n";
        lastTen = lastTen + LastTenMessages.at(i);

    }

    return lastTen;

}

std::string User::streamMessage(std::string message) {

    std::cout << message << "\n" << std::endl;


}

std::string User::subscribedLocations() {

    std::string location;
    location = "\n  Locations subscribed to:\n";

    for(int i = 0; i < locations.size(); i++) {
        location = location + std::to_string(i+1);
        location = location + ".) ";
        location = location + locations.at(i);
        location = location + "\n";
    }

    return location;
}

void User::subscribeToLocation(std::string location) {
    locations.push_back(location);
}

void User::unsubscribeToLocation(std::string location) {

    for(int i = 0; i < locations.size(); i++) {
        if(locations.at(i) == location) {
            locations.erase(locations.begin() + i);
        }
    }

}

void User::registerUser(std::string username, std::string password) {

    std::ofstream userFile;
    
    userFile.open("Users.txt", std::ios_base::app);

    if(!userFile){
        std::cerr;
        exit(1);
    }

    userFile << username << " "<< password << std::endl;;

}

bool User::checkUserName(std::string username) {

    std::ifstream userFile;
    std::string user;
    std::string pass;

    userFile.open("Users.txt");

    if(!userFile){
        std::cerr;
        exit(1);
    }

    while(!userFile.eof()) {
        
        userFile >> user;
              
        userFile >> pass;

        if(user == username){
            return true;
        }
    
    }

    userFile.close();

    return false;

}

bool User::findLocation(std::string location) {

    for(int i=0;i<locations.size();i++){

        if(locations.at(i) == location) {

            return true;
        }
    }

}

bool User::getInLocation(){

    return inLocation;

}

bool User::findUser(std::string Username, std::string password){

    std::ifstream userFile;
    std::string user;
    std::string pass;

    userFile.open("Users.txt");

    if(!userFile){
        std::cerr;
        exit(1);
    }
   

    while(!userFile.eof()) {
        
        userFile >> user;
              
        userFile >> pass;

        if(user == Username && pass == password){
            return true;
        }
    
    }

    userFile.close();

    return false;
}

bool User::subscribedToLocations() {


    if(locations.size() == 0) {

        return false;

    } else {

        return true;

    }

}

void User::setInLocation(bool inLocation) {

    this->inLocation = inLocation;

}

void User::setUserName(std::string username) {

    this->userName = username;
}

std::string User::getUsername() {

    return userName;

}

int User::getSocketNumber() {

    return socketNumber;
}

void User::setSocketNumber(int socketNumber) {

    this->socketNumber = socketNumber;

}

