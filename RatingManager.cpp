#include "RatingManager.h"
#include <iostream>

#include "RatingManager.h"
#include <iostream>


void RatingManager::rate(int userId, int movieId, double score) {
    if (score < 0.0 || score > 5.0) {
        std::cout << "0~5 사이의 점수를 입력해주세요." << std::endl;
        return;}
    
    ratings.emplace_back(userId, movieId, score);
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