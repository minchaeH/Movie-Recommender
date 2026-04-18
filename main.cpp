#include <iostream>
#include <vector>
#include <string>
#include "Movie.h"
#include "User.h"
#include "Rating.h"

int main() {
    
    MovieManager manager;

    movies.emplace_back(0, "해리포터", "판타지", 2010);
    movies.emplace_back(1, "왕과 사는 남자", "드라마", 2013);
    movies.emplace_back(2, "업", "애니메이션", 2019);

    User u1(1, "Minchae", "minchae@soongsil.ac.kr");
    User u2(2, "Luka", "luka@soongsil.ac.kr");
    
    Rating r1(u1.getId(), movies[0].getId(), 4.5);
    Rating r2(u2.getId(), movies[1].getId(), 3.0);
    Rating r3(u1.getId(), movies[2].getId(), 6.0);

    movies[0].addRating(r1.getScore());
    movies[1].addRating(r2.getScore());
    movies[2].addRating(r3.getScore());

    std::cout << "=== 유저 목록 ===" << std::endl;
    u1.display();
    u2.display();

    std::cout << "=== 영화 목록 ===" << std::endl;
    movies[0].display();
    movies[1].display();
    movies[2].display();

    std::cout << "=== 별점 목록 ===" << std::endl;
    r1.display();
    r2.display();
    r3.display();



    return 0;
}