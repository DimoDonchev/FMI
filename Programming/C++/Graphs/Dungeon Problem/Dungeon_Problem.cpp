#include <iostream>
#include <algorithm> //std::reverse
#include <vector>
#include <list>
#include <queue>
using namespace std;

int findExit(vector<vector<char>>& dungeon,int sr,int sc) {
	int dr[4] = {1,-1,0,0};
	int dc[4] = {0,0,1,-1};

	int rows = dungeon.size();
	int cols = dungeon[0].size();
	queue<int> rq;//row queue
	queue<int> cq;//column queue

	int move_count = 0;
	bool reached_end = false;
	vector<vector<bool>> visited(rows);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			visited[i].push_back(0);
		}
	}
		
	

	rq.push(sr);
	cq.push(sc);

	int nodes_in_current_layer = 1;
	int nodes_in_next_layer = 0;

	while (!rq.empty()) {
		int r = rq.front();
		int c = cq.front();
		visited[r][c] = true;
		rq.pop();
		cq.pop();
		

		if (dungeon[r][c] == 'E') {
			reached_end = true;
			break;
		}
		//move up,down,left,right if possible and add the new cells to the queues
		for (int i = 0; i < 4; i++) {
			int rr = r + dr[i];
			int cc = c + dc[i];

			//skip out of bounds locations
			if (rr < 0 || cc < 0)continue;
			if (rr >= rows || cc >= cols)continue;

			//skip visited locations or blocked cells
			if (visited[rr][cc])continue;
			if (dungeon[rr][cc] == '#')continue;

			//add the new cell and mark it as visited
			rq.push(rr);
			cq.push(cc);
			visited[rr][cc] = true;
			nodes_in_next_layer++;
		}
		nodes_in_current_layer--;
		if (nodes_in_current_layer==0) {
			nodes_in_current_layer = nodes_in_next_layer;
			nodes_in_next_layer = 0;
			move_count++;
		}
	}
	if (reached_end)return move_count;
	else return -1;
}

int main() {
	const int rows = 5;
	const int cols = 7;
	vector<vector<char>> dungeon = {
		{'S','.','.','#','.','.','.'},
		{'.','#','.','.','.','#','.'},
		{'.','#','.','.','.','.','.'},
		{'.','.','#','#','.','.','.'},
		{'#','.','#','E','.','#','.'}
	};

	int exit = findExit(dungeon,0,0);
	cout << exit;
	return 0;
}