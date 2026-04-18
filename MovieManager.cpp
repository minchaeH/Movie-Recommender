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
    for (const auto& movie : movies) {
        if (movie.getTitle() == title) {
            std::cout  << movie << std::endl;
            return;
        }
    }
    std::cout << "검색 결과가 없습니다." << std::endl;
}