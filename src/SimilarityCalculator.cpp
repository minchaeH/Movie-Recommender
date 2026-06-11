#include "SimilarityCalculator.h"
#include <cstdlib> 

namespace SimConst {
    constexpr int NO_SIMILARITY = -100; // 공통으로 본 영화가 없을 때 반환
    constexpr int COMMON_WEIGHT = 10;   // 공통 영화 1개당 가중치 점수
}

int SimilarityCalculator::calculate(
    const std::vector<Rating>& user1, 
    const std::vector<Rating>& user2) 
{
    int commonCount = 0;   
    int scoreDiffSum = 0;  

    for (const Rating& r1 : user1) {
        for (const Rating& r2 : user2) {
            if (r1.getMovieId() == r2.getMovieId()) {
                commonCount++;
                scoreDiffSum += std::abs(r1.getScore() - r2.getScore());
            }
        }
    }

    if (commonCount == 0) {
        return SimConst::NO_SIMILARITY;
    }

    return (commonCount * SimConst::COMMON_WEIGHT) - scoreDiffSum;
}