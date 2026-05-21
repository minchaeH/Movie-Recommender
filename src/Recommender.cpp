#include "Recommender.h"
#include "SimilarityCalculator.h"
#include <algorithm>
#include <map>
#include <set>
#include <iostream>

std::vector<int> Recommender::recommend(int targetUserId, int k, int n) {
    auto myRatings = ratingMgr.findByUser(targetUserId);
    if (myRatings.empty()) return {}; 

    std::set<int> myMovieIds;
    for (const auto& r : myRatings) myMovieIds.insert(r.getMovieId());

    std::vector<std::pair<int, int>> similarities;
    for (int otherId : userMgr.getAllUserIds()) { 
        if (otherId == targetUserId) continue;
        int sim = SimilarityCalculator::calculate(myRatings, ratingMgr.findByUser(otherId));
        if (sim != -100) similarities.push_back({otherId, sim});
    }
    std::sort(similarities.begin(), similarities.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; 
    });

    std::map<int, double> movieScores;
    int count = 0;
    for (const auto& p : similarities) {
        if (++count > k) break;
        for (const auto& r : ratingMgr.findByUser(p.first)) {
            if (myMovieIds.find(r.getMovieId()) == myMovieIds.end()) {
                movieScores[r.getMovieId()] += r.getScore();
            }
        }
    }

    std::vector<std::pair<int, double>> results(movieScores.begin(), movieScores.end());
    std::sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    std::vector<int> finalRec;
    for (int i = 0; i < n && i < (int)results.size(); ++i) finalRec.push_back(results[i].first);
    return finalRec;

}