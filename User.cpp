#include "User.h"

std::string User::getUsername() {

    return userName;

}

int User::getSocketNumber() {

    return socketNumber;
}

void User::setSocketNumber(int socketNumber) {

    this->socketNumber = socketNumber;

}
