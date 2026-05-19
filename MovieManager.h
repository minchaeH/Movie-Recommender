#pragma once
#include <string>
#include "Movie.h"
#include <vector>
#include "BaseManager.h"


class MovieManager : public BaseManager {

    private:
        std::vector<Movie> movies;

    public:
        void addMovie(const Movie& movie);
        void sortByRating();
        void printAll() const;
        void searchMovie(const std::string& title) const;
        void addRating(int movieId, double score);
        const Movie* findById(int id) const; 
        void loadFromFile(const std::string& filename) override;
        void saveToFile(const std::string& filename) override;
        int size() const override;

        std::vector<Movie>& getMovies() { return movies; }
};