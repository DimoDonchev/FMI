#include <iostream>
#include <vector>
#include <list>
using namespace std;

void add_Edge(vector<list<int>>& adjList, int i, int j) {
	adjList[i].push_back(j);
	adjList[j].push_back(i);
}

void init_graph(vector<list<int>>& adjList) {
	//adding 5 separate components

	add_Edge(adjList, 0, 4);
	add_Edge(adjList, 0, 8);
	add_Edge(adjList, 0, 14);
	add_Edge(adjList, 0, 13);
	add_Edge(adjList, 4, 8);
	add_Edge(adjList, 8, 14);
	add_Edge(adjList, 14, 13);

	add_Edge(adjList, 6, 7);
	add_Edge(adjList, 7, 11);
	add_Edge(adjList, 11, 6);

	add_Edge(adjList, 1, 5);
	add_Edge(adjList, 5, 16);
	add_Edge(adjList, 5, 17);

	add_Edge(adjList, 3, 9);
	add_Edge(adjList, 9, 2);
	add_Edge(adjList, 9, 15);
	add_Edge(adjList, 2, 15);
	add_Edge(adjList, 15, 10);

	//vertex 12 has no edges
}

void dfs(vector<list<int>>& adjList, vector<bool>& visited, int node) {
	if (visited[node])return;
	else {
		visited[node] = true;
		int neighbours_size = adjList[node].size();
		for (auto i : adjList[node]) {//for each element of the list
			if(!visited[i]) dfs(adjList, visited, i);
		}
	}
}

int findComponents(vector<list<int>>& adjList,vector<bool>& visited,vector<int>& components) {
	int component_count = 0;
	for (int i = 0; i < adjList.size(); i++) {
		if (!visited[i]) {
			component_count++;
			dfs(adjList, visited, i);
		}
	}
	return component_count;
}

int main() {
	int size = 18;
	vector<list<int>> graph(size);
	init_graph(graph);
	vector<bool> visited(size);
	vector<int> components(size);

	cout << findComponents(graph, visited, components);

	return 0;
}