#pragma once
#include <string>
#include "Movie.h"
#include <vector>
#include "BaseManager.h"


class MovieManager : public BaseManager {

    private:
        std::vector<Movie> movies;
        int calculateLevenshteinDistance(const std::string& s1, const std::string& s2) const;
        
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
        void filterByGenre(const std::string& genre) const;
        void printStatistics() const;

        std::vector<Movie>& getMovies() { return movies; }
};