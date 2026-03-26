#include "Rating.h"
#include <iostream>

Rating::Rating() : userId(0), movieId(0), score(0) {}
Rating::Rating(int userId, int movieId, double score)
    : userId(userId), movieId(movieId), score(score) {}


int Rating::getUserId() const { return userId; }
int Rating::getMovieId() const { return movieId; }

double Rating::getScore() const { 
    if (score < 0.0 || score > 5.0) {
        return 0.0;
    }
    return score; 
}

void Rating::display() const {
    std::cout << "User ID: " << userId << ", Movie ID: " << movieId << ", Score: ";
    if (score < 0.0 || score > 5.0) {
        std::cout << 0.0; } 
    else {
        std::cout << score; }
    std::cout << std::endl;
    
}

