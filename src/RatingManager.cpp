#include "RatingManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

void RatingManager::rate(int userId, int movieId, double score) {
    if (score < 0.0 || score > 5.0) {
        std::cout << "0~5 사이의 점수를 입력해주세요." << std::endl;
        return;}
    
    ratings.emplace_back(userId, movieId, score);
}

std::vector<Rating> RatingManager::findByUser(int userId) const {
    std::vector<Rating> userRatings;
    for (const auto& r : ratings) {
        if (r.getUserId() == userId) {
            userRatings.push_back(r);
        }
    }
    return userRatings;
}

void RatingManager::printRating(int movieId) const {
    std::cout << "< 영화 ID: " << movieId << " 의 전체 평점 목록 >" << std::endl;
    bool tf = false;

    for (const auto& r : ratings) {
        if (r.getMovieId() == movieId) {
            r.display();
            tf = true;
        }
    }

    if (!tf) {
        std::cout << "해당 영화에 대한 평점이 없습니다. " << std::endl;
    }
}

void RatingManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    std::getline(file, line); 

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string token;
        int uId, mId;
        double score;

        std::getline(ss, token, ','); uId = std::stoi(token);
        std::getline(ss, token, ','); mId = std::stoi(token);
        std::getline(ss, token, ','); score = std::stod(token); 

        ratings.emplace_back(uId, mId, score);
    }
    file.close();
}

void RatingManager::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    file << "userId,movieId,score\n";
    for (const auto& r : ratings) {
        file << r.getUserId() << "," << r.getMovieId() << "," << r.getScore() << "\n";
    }
    file.close();
}