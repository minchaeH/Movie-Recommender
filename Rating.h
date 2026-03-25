#pragma once
#include <string>

class Rating {
private:
    int         userId;
    int         movieId;
    double      score;

public:
    Rating();
    Rating(int userId, int movieId, double score);

    int         getUserId()  const;
    int         getMovieId() const;
    double      getScore()   const;

    void        display() const;
};