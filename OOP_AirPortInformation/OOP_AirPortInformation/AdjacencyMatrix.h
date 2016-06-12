#pragma once
#ifndef ADJACENCY_MATRIX_H
#define ADJACENCY_MATRIX_H
#include <string>
#include <list>
#include <iterator>
#include <vector>
#include <iostream>
#include <queue>
#include <map>
#include <stack>
#include "FlightInfo.h"
class AdjacencyMatrix
{
public:
	AdjacencyMatrix() {};
	~AdjacencyMatrix() 
	{
		for (int i = 0; i < nodes; i++)
		{
			delete []adjMatrix[i];
			
		}
		delete []visited;
		delete []adjMatrix;
	};
	AdjacencyMatrix(int init);
	bool HasEdge(int source, int target);
	void PrintGraph(int counter);
	void PrintGraph(int counter, vector<string> nodes);
	void AddEdge(int source, int dest, int cost);
	int DepthFirstSearch(int from, int to, int size);
	int minDistance(vector<int> dist, vector<bool> sptSet);
	int Dijkstra(int src, int to, vector<string> cities);
	vector<int> ShortestPath(int src, int to, vector<string> cities);
	vector<int> path(int source, int target, map<int, int> parentMap, vector<string> cities);
private:
	vector<int> listStops;
	int nodes;
	int **adjMatrix;
	bool *visited;
};


#endif
