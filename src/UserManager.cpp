#include "UserManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

void UserManager::addUser(const User& user) {
    users.emplace_back(user);
}

void UserManager::printAll() const {
    for (const auto& user : users) {
        std::cout << user << std::endl;
    }
}

void UserManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("파일을 열 수 없습니다: " + filename);
    }

    std::string line;
    std::getline(file, line); 

    int lineNum = 1;

    while (std::getline(file, line)) {
        lineNum++;
        if (line.empty()) continue;

        try{
            std::stringstream ss(line);
            std::string token, name, email;
            int id;

            std::getline(ss, token, ','); id = std::stoi(token); 
            std::getline(ss, name, ',');
            std::getline(ss, email, ',');

            users.emplace_back(id, name, email);
        }
        catch (const std::exception& e) {
            std::cerr << lineNum << "번 줄 건너뜀 (데이터 오류): " << e.what() << std::endl;
        }
    }
    file.close();
}

void UserManager::saveToFile(const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("저장할 파일을 열 수 없습니다: " + filename);
    }
    
    file << "id,name,email\n"; // [cite: 5805]
    for (const auto& u : users) {
        file << u.getId() << "," << u.getName() << "," << u.getEmail() << "\n";
    }
    file.close();
}

std::vector<int> UserManager::getAllUserIds() const {
    std::vector<int> ids;
    for (const auto& u : users) ids.push_back(u.getId());
    return ids;
}