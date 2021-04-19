#include "Graph.h"
#include "Set.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <chrono>

// The following reference was used when working with the executution time: https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
// The following reference was used to call the Implement class in python: https://www.geeksforgeeks.org/how-to-call-c-c-from-python/

using namespace std;
using namespace std::chrono;

class Implement
{
	unordered_Set* set = NULL;
	Graph* graph = NULL;

	vector<string> updateGenre(string& s)
	{
		vector<string> toReturn;
		if (s.substr(0, 1) != "\"")
		{
			toReturn.push_back(s);
			return toReturn;
		}
		s = s.substr(1, s.size() - 2);
		while (s.find(',') != string::npos)
		{
			toReturn.push_back(s.substr(0, s.find(',')));
			s = s.substr(s.find(',') + 2);
		}
		toReturn.push_back(s);
		return toReturn;
	}
	void updateCountry(string& s)
	{
		if (s.substr(0, 1) == "\"")
			s = s.substr(1, s.find(",") - 1);
	}
	stack<Movie*> makeList()
	{
		stack<Movie*> movies;
		ifstream file("movies.txt");
		string line;
		getline(file, line);
		string code;
		string title;
		string year;
		string tempGenres;
		vector<string> genres;
		string duration;
		string country;
		for (int i = 1; i < 85856; i++)
		{
			getline(file, code, '\t');
			getline(file, title, '\t');
			getline(file, year, '\t');
			getline(file, tempGenres, '\t');
			genres = updateGenre(tempGenres);
			getline(file, duration, '\t');
			getline(file, country);
			updateCountry(country);
			movies.push(new Movie(code, title, stoi(year), genres, stoi(duration), country));
		}
		file.close();
		return movies;
	}

public:

	Implement()
	{
		stack<Movie*> movies_Graph = makeList();
		stack<Movie*> movies_Set = movies_Graph;
		ofstream file("implemetationTime.txt");

		auto set_start = high_resolution_clock::now();
		set = new unordered_Set();
		while (!movies_Set.empty())
		{
			set->insert(movies_Set.top());
			movies_Set.pop();
		}
		auto set_stop = high_resolution_clock::now();
		auto set_implementation_duration = duration_cast<milliseconds>(set_stop - set_start);
		file << "Time required for set implementation: " << set_implementation_duration.count() << " milliseconds" << endl;


		auto graph_start = high_resolution_clock::now();
		graph = new Graph();
		while (!movies_Graph.empty())
		{
			graph->insertMovie(movies_Graph.top());
			movies_Graph.pop();
		}
		auto graph_stop = high_resolution_clock::now();
		auto graph_implementation_duration = duration_cast<milliseconds>(graph_stop - graph_start);
		file << "Time required for graph implementation: " << graph_implementation_duration.count() << " milliseconds" << endl;

		file.close();
	}

	void filter()
	{
		ifstream file("userInput.txt");
		string genre;
		int year1;
		int year2;
		int duration1;
		int duration2;
		string country;
		file >> genre;
		file >> year1;
		file >> year2;
		file >> duration1;
		file >> duration2;
		file >> country;
		file.close();
		string* countryInput = &country;
		if (country == "All")
		{
			countryInput = nullptr;
		}
		ofstream file1("implemetationTime.txt");

		auto set_start = high_resolution_clock::now();
		vector<Movie*> filteredSet = set->FindMovies(&genre, &year1, &year2, &duration1, &duration2, countryInput);
		ofstream file2("outputSet.txt");
		for (int i = 0; i < filteredSet.size(); i++)
		{
			file2 << filteredSet[i]->title << endl;
			file2 << filteredSet[i]->code << endl;
		}
		file2.close();
		auto set_stop = high_resolution_clock::now();
		auto set_implementation_duration = duration_cast<milliseconds>(set_stop - set_start);
		file1 << "Time required for filtering set: " << set_implementation_duration.count() << " milliseconds" << endl;

		auto graph_start = high_resolution_clock::now();
		vector<Movie*> filteredGraph = graph->Filter(&genre, &year1, &year2, &duration1, &duration2, countryInput);
		ofstream file3("outputGraph.txt");
		for (int i = 0; i < filteredGraph.size(); i++)
		{
			file3 << filteredSet[i]->title << endl;
			file3 << filteredSet[i]->code << endl;
		}
		file3.close();
		auto graph_stop = high_resolution_clock::now();
		auto graph_implementation_duration = duration_cast<milliseconds>(graph_stop - graph_start);
		file1 << "Time required for filtering graph: " << graph_implementation_duration.count() << " milliseconds" << endl;
	}

};

extern "C"
{
	Implement* Implement_new() {
		return new Implement();
	}
	void Implement_filter(Implement* obj) {
		obj->filter();
	}
}