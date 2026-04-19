#pragma once
#include <string>
#include <vector>
#include "User.h"

class UserManager {

    private:
        std::vector<User> users;

    public:

        void addUser(const User& user);
        void printAll() const;

};