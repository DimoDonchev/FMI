#include <iostream>
#include <algorithm> //std::reverse
#include <vector>
#include <list>
#include <queue>
using namespace std;

void add_Edge(vector<list<int>>& adjList, int i, int j) {
	adjList[i].push_back(j);
	adjList[j].push_back(i);
}

void init_graph(vector<list<int>>& adjList) {
	add_Edge(adjList, 0, 9);
	add_Edge(adjList, 0, 7);
	add_Edge(adjList, 0, 11);

	add_Edge(adjList, 9, 10);
	add_Edge(adjList, 9, 8);

	add_Edge(adjList, 7, 11);
	add_Edge(adjList, 7, 6);
	add_Edge(adjList, 7, 3);

	add_Edge(adjList, 10, 1);

	add_Edge(adjList, 8, 1);
	add_Edge(adjList, 8, 12);

	add_Edge(adjList, 6, 5);

	add_Edge(adjList, 3, 2);
	add_Edge(adjList, 3, 4);

	add_Edge(adjList, 12, 2);
}


vector<int> bfs(vector<list<int>>& adjList, int startingPoint) {
	int size = adjList.size();
	vector<bool> visited(size);
	queue<int> wave;

	vector<int> prev(size);//prev[w]=u (node w is reached through u)

	wave.push(startingPoint);
	while (!wave.empty()) {//for each element in the queue
		visited[wave.front()] = true;//mark it as visited

		for (auto i : adjList[wave.front()]) {//add their neighbours to the bottom of the queue
			if (!visited[i]) {
				wave.push(i);
				prev[i] = wave.front();//for each path remember the previous node
			}
		}
		wave.pop();//remove it from the top of the queue
	}
	return prev;
}

vector<int> constructPath(int startPoint, int endPoint, vector<int>& prev) {
	vector<int> path = {};
	if (prev[endPoint] == 0) {//if Endpoint has not been reached
		return path;
	}
	else {
		for (int at = endPoint; at != 0; at = prev[at]) {//add the path from end to start (prev[start]==0)
			path.push_back(at);
		}
		reverse(path.begin(), path.end());//reverse the path so it goes from start to end
		return path;
	}
}

vector<int> bfs_shortest_path(vector<list<int>>& adjList, int startingPoint,int endPoint) {
	vector<int> prev = bfs(adjList, startingPoint);
	return constructPath(startingPoint, endPoint, prev);
}

int main() {
	int size = 13;
	vector<list<int>> graph(size);
	init_graph(graph);

	vector<int> path = bfs_shortest_path(graph, 0, 12);
	for (auto i : path) {
		cout << i << " ";
	}
	return 0;
}