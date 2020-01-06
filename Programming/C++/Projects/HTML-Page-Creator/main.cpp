#include <iostream>
#include "Page.h"
using namespace std;

void help() {
	cout << "commands:\nload <filename>\nadd <tagtype>\nprint\nremove\nmoveTo <position> <desription>\nsave\nexit\n";
	cout << "tagtypes:heading paragraph video hyperlink picture\n";
}

const int MAX_BUFFER_LENGTH = 1024;
int main() {

	Page page;
	char buffer[MAX_BUFFER_LENGTH];


	for (;;) {
		cout << "Enter command:";
		cin >> buffer;
		cout << "\n";

		if (!strcmp(buffer, "load")) {
			char filename[64];
			cin >> filename;
			page.load(filename);
		}
		else if (!strcmp(buffer, "add"))
			page.addTag();
		else if (!strcmp(buffer, "remove"))
			page.removeTag();
		else if (!strcmp(buffer, "print"))
			page.print();
		else if (!strcmp(buffer, "moveTo"))
			page.moveTo();
		else if (!strcmp(buffer, "save"))
			page.save();
		else if (!strcmp(buffer, "help"))
			help();
		else if (!strcmp(buffer, "exit")) {
			page.save();
			return 0;
		}
			
		else {
			cout << "Unknown command!\nWrite command help to see commands\n";

			cin.ignore(INT_MAX, '\n');
		}

	}

	return 0;
}