#ifndef PARTB_H
#define PARTB_H

#include "PartA.h"

struct Point {
	int x;
	int y;
	bool inPath;
};

double arbitraryInsertion(vector<Point> &nodes, vector<int> &path);

void readFilePartB(vector<Point> &nodes);

double distancePartB(Point &a, Point &b);

void printPath(vector<int> &path);

#endif //PARTB_H
