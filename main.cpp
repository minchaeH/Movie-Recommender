#include <iostream>
#include <vector>
#include <string>
#include "Movie.h"
#include "User.h"
#include "Rating.h"
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"

int main() {
    
    MovieManager movieM;
    UserManager userM;
    RatingManager ratingM;

    int select;
    
    while(true) {
        
        std::cout << "\n0~8 사이의 숫자를 입력해주세요.\n" << std::endl;
        std::cout << "0: 종료,\n1: 영화 추가\n2: 영화 제목으로 검색\n";
        std::cout << "3: 영화 전체 출력\n4: 영화 평점순 출력\n5: 사용자 추가\n";
        std::cout << "6: 사용자 목록 출력\n7: 평점 입력\n8: 영화별 전체 평점 조회" << std::endl;
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

            default:
                std::cout << "잘못된 입력입니다." << std::endl;
        }
    }

    return 0;
}