#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <utility>
using namespace std;

//adds an edge in an Adjacency Matrix
void addEdge(vector<vector<int>>& adjMatrix, int i, int j, int weight) {
	adjMatrix[i][j] = weight;//for a directed graph
	//adjMatrix[j][i]= weight;//for an undirected graph
}

//creates Adjacency Matrix for custom Graph
void createCustomMatrix(vector<vector<int>>& adjMatrix, int V) {
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			adjMatrix[i][j] = 0;
		}
	}

	addEdge(adjMatrix, 0, 1, 4);
	addEdge(adjMatrix, 0, 2, 1);
	addEdge(adjMatrix, 0, 3, 9);
	addEdge(adjMatrix, 1, 0, 3);
	addEdge(adjMatrix, 1, 2, 6);
	addEdge(adjMatrix, 1, 3, 11);
	addEdge(adjMatrix, 2, 0, 4);
	addEdge(adjMatrix, 2, 1, 1);
	addEdge(adjMatrix, 2, 3, 2);
	addEdge(adjMatrix, 3, 0, 6);
	addEdge(adjMatrix, 3, 1, 5);
	addEdge(adjMatrix, 3, 2, 7);
}

//adds an edge in an Adjacency List
void addEdge(vector<list<pair<int, int>>>& adjList, int i, int j, int weight) {
	adjList[i].push_back(make_pair(j, weight));//for a directed graph
	//adjList[j].push_back(make_pair(i,weight));//for an undirected graph
}


//creates AdjacencyList for custom Graph
void createCustomList(vector<list<pair<int, int>>>& adjList, int V) {
	addEdge(adjList, 0, 1, 4);
	addEdge(adjList, 0, 2, 1);
	addEdge(adjList, 0, 3, 9);
	addEdge(adjList, 1, 0, 3);
	addEdge(adjList, 1, 2, 6);
	addEdge(adjList, 1, 3, 11);
	addEdge(adjList, 2, 0, 4);
	addEdge(adjList, 2, 1, 1);
	addEdge(adjList, 2, 3, 2);
	addEdge(adjList, 3, 0, 6);
	addEdge(adjList, 3, 1, 5);
	addEdge(adjList, 3, 2, 7);
}

int main() {
	/*
	An adjacency matrix m is a very simple way to represent a graph
	The idea is that the cell m[i][j] represents the edge weight of
	going from node i to node j
	*/

	int V = 4;//number of vertices
	vector<vector<int>> adjMatrix(V);
	createCustomMatrix(adjMatrix, V);
	
	/*
	Pros:
	Space Efficient for representing dense graphs.
	Edge weight lookup is O(1).
	Simplest graph representation.

	Cons:
	Requires O(V^2) space.
	Iterating over all edges takes O(V^2) time.
	*/

	//-----------------------------------------------------------------

	/*
	An Adjacency List is a way to represent a graph.
	The vertices are indexes in a vector.
	Each vertex has a list of its edges represented as pairs(where it goes,weight).
	*/

	vector<list<pair<int,int>>> adjList(4);
	createCustomList(adjList, 4);

	/*
	Pros:
	Space efficient for representing sparse graphs.
	Iterating over all edges is efficient - O(E).

	Cons:
	Less space efficient for denser graphs.
	edge weight lookup is O(E).
	slightly more complex graph representation.
	*/

	//-----------------------------------------------------------------

	/*
	An Edge List is a way to represent a graph simply as an unordered list of edges.
	Every edge is a triple (u,v,w) "the weight from node u to v is w"
	*/

	//Not really popular to use

	/*
	Pros:
	Space efficient for representing sparse graphs.
	Iterating over all edges is efficient.
	Very simple structure.
	
	Cons:
	Less Space efficient for denser graphs.
	Edge weight lookup is O(E).
	No way to access unconnected nodes.
	*/

	return 0;
}



