#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Page.h"


const int MAX_BUFFER_LENGTH = 1024;

char* getContent(const char* buffer,char * content) {
	int i = 0;
	while (buffer[i] != '>') {
		i++;
	}
	i++;
	int start = i;
	while (buffer[i] != '<' && i < 127) {
		content[i - start] = buffer[i];
		i++;
	}
	content[i - start] = '\0';
	return content;
}

char* getDescription(const char* buffer,char * description) {
	int i = 0;
	while (buffer[i] != 'r' || buffer[i+1]!='=' || buffer[i+2]!='"') {//find the start of descr=" 
		i++;
	}
	i=i+3;
	int start = i;
	while (buffer[i] != '"' && start-i < 63) {
		description[i - start] = buffer[i];
		i++;
	}
	description[i - start] = '\0';
	return description;
}

char * getPath(const char * buffer, char * path) {
	int i = 0;
	while (buffer[i] != 'c' && buffer[i + 1] != '=' && buffer[i + 2] != '"') {// find the start of src="
		i++;
	}
	i+=3;
	int start = i;
	while (buffer[i] != '"' && i < 64) {
		path[i - start] = buffer[i];
		i++;
	}
	path[i - start] = '\0';
	return path;
}

char * getLink(const char * buffer, char * link) {
	int i = 0;
	while (buffer[i] != 'f' && buffer[i + 1] != '=' && buffer[i + 2] != '"') {// find the start of src="
		i++;
	}
	i+=3;
	int start = i;
	while (buffer[i] != '"' && i < 64) {
		link[i - start] = buffer[i];
		i++;
	}
	link[i - start] = '\0';
	return link;
}

Page::Page()
{
	filename = nullptr;
}


Page::~Page()
{
	clear();
}

void Page::clear()
{
	delete[] filename;
	collection.clear();
}


void Page::load(char * rhsfilename)
{
	this->clear();

	if (!rhsfilename) {
		std::cout << "Invalid filename\n";
		return;
	}

	filename = new char[strlen(rhsfilename) +strlen(".html")+ 1];
	strcpy(filename, rhsfilename);
	strcat(filename, ".html");

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
		if (!strncmp(buffer, "<h", 2) && ((strncmp(buffer,"<he",3))&&(strncmp(buffer,"<ht",3)))) {//if it start with <h but it is not <head or <html (its ugly i know)
			char description[64];
			char content[128];
			collection.addTag(new Heading(getDescription(buffer,description), getContent(buffer,content), buffer[2]));
		}
		else if (!strncmp(buffer, "<p", 2)) {
			char description[64];
			char content[128];
			collection.addTag(new Paragraph(getDescription(buffer,description), getContent(buffer,content)));
		}
		else if (!strncmp(buffer, "<img", 4)) {
			char description[64];
			char path[64];
			collection.addTag(new Picture(getDescription(buffer, description), getPath(buffer,path)));
		}
		else if (!strncmp(buffer, "<iframe", 7)) {
			char description[64];
			char path[64];
			collection.addTag(new Video(getDescription(buffer, description), getPath(buffer, path)));
		}
		else if (!strncmp(buffer, "<a", 2)) {
			char description[64];
			char link[64];
			char content[128];
			collection.addTag(new Hyperlink(getDescription(buffer, description),getLink(buffer, link),getContent(buffer, content)));
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
	else {
		std::cout << "No such Tag type exists\n";
	}
}

void Page::removeTag()
{
	char desc[64];
	std::cin >> desc;
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


