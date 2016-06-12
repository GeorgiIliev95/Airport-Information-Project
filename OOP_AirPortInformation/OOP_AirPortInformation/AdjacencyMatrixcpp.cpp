#include "AdjacencyMatrix.h"

void print(int source, int target, map<int, int> parentMap, vector<string> cities);

AdjacencyMatrix::AdjacencyMatrix(int init)
{
	nodes = init;
	visited = new bool[init];
	for (int i = 0; i < init; i++)
	{
		visited[i] = false;
	}
	adjMatrix = new int*[init];
	for (int i = 0; i < init; i++)
	{

		adjMatrix[i] = new int[init];

	}
	for (int i = 0; i < init; i++)
	{
		for (int j = 0; j < init; j++)
		{
			adjMatrix[i][j] = 0;
		}
	}
}
bool AdjacencyMatrix::HasEdge(int source, int target)
{
	return adjMatrix[source][target] > 0;
}
void AdjacencyMatrix::PrintGraph(int counter)
{
	for (int i = 0; i < counter; i++)
	{
		for (int j = 0; j < counter; j++)
		{
			std::cout << adjMatrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}
};
void AdjacencyMatrix::PrintGraph(int counter, vector<string> nodes)
{
	cout << "\t";
	for each (auto var in nodes)
	{
		cout << var << "\t";
	}
	cout << endl;
	for (int i = 0; i < counter; i++)
	{
		cout << nodes[i] << "\t";
		for (int j = 0; j < counter; j++)
		{
			std::cout << adjMatrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}
void AdjacencyMatrix::AddEdge(int source, int dest, int cost)
{
	adjMatrix[source][dest] = cost;
}
int AdjacencyMatrix::DepthFirstSearch(int from, int to, int size)
{
	
	for (int i = 0; i < size; i++)
	{
		visited[i] = false;
	}
	stack<int> Stack;
	Stack.push(from);
	visited[from] = true;
	int c = 0;
	if (from == to)
	{
		return -2;
	}
	//cout << "Depth first Search starting from vertex ";
	//cout << from << " : " << endl;
	while (!Stack.empty())
	{
		from = Stack.top();
		//cout << from << " ";
		Stack.pop();
		if (from == to && c != 1)
		{
			//cout << "Airport found" << endl;
			return 1;
		}
		if (from == to && c == 1)
		{
			//cout << "Airport found" << endl;
			return 0;
		}
		for (int i = 0; i < size; i++)
		{
			if (adjMatrix[from][i] >0 && !visited[i])
			{
				visited[i] = true;
				Stack.push(i);
			}
		}
		c++;
	}
	cout << endl;
	return -1;

};

int  AdjacencyMatrix::minDistance(vector<int> dist, vector<bool> sptSet)
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v <nodes; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}


int  AdjacencyMatrix::Dijkstra(int src, int to, vector<string> cities)
{
	map<int, int> parentMap;
	vector<int> dist(nodes); // The output array.  dist[i] will hold the shortest
							 // distance from src to i

	vector<bool> sptSet(nodes); // sptSet[i] will true if vertex i is included in shortest
								// path tree or shortest distance from src to i is finalized

								// Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < nodes; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < nodes - 1; count++)
	{
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in first iteration.
		int u = minDistance(dist, sptSet);
		
		
		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the picked vertex.
		for (int v = 0; v <nodes; v++)

			// Update dist[v] only if is not in sptSet, there is an edge from
			// u to v, and total weight of path from src to  v through u is
			// smaller than current value of dist[v]
			if (!sptSet[v] && adjMatrix[u][v] && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v])
			{
				parentMap[v] = u;
				dist[v] = dist[u] + adjMatrix[u][v];
				//cout << cities[v] << "-";
			}
	}
	
	print(src, to, parentMap,cities);
	
	// print the constructed distance array
	return dist[to];
}
void print(int source,int target,map<int,int> parentMap,vector<string> cities)
{
	vector<int> citiesVec;
	int current=target;
	while (current!=source)
	{
		
		citiesVec.push_back(current);
		current=parentMap[current];
	}
	citiesVec.push_back(current);
	cout << "\n\tCity stopovers:";
	for (int i =citiesVec.size()-1; i >=0;i--)
	{
		cout << cities[citiesVec[i]] << " ";
	}
	
	cout << endl;
}
vector<int> AdjacencyMatrix::path(int source, int target, map<int, int> parentMap, vector<string> cities)
{
	vector<int> citiesVec;
	vector<int> citiesInOrder;
	int current = target;
	while (current != source)
	{

		citiesVec.push_back(current);
		current = parentMap[current];
	}
	citiesVec.push_back(current);
	for (int i = citiesVec.size() - 1; i >= 0;i--)
	{
		citiesInOrder.push_back(citiesVec[i]);
	}
	return citiesInOrder;
}
vector<int> AdjacencyMatrix::ShortestPath(int src, int to, vector<string> cities)
{
	map<int, int> parentMap;
	vector<int> dist(nodes); // The output array.  dist[i] will hold the shortest
							 // distance from src to i

	vector<bool> sptSet(nodes); // sptSet[i] will true if vertex i is included in shortest
								// path tree or shortest distance from src to i is finalized

								// Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < nodes; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < nodes - 1; count++)
	{
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in first iteration.
		int u = minDistance(dist, sptSet);


		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the picked vertex.
		for (int v = 0; v <nodes; v++)

			// Update dist[v] only if is not in sptSet, there is an edge from
			// u to v, and total weight of path from src to  v through u is
			// smaller than current value of dist[v]
			if (!sptSet[v] && adjMatrix[u][v] && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v])
			{
				parentMap[v] = u;
				dist[v] = dist[u] + adjMatrix[u][v];
				//cout << cities[v] << "-";
			}
	}

	return path(src, to, parentMap, cities);
}