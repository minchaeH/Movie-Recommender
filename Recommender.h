#pragma once
#include <vector>
#include "MovieManager.h"
#include "RatingManager.h"
#include "UserManager.h"

class Recommender {
private:
    MovieManager& movieMgr;
    RatingManager& ratingMgr;
    UserManager&  userMgr;

public:
    Recommender(MovieManager& mm, RatingManager& rm, UserManager& um) : movieMgr(mm), ratingMgr(rm), userMgr(um) {} 

    std::vector<int> recommend(int targetUserId, int k = 3, int n = 5);
};