#ifndef PARTA_H
#define PARTA_H

#include <cmath>
#include <limits>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Pokemon {
public:
	Pokemon(int xIn, int yIn) : x(xIn), y(yIn), prev(-2), distance(numeric_limits<double>::infinity()), visited(false) {}

	int getX() {
		return x;
	}

	int getY() {
		return y;
	}

	void setPrev(int prevIn) {
		prev = prevIn;
	}

	int getPrev() {
		return prev;
	}

	void setDistance(double distanceIn) {
		distance = distanceIn;
	}

	double getDistance() {
		return distance;
	}

	void setVisited(bool visitedIn) {
		visited = visitedIn;
	}

	bool isVisited() {
		return visited;
	}

private:
	int x, y, prev;
	double distance;
	bool visited;
};

void readFile(vector<Pokemon> &graph);

double calcDistance(Pokemon &pokemon1, Pokemon &pokemon2);

double findMST(vector<Pokemon> &graph);

void printMST(vector<Pokemon> &graph);

bool isSea(Pokemon &pokemon);

bool isCoast(Pokemon &pokemon);

bool isLand(Pokemon &pokemon);
#endif // PARTA_H
