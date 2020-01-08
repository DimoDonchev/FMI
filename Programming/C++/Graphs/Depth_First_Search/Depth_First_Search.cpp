#include <iostream>
#include <vector>
#include <list>
using namespace std;

void init_graph(vector<list<int>>& G) {
	G[0].push_back(9);
	G[1].push_back(0);
	G[3].push_back(2);
	G[3].push_back(4);
	G[3].push_back(5);
	G[5].push_back(6);
	G[6].push_back(7);
	G[7].push_back(3);
	G[7].push_back(10);
	G[8].push_back(7);
	G[8].push_back(1);
	G[9].push_back(8);
	G[10].push_back(11);
	G[11].push_back(7);
}

void dfs(vector<list<int>>& adjList,vector<bool>& visited, int node) {
	if (visited[node])return;
	else {
		visited[node] = true;
		cout << "Node:" << node << " visited\n";
		int neighbours_size = adjList[node].size();
		for (auto i : adjList[node]) {//for each element of the list
			dfs(adjList, visited, i);
		}
		/*
		//you can use an iterator 
		for (auto i = adjList[node].begin(); i != adjList[node].end(); i++) {
			dfs(adjList, visited, *i);
		}
		*/
	}
}

int main() {
	int size = 12;
	vector<list<int>> graph(size);
	init_graph(graph);
	vector<bool> visited(size);

	dfs(graph, visited, 0);

	return 0;
}