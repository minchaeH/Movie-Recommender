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
#include <cctype>
#include <cstdlib>

const std::string COLOR_RESET = "\033[0m";   // 원래 색으로
const std::string COLOR_RED = "\033[31m";    // 에러/경고 (빨강)
const std::string COLOR_GREEN = "\033[32m";  // 성공/제목 (초록)
const std::string COLOR_YELLOW = "\033[33m"; // 정보/알림 (노랑)

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

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
    clearScreen();
    std::cout << COLOR_GREEN << "\n🎬 [전체 영화 목록]" << COLOR_RESET << std::endl;
    
    int count = 0;
    for (const auto& movie : movies) {
        std::cout << movie << std::endl;
        count++;
        
        if (count % 10 == 0 && count < movies.size()) {
            std::cout << COLOR_YELLOW << "\n[ " << (count / 10) << " 페이지 ] 다음 페이지를 보려면 아무 문자나 입력 후 Enter를 치세요 (q 누르면 종료): " << COLOR_RESET;
            std::string input;
            std::cin >> input;
            if (input == "q" || input == "Q") {
                clearScreen();
                return; 
            }
            clearScreen(); 
            std::cout << COLOR_GREEN << "\n[전체 영화 목록 - 계속]" << COLOR_RESET << std::endl;
        }
    }
    std::cout << COLOR_GREEN << "\n목록 출력이 완료되었습니다." << COLOR_RESET << std::endl;
}

void MovieManager::searchMovie(const std::string& title) const {
    Timer t("영화 검색");

    clearScreen();
    std::string lowerTitle = title;
    std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);

    bool foundAny = false;
    std::cout << COLOR_GREEN << "\n[" << title << "] 검색 결과..." << COLOR_RESET << std::endl;

    for (const auto& movie : movies) {
        std::string lowerMovieTitle = movie.getTitle();
        std::transform(lowerMovieTitle.begin(), lowerMovieTitle.end(), lowerMovieTitle.begin(), ::tolower);

        if (lowerMovieTitle.find(lowerTitle) != std::string::npos) {      
            std::cout << "🎬 " << movie << std::endl;
            foundAny = true;
        }
    }

    if (foundAny) {
        return; 
    }


    int minDistance = 9999;
    std::string closestTitle = "";
    const Movie* closestMovie = nullptr;

    for (const auto& movie : movies) {

        std::string lowerMovieTitle = movie.getTitle();
        std::transform(lowerMovieTitle.begin(), lowerMovieTitle.end(), lowerMovieTitle.begin(), ::tolower);

        int dist = calculateLevenshteinDistance(lowerTitle, lowerMovieTitle);
        
        if (dist < minDistance) {
            minDistance = dist;
            closestTitle = movie.getTitle();
            closestMovie = &movie;
        }
    }
    if (minDistance <= 3 && closestMovie != nullptr) {
       std::cout << COLOR_RED << "\n정확한 검색 결과가 없습니다." << COLOR_RESET << std::endl;
        std::cout << COLOR_YELLOW << "혹시 [" << closestTitle << "] 을(를) 찾으시나요?" << COLOR_RESET << std::endl;
        std::cout << COLOR_GREEN << "추천 결과: " << *closestMovie << COLOR_RESET << std::endl;
    } else {
        std::cout << COLOR_RED << "검색 결과가 없습니다." << COLOR_RESET << std::endl;
    }
}

void MovieManager::addRating(int movieId, double score) {
    for (auto& movie : movies) {
        if (movie.getId() == movieId) {
            movie.addRating(score);
            return;
        }
    }
    std::cout << COLOR_RED << "해당 ID의 영화가 없습니다." << COLOR_RESET << std::endl;
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
            std::cerr << COLOR_YELLOW << lineNum << "번 줄 건너뜀 (데이터 오류): " << e.what() << COLOR_RESET << std::endl;
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
    clearScreen();
    std::vector<Movie> filtered;
    
    std::copy_if(movies.begin(), movies.end(), std::back_inserter(filtered),
                 [&genre](const Movie& m) { return m.getGenre() == genre; });

    if (filtered.empty()) {
        std::cout << COLOR_RED << genre << " 장르의 영화가 없습니다." << COLOR_RESET << std::endl;
    } else {
        std::cout << COLOR_GREEN << "\n=== [" << genre << "] 장르 영화 목록 ===" << COLOR_RESET << std::endl;
        for (const auto& m : filtered) {
            std::cout << m << std::endl;
        }
    }
}

void MovieManager::printStatistics() const {

    clearScreen();
    if (movies.empty()) {
        std::cout << COLOR_RED << "등록된 영화가 없습니다." << COLOR_RESET << std::endl;
        return;
    }

    // 1. 전체 평균 (for문 안 쓰고 accumulate로 우아하게 합산)
    double totalScore = std::accumulate(movies.begin(), movies.end(), 0.0,
        [](double sum, const Movie& m) { return sum + m.getAverageRating(); });
    double overallAverage = totalScore / movies.size();

    std::cout << COLOR_GREEN << "\n[영화 통계 요약]" << COLOR_RESET << std::endl;
    std::cout << "총 영화 개수: " << movies.size() << "편" << std::endl;
    std::cout << std::fixed << std::setprecision(2); // 소수점 2자리 고정
    std::cout << "전체 평균 평점: " << overallAverage << "점\n" << std::endl;

    // 2. 장르별 평균 (map을 써서 쥰내 쉽게 분류)
    std::map<std::string, std::pair<double, int>> genreStats; // <장르, <총점, 개수>>
    for (const auto& m : movies) {
        genreStats[m.getGenre()].first += m.getAverageRating();
        genreStats[m.getGenre()].second += 1;
    }

    std::cout << COLOR_YELLOW << "[장르별 평균 평점]" << COLOR_RESET << std::endl;
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