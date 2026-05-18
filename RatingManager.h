#pragma once
#include <vector>
#include "Rating.h"
#include <string>
#include "BaseManager.h"

class RatingManager : public BaseManager{
private:
    std::vector<Rating> ratings;
public:
    void rate(int userId, int movieId, double score);
    void printRating(int movieId) const;
    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) override;
    int size() const override { return (int)ratings.size(); }
    std::vector<Rating> findByUser(int userId) const;
};