#ifndef PARTC_H
#define PARTC_H

#include "PartB.h"
#include <algorithm>

class OPTTSP {
public:
	OPTTSP() {
		readFilePartC();
		adjMat.resize(points.size());
		for (size_t i = 0; i < points.size(); i++) {
			adjMat[i].reserve(points.size());
			for (size_t j = 0; j < points.size(); j++) {
				if (j != i) {
					adjMat[i].push_back(calcDistanceFromIndicies((int)i, (int)j));
				}
				else {
					adjMat[i].push_back(0);
				}
			}
		}
		bestWeight = arbitraryInsertionC();
		bestPath.pop_back();
		/*
		currPath.reserve(bestPath.size());
		for (int i = 0; i < (int)bestPath.size(); i++) {
			currPath.push_back(bestPath[i]);
		}
		*/
		currPath = bestPath;
	}

	void genPerms(size_t permLength, double currWeight) {
		if (permLength == currPath.size()) {
			//currWeight = calcWeight(currPath, permLength);
			currWeight += adjMat[currPath[0]][currPath[permLength - 1]];
			//cout << currWeight << "\n";
			if (currWeight < bestWeight) {
				for (size_t i = 0; i < bestPath.size(); i++) {
					bestPath[i] = currPath[i];
				}
				bestWeight = currWeight;
			}
			//currWeight = 0;
			return;
		}
		if (!promising(permLength, currWeight)) {
			//currWeight = 0;
			return;
		}
		for (size_t i = permLength; i < currPath.size(); i++) {
			swap(currPath[permLength], currPath[i]);
			genPerms(permLength + 1, 
					 currWeight + adjMat[currPath[permLength]][currPath[permLength - 1]]);
			swap(currPath[permLength], currPath[i]);
		}
	}

	void printBestPath() {
		cout << bestWeight << "\n";
		for (size_t i = 0; i < bestPath.size(); i++) {
			cout << bestPath[i] << " ";
		}
		cout << "\n";
	}
private:
	vector<int> currPath;
	vector<int> bestPath;
	vector<Point> points;
	vector<vector<double>> adjMat;
	//double currWeight;
	double bestWeight;
	//add an adjacency matrix


	//member functions
	void readFilePartC() {
		int numNodes, x, y;
		cin >> numNodes;
		for (int i = 0; i < numNodes; i++) {
			Point temp;
			cin >> x >> y;
			temp.x = x;
			temp.y = y;
			temp.inPath = false;
			points.push_back(temp);
		}
		return;
	}
	
	double calcDistanceFromIndicies(int i, int j) {
		double distance = 0;
		double x1 = points[i].x;
		double x2 = points[j].x;
		double y1 = points[i].y;
		double y2 = points[j].y;
		distance = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
		return distance;
	}

	double arbitraryInsertionC() {
		double pathWeight = 0;
		//readFilePartC(points);
		bestPath.push_back(0);
		points[0].inPath = true;

		double minDistance = numeric_limits<double>::max();
		
		int minIndex = 0;
		/*
		for (int i = 1; i < (int)points.size(); i++) {
			double distance = distancePartB(points[0], points[i]);
			if (distance - minDistance < 0) {
				minDistance = distance;
				minIndex = i;
			}
		}
		*/
		bestPath.push_back(1);
		bestPath.push_back(2);
		points[1].inPath = true;
		points[2].inPath = true;
		pathWeight += adjMat[0][1] + adjMat[1][2] + adjMat[2][0];
		bestPath.push_back(0);

		for (int i = 0; i < (int)points.size(); i++) {
			if (!points[i].inPath) {
				double distance;
				minDistance = numeric_limits<double>::max();
				for (int j = 1; j < (int)(bestPath.size()); j++) {
					//distance = (distancePartB(points[bestPath[j - 1]], points[i]) +
						//distancePartB(points[i], points[bestPath[j]]) -
						//distancePartB(points[bestPath[j - 1]], points[bestPath[j]]));
					distance = (adjMat[bestPath[j - 1]][i] +
						adjMat[i][bestPath[j]] -
						adjMat[bestPath[j - 1]][bestPath[j]]);
					if (distance - minDistance < 0) {
						minDistance = distance;
						minIndex = j;
					}
				}
				bestPath.insert(bestPath.begin() + minIndex, i);
				points[i].inPath = true;
				pathWeight += minDistance;
			}
		}

		return pathWeight;
	}

	/*
	double calcWeight(vector<int> &path, size_t permLength) {
		double weight = 0;
		for (size_t i = 1; i < permLength; i++) {
			weight += distancePartB(points[path[i - 1]], points[path[i]]);
		}
		return weight;
	}
	*/

	bool promising(size_t permLength , double currWeight) {
		//currWeight = calcWeight(currPath, permLength);
		//cout << currWeight << "\n";
		if (currWeight >= bestWeight) {
			return false;
		}
		else {
			if (permLength > 4) {
				vector<Pokemon> MST;
				vector<int> indices;
				MST.reserve(currPath.size() - permLength);
				indices.reserve(currPath.size() - permLength);
				double minDistA = numeric_limits<double>::max();
				double minDistB = numeric_limits<double>::max();
				for (size_t i = permLength; i < currPath.size(); i++) {
					double distA, distB;
					MST.push_back(Pokemon(points[currPath[i]].x, points[currPath[i]].y));
					indices.push_back(currPath[i]);
					//distA = distancePartB(points[0], points[currPath[i]]);
					//distB = distancePartB(points[currPath[permLength - 1]], points[currPath[i]]);
					distA = adjMat[0][currPath[i]];
					distB = adjMat[currPath[permLength - 1]][currPath[i]];
					if (distA < minDistA) {
						minDistA = distA;
					}
					if (distB < minDistB) {
						minDistB = distB;
					}
				}
				double MSTweight = findMSTC(MST, indices);
				return ((currWeight + MSTweight + minDistA + minDistB) < bestWeight);
			}
			return currWeight < bestWeight;
		}
	}

	double findMSTC(vector<Pokemon> &graph, vector<int> &indices) {
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
				minIndex = minEdgeIndex;
			}
			graph[minIndex].setVisited(true);
			weight += graph[minIndex].getDistance();
			double distance;
			if (i != (int)graph.size() - 1) {
				for (int j = 0; j < (int)graph.size(); j++) {
					if (graph[j].isVisited() == false && j != minIndex) {
						//distance = calcDistance(graph[minIndex], graph[j]);
						distance = adjMat[indices[minIndex]][indices[j]];
						if (distance < graph[j].getDistance()) {
							graph[j].setDistance(distance);
							graph[j].setPrev(minIndex);
						}
					}
					if (graph[j].isVisited() == false &&
						graph[j].getDistance() - minDistance < 0 &&
						j != minIndex) {
						minDistance = graph[j].getDistance();
						minEdgeIndex = j;
					}
				}
			}
		}

		return weight;
	}
};


#endif