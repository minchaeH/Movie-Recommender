#include "SimilarityCalculator.h"
#include <cstdlib> 

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
        return -100;
    }

    return (commonCount * 10) - scoreDiffSum;
}