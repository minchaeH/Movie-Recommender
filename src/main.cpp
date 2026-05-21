#include <iostream>
#include <vector>
#include <string>
#include "Movie.h"
#include "User.h"
#include "Rating.h"
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "SimilarityCalculator.h"
#include "Recommender.h"

int main() {
    
    MovieManager movieM;
    UserManager userM;
    RatingManager ratingM;

    movieM.loadFromFile("data/movies.csv");
    userM.loadFromFile("data/users.csv");
    ratingM.loadFromFile("data/ratings.csv");

    for (int uid : userM.getAllUserIds()) {
        for (const auto& r : ratingM.findByUser(uid)) {
            movieM.addRating(r.getMovieId(), r.getScore());
            }
    }

    int select;
    
    while(true) {
        
        std::cout << "\n0~10 사이의 숫자를 입력해주세요.\n" << std::endl;
        std::cout << "0: 종료,\n1: 영화 추가\n2: 영화 제목으로 검색\n";
        std::cout << "3: 영화 전체 출력\n4: 영화 평점순 출력\n5: 사용자 추가\n";
        std::cout << "6: 사용자 목록 출력\n7: 평점 입력\n8: 영화별 전체 평점 조회\n9: 사용자별 유사도 조회\n10: 영화 추천 받기 (M3 핵심!)" << std::endl;
        std::cin >> select;

        if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1000, '\n'); 
        std::cout << "잘못된 입력입니다." << std::endl;
        continue;
    }

        switch(select) {
            case 0: {
                std::cout << "프로그램을 종료합니다." << std::endl;
                movieM.saveToFile("data/movies.csv");
                userM.saveToFile("data/users.csv");
                ratingM.saveToFile("data/ratings.csv");
                return 0; }

            case 1:{
                int id, year;
                std::string title, genre;
                std::cout << "영화의 ID, 제목, 장르, 연도를 입력하세요 : ";
                std::cin >> id >> title >> genre >> year;
                movieM.addMovie(Movie(id, title, genre, year));
                break;}

            case 2: {
                std::string title;
                std::cout << "제목을 입력하세요 : ";
                std::cin >> title;
                movieM.searchMovie(title);
                break; }

            case 3: {
               movieM.printAll();
                break; }

            case 4:{
                movieM.sortByRating();
                movieM.printAll();
                break; }

            case 5: {
                int id;
                std::string name, email;
                std::cout << "ID, 이름, 이메일을 입력하세요 : ";
                std::cin >> id >> name >> email;
                userM.addUser(User(id, name, email));
                break; }

            case 6:
               userM.printAll();
                break;

            case 7: { 
                int userid, movieid;
                double score;
                std::cout << "유저ID, 영화ID, 평점(0~5)을 입력하세요 : ";
                std::cin >> userid >> movieid >> score;
                ratingM.rate(userid, movieid, score); 
                movieM.addRating(movieid, score);
                break; }

            case 8: { 
                int movieid;
                std::cout << "조회할 영화 ID를 입력하세요 : ";
                std::cin >> movieid;
                ratingM.printRating(movieid);
                break;
            }

            case 9: {
                int u1, u2;
                std::cout << "비교할 두 유저의 ID를 입력하세요: ";
                std::cin >> u1 >> u2;

                std::vector<Rating> ratings1 = ratingM.findByUser(u1);
                std::vector<Rating> ratings2 = ratingM.findByUser(u2);

                int sim = SimilarityCalculator::calculate(ratings1, ratings2);

                if (sim == -100) {
                    std::cout << "공통으로 본 영화가 없어서 비교 불가!" << std::endl;
                } else {
                    std::cout << "User " << u1 << "와 User " << u2 << "의 유사도: " << sim << std::endl;
                }
                break;
            }

            case 10: {
                int targetId;
                std::cout << "추천받을 유저 ID 입력: ";
                std::cin >> targetId;
    
                Recommender rec(movieM, ratingM, userM);
                std::vector<int> recMovies = rec.recommend(targetId);
    
                if (recMovies.empty()) {
                    std::cout << "추천 결과가 없습니다! 평점을 더 남기거나 친구를 만드세요." << std::endl;
                } else {
                    std::cout << "\n=== 당신을 위한 추천 영화 ===" << std::endl;
                    for (int mId : recMovies) {
            
                    const Movie* m = movieM.findById(mId);
                    if (m) std::cout << *m << std::endl;
                    }
                }
                break;
            }

            default:
                std::cout << "잘못된 입력입니다." << std::endl;
        }
    }

    return 0;
}