#include "PartB.h"

double arbitraryInsertion(vector<Point> &nodes, vector<int> &path) {
	double pathWeight = 0;
	readFilePartB(nodes);
	path.push_back(0);
	nodes[0].inPath = true;

	double minDistance = numeric_limits<double>::max();
	int minIndex;
	for (int i = 1; i < (int)nodes.size(); i++) {
		double distance = distancePartB(nodes[0], nodes[i]);
		if (distance - minDistance < 0) {
			minDistance = distance;
			minIndex = i;
		}
	}
	nodes[minIndex].inPath = true;
	path.push_back(minIndex);
	pathWeight += (2.0 * minDistance);
	path.push_back(0);

	for (int i = 0; i < (int)nodes.size(); i++) {
		if (!nodes[i].inPath) {
			double distance;
			minDistance = numeric_limits<double>::max();
			for (int j = 1; j < (int)(path.size()); j++) {
				distance = (distancePartB(nodes[path[j - 1]], nodes[i]) + 
							distancePartB(nodes[i], nodes[path[j]]) - 
							distancePartB(nodes[path[j - 1]], nodes[path[j]]));
				if (distance - minDistance < 0) {
					minDistance = distance;
					minIndex = j;
				}
			}
			path.insert(path.begin() + minIndex, i);
			nodes[i].inPath = true;
			pathWeight += minDistance;
		}
	}

	return pathWeight;
}

void readFilePartB(vector<Point> &nodes) {
	int numNodes, x, y;
	cin >> numNodes;
	for (int i = 0; i < numNodes; i++) {
		Point temp;
		cin >> x >> y;
		temp.x = x;
		temp.y = y;
		temp.inPath = false;
		nodes.push_back(temp);
	}
	return;
}

double distancePartB(Point &a, Point &b) {
	double x1 = (double)a.x;
	double y1 = (double)a.y;
	double x2 = (double)b.x;
	double y2 = (double)b.y;

	return sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));
}

void printPath(vector<int> &path) {
	for (int i = 0; i < (int)(path.size() - 1); i++) {
		cout << path[i] << " ";
	}
	cout << "\n";
}