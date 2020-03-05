#include <iostream>
using namespace std;

int Euclid_Iterative(int a, int b) {
	while (a % b > 0) {
		int r = a % b;
		a = b;
		b = r;
	}
	return b;
}

int Euclid_Recursive(int a, int b) {
	if (a % b == 0) return b;
	else return Euclid_Recursive(b, a%b);
}


int main() {
	cout << "Greatest Common Divider of 54 and 24 is: " << Euclid_Iterative(54, 24) << endl;
	cout << "Greatest Common Divider of 256 and 2048 is: " << Euclid_Recursive(256, 2048) << endl;
	return 0;
}