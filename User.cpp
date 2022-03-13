#include "User.h"

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

std::string User::getUsername() {

    return userName;

}

int User::getSocketNumber() {

    return socketNumber;
}

void User::setSocketNumber(int socketNumber) {

    this->socketNumber = socketNumber;

}
