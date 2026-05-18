#pragma once
#include <vector>
#include "MovieManager.h"
#include "RatingManager.h"
#include "UserManager.h"

class Recommender {
private:
    // 여기!!: 원본 데이터를 참조(&)로 들고 있어야 함 [cite: 65, 68]
    MovieManager& movieMgr;
    RatingManager& ratingMgr;
    UserManager&  userMgr;

public:
    Recommender(MovieManager& mm, RatingManager& rm, UserManager& um) : movieMgr(mm), ratingMgr(rm), userMgr(um) {} // 여기!!

    // 여기!!: 핵심 추천 함수 [cite: 281, 521]
    std::vector<int> recommend(int targetUserId, int k = 3, int n = 5);
};