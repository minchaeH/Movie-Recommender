#include "MovieManager.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

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
        if (movie == temp) {      
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

void MovieManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    std::getline(file, line); 

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token, title, genre;
        int id, year;

        std::getline(ss, token, ','); id = std::stoi(token); 
        std::getline(ss, title, ',');
        std::getline(ss, genre, ',');
        std::getline(ss, token, ','); year = std::stoi(token);

        movies.emplace_back(id, title, genre, year);
    }
    file.close();
}

void MovieManager::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    
    file << "id,title,genre,releaseYear\n";
    for (const auto& m : movies) {
        file << m.getId() << "," << m.getTitle() << "," << m.getGenre() << "," << m.getReleaseYear() << "\n";
    }
    file.close();
}

const Movie* MovieManager::findById(int id) const {
    for (const auto& m : movies) {
        if (m.getId() == id) return &m; 
    }
    return nullptr;
}

int MovieManager::size() const { return (int)movies.size(); }