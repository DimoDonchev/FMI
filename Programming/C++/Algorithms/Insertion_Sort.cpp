#include <iostream>
#include <vector>
using namespace std;

void Insertion_Sort(vector<int>& arr) {
	for (int i = 1; i < arr.size(); i++) {
		int key = arr[i];//we pick a card
		int j = i - 1;
		while (j >= 0 && arr[j] > key) {//shift the cards to the right to make space for our card
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;//put the card in
	}
}

int main() {
	vector<int> arr = { 4, 9, 10, 17, 14, 15, 20, 3, 13, 7 };
	Insertion_Sort(arr);

	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i]<<" ";
	}

	return 0;
}