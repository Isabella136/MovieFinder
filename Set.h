#pragma once
#include "Movie.h"
#include <string>
#include <list>
#include <iterator>


class unordered_Set {
public:
    int bucketCount;
    list<Movie*> movieList;

    unordered_Set() {
        bucketCount = 100000;
    }

    void insert(Movie* movie) {
        movieList.push_back(movie);
    }

    //iterate through set to find matches
    vector<Movie*> FindMovies(string* genre, int* yrLow, int* yrHigh, int* durLow, int* durHigh, string* country) {
        vector<Movie*> recomendations;
        list<Movie*> ::iterator it;

        for (it = movieList.begin(); it != movieList.end(); ++it) {

            //check genres
            for (int j = 0; j < (*it)->genres.size(); j++) {
                if ((*it)->genres[j] == *genre) {

                    //check year
                    if (yrLow == nullptr && yrHigh == nullptr || (*it)->year >= *yrLow && (*it)->year <= *yrHigh) {

                        //check duration
                        if (durLow == nullptr && durHigh == nullptr || (*it)->duration >= *durLow && (*it)->duration <= *durHigh) {

                            //check country
                            if (country == nullptr || (*it)->country == *country) {
                                recomendations.push_back((*it));
                            }
                        }
                    }
                }
            }
        }
        return recomendations;
    }
};

