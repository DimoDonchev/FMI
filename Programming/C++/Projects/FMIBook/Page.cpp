#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Page.h"
#include "utils.h"


const int MAX_BUFFER_LENGTH = 1024;



Page::Page()
{
	filename = nullptr;
}


Page::~Page()
{
	delete[] filename;
}

void Page::clear()
{
	delete[] filename;
	collection.clear();
}


void Page::load(char * rhsfilename)
{
		if (!rhsfilename) {
			std::cout << "Invalid filename\n";
			return;
		}

	char * filepath = new char[strlen(rhsfilename) + strlen(".html") + 1];
	strcpy(filepath, rhsfilename);;
	strcat(filepath, ".html");
	if (filename != nullptr) {
		if (!strcmp(filename, filepath)) 
		{
			return;
		}
	}
		this->clear();


		filename = new char[strlen(filepath) + 1];
		strcpy(filename, filepath);

		std::ifstream in(filename);
		if (!in) {//if file does not exist we create one
			std::ofstream out(filename, std::ios::trunc);
			out.close();
			return;
		}
		char buffer[MAX_BUFFER_LENGTH];


		while (!in.eof())
		{
			in.getline(buffer, MAX_BUFFER_LENGTH);
			if (!strncmp(buffer, "<h", 2) && ((strncmp(buffer, "<he", 3)) && (strncmp(buffer, "<ht", 3)))) {//if it start with <h but it is not <head or <html (its ugly i know)
				char description[64];
				char content[128];
				collection.addTag(new Heading(findDescription(buffer, description), findContent(buffer, content), buffer[2]));
			}
			else if (!strncmp(buffer, "<p", 2)) {
				char description[64];
				char content[128];
				collection.addTag(new Paragraph(findDescription(buffer, description), findContent(buffer, content)));
			}
			else if (!strncmp(buffer, "<img", 4)) {
				char description[64];
				char path[64];
				collection.addTag(new Picture(findDescription(buffer, description), findPath(buffer, path)));
			}
			else if (!strncmp(buffer, "<iframe", 7)) {
				char description[64];
				char path[64];
				collection.addTag(new Video(findDescription(buffer, description), findPath(buffer, path)));
			}
			else if (!strncmp(buffer, "<a", 2)) {
				char description[64];
				char link[64];
				char content[128];
				collection.addTag(new Hyperlink(findDescription(buffer, description), findLink(buffer, link), findContent(buffer, content)));
			}
			else if (!strncmp(buffer, "<div", 4)) {
				char description[64];
				collection.addTag(new Div(findDescription(buffer, description)));
				collection.getTag().addTags(in);

			}
			else {
				continue;
			}

		}
		in.close();
	
	return;

	
}

void Page::addTag()
{
	char tagType[16];
	std::cout << "Enter Tag Type:";
	std::cin >> tagType;

	if (!strcmp(tagType, "heading")) {
		char size;
		char desc[64];
		char content[128];
		std::cout << "Enter Heading Size:";
		std::cin >> size;
		std::cin.ignore();
		std::cout << "Enter Description:";
		std::cin.getline(desc, 64);
		std::cout << "Enter Content:";
		std::cin.getline(content, 128);
		collection.addTag(new Heading(desc, content, size));
	}
	else if (!strcmp(tagType, "paragraph")) {
		char desc[64];
		char content[128];
		std::cin.ignore();
		std::cout << "Enter Description:";
		std::cin.getline(desc, 64);
		std::cout << "Enter Content:";
		std::cin.getline(content, 128);
		collection.addTag(new Paragraph(desc, content));
	}
	else if (!strcmp(tagType, "hyperlink")) {
		char desc[64];
		char link[64];
		char content[128];
		std::cin.ignore();
		std::cout << "Enter Description:";
		std::cin.getline(desc, 64);
		std::cout << "Enter Link:";
		std::cin.getline(link, 64);
		std::cout << "Enter Content:";
		std::cin.getline(content, 128);
		collection.addTag(new Hyperlink(desc,link ,content));
	}
	else if (!strcmp(tagType, "picture")) {
		char desc[64];
		char path[64];
		std::cin.ignore();
		std::cout << "Enter Description:";
		std::cin.getline(desc, 64);
		std::cout << "Enter Path:";
		std::cin.getline(path, 64);
		collection.addTag(new Picture(desc, path));
	}
	else if (!strcmp(tagType, "video")) {
		char desc[64];
		char link[64];
		std::cin.ignore();
		std::cout << "Enter Description:";
		std::cin.getline(desc, 64);
		std::cout << "Enter Link:";
		std::cin.getline(link, 64);
		collection.addTag(new Video(desc, link));
	}
	else if (!strcmp(tagType, "div")) {
		char desc[64];
		std::cin.ignore();
		std::cout << "Enter Description:";
		std::cin.getline(desc, 64);
		collection.addTag(new Div(desc));
	}
	else {
		std::cout << "No such Tag type exists\n";
	}
}

void Page::removeTag()
{
	char desc[64];
	std::cin.ignore();
	std::cout << "Enter tag description:";
	std::cin.getline(desc,64);
	collection.removeTag(desc);
}

void Page::print()
{
	collection.print();
}

void Page::moveTo()
{
	int pos;
	char desc[64];
	std::cin >> pos;
	std::cin >> desc;
	pos--;
	collection.moveTo(pos, desc);
}

void Page::save()
{

	if (filename == nullptr) {
		std::cout << "There's nothing to save\n";
		return;
	}
	std::ofstream out(filename);
	if (!out) {
		std::cout << "could not open file\n";
	}

	out << "<!DOCTYPE html>\n<html>\n<head> </head>\n<body>\n";
	collection.write(out);
	out << "</body>\n</html>";
	out.close();
}

void Page::addToDiv()
{
	std::cin.ignore();
	std::cout << "Enter Tag Type:";
	char tagType[16];
	std::cin.getline(tagType, 16);
	collection.addToDiv(tagType);
}


