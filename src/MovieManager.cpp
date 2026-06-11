#include "MovieManager.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Timer.h"
#include <numeric>  
#include <map>      
#include <iomanip>

void MovieManager::addMovie(const Movie& movie) {
    movies.emplace_back(movie);
}

void MovieManager::sortByRating() {
    Timer timer("sortByRating");

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
    Timer t("영화 검색");

    Movie temp(0, title, "", 0); 
    for (const auto& movie : movies) {
        if (movie == temp) {      
            std::cout << movie << std::endl;
            return;
        }
    }
    int minDistance = 9999;
    std::string closestTitle = "";
    const Movie* closestMovie = nullptr;

    for (const auto& movie : movies) {
        int dist = calculateLevenshteinDistance(title, movie.getTitle());
        if (dist < minDistance) {
            minDistance = dist;
            closestTitle = movie.getTitle();
            closestMovie = &movie;
        }
    }
    if (minDistance <= 3 && closestMovie != nullptr) {
        std::cout << "\n정확한 검색 결과가 없습니다." << std::endl;
        std::cout << "혹시 [" << closestTitle << "] 을(를) 찾으시나요?" << std::endl;
        std::cout << "추천 결과: " << *closestMovie << std::endl;
    } else {
        std::cout << "검색 결과가 없습니다." << std::endl;
    }
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
    if (!file.is_open()) {
        throw std::runtime_error("파일을 열 수 없습니다: " + filename); 
    }

    std::string line;
    std::getline(file, line); 

    int lineNum = 1;

    while (std::getline(file, line)) {
        lineNum++;
        try {
        std::stringstream ss(line);
        std::string token, title, genre;
        int id, year;

        std::getline(ss, token, ','); id = std::stoi(token); 
        std::getline(ss, title, ',');
        std::getline(ss, genre, ',');
        std::getline(ss, token, ','); year = std::stoi(token);

        movies.emplace_back(id, title, genre, year);
    }
        catch (const std::exception& e) {
            std::cerr << lineNum << "번 줄 건너뜀 (데이터 오류): " << e.what() << std::endl;
        }
    }
    file.close();
}

void MovieManager::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("저장할 파일을 열 수 없습니다 (권한 문제 등): " + filename);
    }

    
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

void MovieManager::filterByGenre(const std::string& genre) const {
    std::vector<Movie> filtered;
    
    // for-if문 안 쓴다! 모던 C++ 스타일로 조건에 맞는 놈만 복사!
    std::copy_if(movies.begin(), movies.end(), std::back_inserter(filtered),
                 [&genre](const Movie& m) { return m.getGenre() == genre; });

    if (filtered.empty()) {
        std::cout << genre << " 장르의 영화가 없습니다." << std::endl;
    } else {
        std::cout << "\n=== [" << genre << "] 장르 영화 목록 ===" << std::endl;
        for (const auto& m : filtered) {
            std::cout << m << std::endl;
        }
    }
}

void MovieManager::printStatistics() const {
    if (movies.empty()) {
        std::cout << "등록된 영화가 없습니다." << std::endl;
        return;
    }

    // 1. 전체 평균 (for문 안 쓰고 accumulate로 우아하게 합산)
    double totalScore = std::accumulate(movies.begin(), movies.end(), 0.0,
        [](double sum, const Movie& m) { return sum + m.getAverageRating(); });
    double overallAverage = totalScore / movies.size();

    std::cout << "\n[영화 통계 요약]" << std::endl;
    std::cout << "총 영화 개수: " << movies.size() << "편" << std::endl;
    std::cout << std::fixed << std::setprecision(2); // 소수점 2자리 고정
    std::cout << "전체 평균 평점: " << overallAverage << "점\n" << std::endl;

    // 2. 장르별 평균 (map을 써서 쥰내 쉽게 분류)
    std::map<std::string, std::pair<double, int>> genreStats; // <장르, <총점, 개수>>
    for (const auto& m : movies) {
        genreStats[m.getGenre()].first += m.getAverageRating();
        genreStats[m.getGenre()].second += 1;
    }

    std::cout << "[장르별 평균 평점]" << std::endl;
    for (const auto& pair : genreStats) {
        std::cout << "- " << pair.first << ": " << (pair.second.first / pair.second.second) 
                  << "점 (" << pair.second.second << "편)" << std::endl;
    }
}

    int MovieManager::calculateLevenshteinDistance(const std::string& s1, const std::string& s2) const {
    const std::size_t len1 = s1.size(), len2 = s2.size();
    std::vector<std::vector<int>> d(len1 + 1, std::vector<int>(len2 + 1));

    for (int i = 0; i <= (int)len1; ++i) d[i][0] = i;
    for (int i = 0; i <= (int)len2; ++i) d[0][i] = i;

    for (int i = 1; i <= (int)len1; ++i) {
        for (int j = 1; j <= (int)len2; ++j) {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            d[i][j] = std::min({d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + cost});
        }
    }
    return d[len1][len2];
}