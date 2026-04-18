#include "Movie.h"
#include <iostream>

// 기본 생성자
Movie::Movie()
    : id(0), releaseYear(0),
      totalRating(0.0), ratingCount(0), averageRating(0.0) {}

// 4인자 생성자
Movie::Movie(int id, const std::string& title,
             const std::string& genre, int year)
    : id(id), title(title), genre(genre),
      releaseYear(year),
      totalRating(0.0), ratingCount(0), averageRating(0.0) {}

int         Movie::getId()           const { return id; }
std::string Movie::getTitle()        const { return title; }
std::string Movie::getGenre()        const { return genre; }
int         Movie::getReleaseYear()  const { return releaseYear; }
int         Movie::getRatingCount()  const { return ratingCount; }

double Movie::getAverageRating() const {
    if (ratingCount == 0) return 0.0;   // 0 나눗셈 방어
    return averageRating;
}

void Movie::addRating(double score) {
    if (score < 0.0 || score > 5.0) return;    // 유효성 검사
    totalRating += score;
    ratingCount++;
    if (ratingCount > 0)
    averageRating = totalRating / ratingCount;
}

void Movie::display() const {           // 중복 제거 — 하나만 유지
    std::cout << id << ". " << title
              << " (" << releaseYear << ")"
              << "  평점: " << getAverageRating()
              << " (" << ratingCount << "건)"
              << std::endl;
}

//제목 찾기
bool Movie::operator==(const Movie& b) const {
    return title == b.title;  
}

//평점순
bool Movie::operator<(const Movie& other) const {
    return this->averageRating > other.averageRating;
}
// 출력 위해
std::ostream& operator<<(std::ostream& os, const Movie& movie) {
    os << "제목: " << movie.title << " ㅣ 연도: " << movie.releaseYear
       << " ㅣ 평점: " << movie.getAverageRating() << " ㅣ 평가 수: " << movie.ratingCount << "건";
    return os;
}
