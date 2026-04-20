#pragma once
#include <vector>
#include "Rating.h"

class RatingManager {
private:
    std::vector<Rating> ratings;
public:
    void rate(int userId, int movieId, double score);
    void printRating(int movieId) const;

};