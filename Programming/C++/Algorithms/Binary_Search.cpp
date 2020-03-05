#include <iostream>
#include <vector>
using namespace std;


int Binary_Search_Iterative(const vector<int>& arr, int key) {
	int left = 0;
	int right = arr.size();
	while (left <= right) {
		int mid = (left + right) / 2;
		if (arr[mid] == key) return mid;
		else if (key < arr[mid]) right = mid - 1;
		else left = mid + 1;
	}
	return -1;
}


int Binary_Search_Recursive_Wrap(const vector<int>& arr, int key,int left ,int right) {
	if (left > right) return -1;
	else {
		int mid = (left + right) / 2;
		if (arr[mid] == key)return mid;
		else if (key < arr[mid]) return Binary_Search_Recursive_Wrap(arr, key, left, mid - 1);
		else return Binary_Search_Recursive_Wrap(arr, key, mid + 1, right);
	}
}

int Binary_Search_Recursive(const vector<int>& arr, int key) {
	int left = 0;
	int right = arr.size();
	return Binary_Search_Recursive_Wrap(arr, key, left, right);
}

int main() {
	vector<int> array = { 1,2,3,4,5,6,7,8,10,12,56,102,250,400 };

	cout << "what is the position of element 10 in the array?\n" << Binary_Search_Iterative(array, 10)<<endl;

	cout << "what is the position of element 102 in the array?\n" << Binary_Search_Recursive(array, 102)<<endl;

	return 0;
}