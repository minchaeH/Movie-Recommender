#pragma once
#include <string>
#include <vector>
#include "User.h"
#include "BaseManager.h"

class UserManager : public BaseManager {

    private:
        std::vector<User> users;

    public:
        void addUser(const User& user);
        void printAll() const;
        std::vector<int> getAllUserIds() const; 
        void loadFromFile(const std::string& filename) override;
        void saveToFile(const std::string& filename) override;
        int size() const override { return (int)users.size(); }
};