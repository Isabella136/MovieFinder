#pragma once

#include<string>
#include<vector>
using namespace std;

class Movie
{
public:

	string code;
	string title;
	int year;
	vector<string> genres;
	int duration;
	string country;


	Movie(string code, string title, int year, vector<string> genres, int duration, string country) {
		this->code = code;
		this->title = title;
		this->year = year;
		this->genres = genres;
		this->duration = duration;
		this->country = country;
	}

	bool Check(string* source) {
		for (string gen : this->genres) {
			if (gen == *source) return true;
		}
		return false;
	}

};