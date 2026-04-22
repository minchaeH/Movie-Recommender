#include "MovieManager.h"
#include <algorithm>
#include <iostream>

void MovieManager::addMovie(const Movie& movie) {
    movies.emplace_back(movie);
}

void MovieManager::sortByRating() {
    std::sort(movies.begin(), movies.end(), [](const Movie& a, const Movie& b) {
        if (a.getAverageRating() != b.getAverageRating()) {
            return a.getAverageRating() > b.getAverageRating();
        }
        return a.getTitle() < b.getTitle();
    });
}

void MovieManager::printAll() const {
    for (const auto& movie : movies) {
        std::cout << movie << std::endl;
    }
}

void MovieManager::searchMovie(const std::string& title) const {
    Movie temp(0, title, "", 0); 
    for (const auto& movie : movies) {
        if (movie == temp) {       // operator== 사용
            std::cout << movie << std::endl;
            return;
        }
    }
    std::cout << "검색 결과가 없습니다." << std::endl;
}

void MovieManager::addRating(int movieId, double score) {
    for (auto& movie : movies) {
        if (movie.getId() == movieId) {
            movie.addRating(score);
            return;
        }
    }
    std::cout << "해당 ID의 영화가 없습니다." << std::endl;
}