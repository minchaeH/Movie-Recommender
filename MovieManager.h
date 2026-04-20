#pragma once
#include <string>
#include <vector>
#include "Movie.h"

class MovieManager {

    private:
        std::vector<Movie> movies;

    public:
        void addMovie(const Movie& movie);
        void sortByRating();
        void printAll() const;
        void searchMovie(const std::string& title) const;

};