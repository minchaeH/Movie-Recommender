#include "UserManager.h"

#include <iostream>

void UserManager::addUser(const User& user) {
    users.emplace_back(user);
}

void UserManager::printAll() const {
    for (const auto& user : users) {
        std::cout << user << std::endl;
    }
}