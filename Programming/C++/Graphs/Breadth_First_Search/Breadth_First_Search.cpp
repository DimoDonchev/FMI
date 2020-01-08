#include <iostream>
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

void bfs(vector<list<int>>& adjList, int startingPoint) {
	int const size = adjList.size();
	vector<bool> visited(size);
	queue<int> wave;
	wave.push(startingPoint);

	while (!wave.empty()) {//for each element in the queue
		visited[wave.front()] = true;//mark it as visited
		for (auto i : adjList[wave.front()]) {//add their neighbours to the bottom of the queue
			if (!visited[i]) {
				cout << wave.front() << " goes to " << i << endl;
				wave.push(i);
			}
		}
		wave.pop();//remove it from the top of the queue
	}

}

int main() {
	int size = 13;
	vector<list<int>> graph(size);
	init_graph(graph);

	bfs(graph, 0);

	return 0;
}