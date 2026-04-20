#include "User.h"
#include <iostream>

User::User() :id(0), name(""), email(""){}
User::User(int id, const std::string& name, const std::string& email) 
    : id(id), name(name), email(email){}

int User::getId() const {return id;}
std::string User::getName() const {return name;}
std::string User::getEmail() const {return email;}

void User::display() const {
    std::cout << "ID: " << id << ", Name: " << name << ", Email: " << email << std::endl;
}

bool User::operator==(const User& other) const {
    return name == other.name;  
}

std::ostream& operator<<(std::ostream& os, const User& user) {
    os << "ID: " << user.getId() << " ㅣ 이름: " << user.getName() << " ㅣ 이메일: " << user.getEmail();
    return os;
}