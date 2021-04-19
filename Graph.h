#pragma once
#include "Movie.h"
#include<map>
#include<fstream>

class Graph
{
public:

	map<string*, vector<Movie*>> adjList;
	string* sources;

	Graph() {
		ifstream file("Genres.txt");
		string line;
		sources = new string[21];
		for (int i = 0; file >> line; i++) {
			sources[i] = line;
		}
	}

	void insertMovie(Movie* movie) {
		for (int i = 0; i < 21; i++) {
			if ((*movie).Check(&sources[i])) {
				adjList[&sources[i]].push_back(movie);
			}
		}
	}

	vector<Movie*> Filter(string* genre, int* yrLow, int* yrHigh, int* durLow, int* durHigh, string* country) {

		vector<Movie*> result;
		for (auto source : adjList) {
			if (*source.first == *genre) {
				for (int i = 0; i < source.second.size(); i++)
					if ((source.second[i]->year >= *yrLow) && (source.second[i]->year <= *yrHigh) && (source.second[i]->duration >= *durLow) && (source.second[i]->duration <= *durHigh) && (country == nullptr || source.second[i]->country == *country))
						result.push_back(source.second[i]);
			}
		}
		return result;

	}

};
