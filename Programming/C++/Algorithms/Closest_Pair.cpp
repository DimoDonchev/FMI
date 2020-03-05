#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

//Task: Find the pair of the two closest in value elements in an array
//Complexity: 0(n.log(n))

pair<int, int> Closest_Pair(vector<int> arr) {
	sort(arr.begin(),arr.end());//n.log(n) complexity
	int closest = INT_MAX;
	int first, second;
	for (int i = 0; i < arr.size()-1; i++) {
		if (arr[i + 1] - arr[i] < closest) {
			closest = arr[i + 1] - arr[i];
			first = arr[i];
			second = arr[i + 1];
		}
	}
	return make_pair(first, second);
}



int main() {
	vector<int> arr = { 1,5,12,187,24534,12321,345,32,546,456,123,789,8 };
	pair<int, int> pair = Closest_Pair(arr);
	cout << "Closest Pair is: (" << pair.first << "," << pair.second << ")" << endl;

	return 0;
}