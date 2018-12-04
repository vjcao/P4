#include "PartA.h"

void readFile(vector<Pokemon> &graph) {
	int numV;
	cin >> numV;

	graph.reserve(numV);

	int x, y;

	int numSea = 0, numCoast = 0, numLand = 0;

	for (int i = 0; i < numV; i++) {
		cin >> x >> y;
		if (x < 0 && y < 0) {
			numSea++;
		}
		else if ((x <= 0 && y == 0) || (x == 0 && y <= 0)) {
			numCoast++;
		}
		else {
			numLand++;
		}
		graph.push_back(Pokemon(x, y));
	}
	if (numSea > 0 && numLand > 0 && numCoast == 0) {
		cerr << "Cannot construct MST";
		exit(1);
	}
}

double calcDistance(Pokemon &pokemon1, Pokemon &pokemon2) {
	double x1 = (double)pokemon1.getX();
	double y1 = (double)pokemon1.getY();
	double x2 = (double)pokemon2.getX();
	double y2 = (double)pokemon2.getY();
	double distance;

	distance = sqrt((double)((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));

	return distance;
}

//FIXME: REMOVE AFTER OPTIMIZING
int findMinKey(vector<Pokemon> &graph) {
	double min = numeric_limits<double>::max();
	int minIndex = 0;
	for (int i = 0; i < (int)graph.size(); i++) {
		if (graph[i].isVisited() == false && graph[i].getDistance() < min) {
			minIndex = i;
			min = graph[i].getDistance();
		}
	}
	return minIndex;
}

//FIXME: OPTIPMIZE
double findMST(vector<Pokemon> &graph) {
	graph[0].setDistance(0);
	graph[0].setPrev(-1);
	double weight = 0;
	int minEdgeIndex = 0;

	for (int i = 0; i < (int)graph.size(); i++) {
		double minDistance = numeric_limits<double>::max();
		int minIndex;
		//int numIndexChange = 0;
		if (i == 0) {
			minIndex = 0;
		}
		else {
			minIndex = minEdgeIndex;//findMinKey(graph);
		}
		graph[minIndex].setVisited(true);
		weight += graph[minIndex].getDistance();
		double distance;
		if (i != (int)graph.size() - 1) {
			if (isSea(graph[minIndex])) {
				for (int j = 0; j < (int)graph.size(); j++) {
					if ((isSea(graph[j]) || isCoast(graph[j])) && graph[j].isVisited() == false && j != minIndex) {
						distance = calcDistance(graph[minIndex], graph[j]);
						if (distance < graph[j].getDistance()) {
							graph[j].setDistance(distance);
							graph[j].setPrev(minIndex);
						}
					}
					if (graph[j].isVisited() == false && graph[j].getDistance() - minDistance < 0 && j != minIndex) {
						minDistance = graph[j].getDistance();
						minEdgeIndex = j;
					}
				}
			}
			else if (isLand(graph[minIndex])) {
				for (int j = 0; j < (int)graph.size(); j++) {
					if ((isLand(graph[j]) || isCoast(graph[j])) && graph[j].isVisited() == false && j != minIndex) {
						distance = calcDistance(graph[minIndex], graph[j]);
						if (distance < graph[j].getDistance()) {
							graph[j].setDistance(distance);
							graph[j].setPrev(minIndex);
						}
					}
					if (graph[j].isVisited() == false && graph[j].getDistance() - minDistance < 0 && j != minIndex) {
						minDistance = graph[j].getDistance();
						minEdgeIndex = j;
					}
				}
			}
			else {
				for (int j = 0; j < (int)graph.size(); j++) {
					if (graph[j].isVisited() == false && j != minIndex) {
						distance = calcDistance(graph[minIndex], graph[j]);
						if (distance < graph[j].getDistance()) {
							graph[j].setDistance(distance);
							graph[j].setPrev(minIndex);
						}
					}
					if (graph[j].isVisited() == false && graph[j].getDistance() - minDistance < 0 && j != minIndex) {
						minDistance = graph[j].getDistance();
						minEdgeIndex = j;
					}
				}
			}
		}
	}

	return weight;
}

void printMST(vector<Pokemon> &graph) {
	for (int i = 1; i < (int)graph.size(); i++) {
		cout << min(i, graph[i].getPrev()) << " " << max(i, graph[i].getPrev()) << "\n";
	}
}

bool isSea(Pokemon &pokemon) {
	return (pokemon.getX() < 0 && pokemon.getY() < 0);
}

bool isCoast(Pokemon &pokemon) {
	return ((pokemon.getX() <= 0 && pokemon.getY() == 0) || (pokemon.getX() == 0 && pokemon.getY() <= 0));
}

bool isLand(Pokemon &pokemon) {
	return ((pokemon.getX() > 0 && pokemon.getY() > 0) || (pokemon.getX() <= 0 && pokemon.getY() > 0) || (pokemon.getX() > 0 && pokemon.getY() <= 0));
}