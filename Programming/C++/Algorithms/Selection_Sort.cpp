#include <iostream>
#include <vector>
using namespace std;

void swap(int& a, int&b) {
	int temp = a;
	a = b;
	b = temp;
}

void Selection_Sort(vector<int>& arr) {
	for (int i = 0; i < arr.size() - 1; i++) {
		for (int j = i + 1; j < arr.size(); j++) {
			if (arr[j] < arr[i]) {
				swap(arr[j], arr[i]);
			}
		}
	}
}

int main() {
	vector<int> arr = { 4, 9, 10, 17, 14, 15, 20, 3, 13, 7 };
	Selection_Sort(arr);

	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << " ";
	}

	return 0;
}