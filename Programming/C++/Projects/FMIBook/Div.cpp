#define _CRT_SECURE_NO_WARNINGS
#include "Div.h"

#include <iostream>


void Div::copyFrom(const Div & other)
{
	descr = new char[strlen(other.descr) + 1];
	strcpy(descr, other.descr);

	size = other.size;
	cap = other.cap;
	try { content = new Tag*[other.size]; }
	catch (std::bad_alloc & e) {
		std::cout << "not enough memory to make copy\n";
		throw;
	}
	for (int i = 0; i < other.size; i++)
	{
		content[i] = other.content[i]->clone();
	}
}

void Div::resize()
{
	Tag ** temp = new (std::nothrow)Tag*[2 * cap];
	if (!temp) {
		std::cout << "not enough memory\n";
		return;
	}
	for (int i = 0; i < size; i++)
	{
		temp[i] = content[i];
	}

	cap *= 2;

	delete[] content;
	content = temp;
}

Div::Div(const char * desc)
	:Tag(desc), size(0), cap(2)
{
	{
		try {
			content = new Tag*[cap];
		}
		catch (std::bad_alloc & e) {
			std::cout << "not enough memory to create TagCollection\n";
			throw;
		}
	}
}

Div::Div(const Div& other)
{
	copyFrom(other);
}

Div & Div::operator=(const Div& other)
{
	if (this != &other) {
		clear();
		copyFrom(other);
	}
	return *this;
}


Div::~Div()
{
	clear();
}

bool Div::isContainer()
{
	return true;
}

bool Div::removeTag(const char * desc)
{
	for (int i = 0; i < size; i++) {//we look for the tag in the container
		if (!strcmp(content[i]->getDescription(), desc)) {
			delete content[i];
			int newsize = size - 1;
			for (int j = i; j < newsize; j++) {
				content[j] = content[j + 1];
			}
			size =newsize;
			return 1;
		}
	}
	for (int i = 0; i < size; i++) {// if we dont find the tag in the container we look for the tag in the containers of the container
		if (content[i]->isContainer()) {
			if (content[i]->removeTag(desc)) {
				return 1;
			}
		}
	}
	return 0;
}


void Div::clear()
{
	for (int i = 0; i < size; i++) {
		delete content[i];
	}
	delete[] content;
}

void Div::writeTag(std::ofstream & out)
{
	out << "<div descr=" << '"' << descr << '"' << ">\n";
	for (int i = 0; i < size; i++) {
		content[i]->writeTag(out);
		out << "\n<br>\n";
	}
	out << "</div>\n";
}

Tag * Div::clone() const
{
	return new Div(*this);
}

void Div::print()
{
	std::cout << " <div descr=" << '"' << descr << '"' << ">\n";
	for (int i = 0; i < size; i++) {
		std::cout << "	";
		content[i]->print();
		std::cout << "\n";
	}
	std::cout << " </div>";
}

bool Div::findTag(const char * desc,Tag *& temp)
{
	for (int i = 0; i < size; i++) {//we search the div
		if (!strcmp(content[i]->getDescription(), desc)) {
			temp = content[i]->clone();
			return 1;
		}
	}
	for (int i = 0; i < size; i++) {//we search in the divs of the div
		if (content[i]->isContainer()) {
			return content[i]->findTag(desc, temp);
		}
	}
	return 0;
}

bool Div::insert(int& search, int pos, Tag * temp)
{
	for (int i = 0; i < size; i++) {
		search++;
		if (search == pos) {
			if (size >= cap)resize();
			for (int j = size ; j > i; j--) {
				content[j] = content[j - 1];
			}
			content[i]=temp;
			size++;
			return 1;
		}
		if (content[i]->isContainer()) {
			return content[i]->insert(search, pos, temp);
		}
	}
	return 0;
}

void Div::addTag(Tag * newTag)
{
	if (!newTag) {
		std::cout << "not enough memory to make new post\n";
		return;
	}

	if (content == nullptr) {
		content = new Tag*[cap];
	}

	if (size >= cap)
	{
		resize();
	}


	content[size] = newTag;
	size++;
}

void Div::addTag(const char * tagType)
{
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
		addTag(new Heading(desc, content, size));
	}
	else if (!strcmp(tagType, "paragraph")) {
		char desc[64];
		char content[128];
		std::cout << "Enter Description:";
		std::cin.getline(desc, 64);
		std::cout << "Enter Content:";
		std::cin.getline(content, 128);
		addTag(new Paragraph(desc, content));
	}
	else if (!strcmp(tagType, "hyperlink")) {
		char desc[64];
		char link[64];
		char content[128];
		std::cout << "Enter Description:";
		std::cin.getline(desc, 64);
		std::cout << "Enter Link:";
		std::cin.getline(link, 64);
		std::cout << "Enter Content:";
		std::cin.getline(content, 128);
		addTag(new Hyperlink(desc, link, content));
	}
	else if (!strcmp(tagType, "picture")) {
		char desc[64];
		char path[64];
		std::cout << "Enter Description:";
		std::cin.getline(desc, 64);
		std::cout << "Enter Path:";
		std::cin.getline(path, 64);
		addTag(new Picture(desc, path));
	}
	else if (!strcmp(tagType, "video")) {
		char desc[64];
		char link[64];
		std::cout << "Enter Description:";
		std::cin.getline(desc, 64);
		std::cout << "Enter Link:";
		std::cin.getline(link, 64);
		addTag(new Video(desc, link));
	}
	else if (!strcmp(tagType, "div")) {
		char desc[64];
		std::cout << "Enter Description:";
		std::cin.getline(desc, 64);
		addTag(new Div(desc));
	}
	else {
		std::cout << "No such Tag type exists\n";
	}

}

bool Div::addToDiv(const char * devdesc, const char * tagType)
{
	for (int i = 0; i < size; i++) {//if it finds the div inside his content
		if (content[i]->isContainer()) {
			if (!strcmp(content[i]->getDescription(), devdesc)) {
				content[i]->addTag(tagType);
				return 1;
			}
		}
	}
	for (int i = 0; i < size; i++) {//it looks inside the divs inside his content
		if (content[i]->isContainer()) {
			if (content[i]->addToDiv(devdesc, tagType)) {
				return 1;
			}
		}
	}
	return 0;
}

void Div::addTags(std::ifstream & in)
{
	char buffer[1024];
	do {
		in.getline(buffer,1024);
		if (!strncmp(buffer, "<h", 2) && ((strncmp(buffer, "<he", 3)) && (strncmp(buffer, "<ht", 3)))) {//if it start with <h but it is not <head or <html (its ugly i know)
			char description[64];
			char text[128];
			addTag(new Heading(findDescription(buffer, description), findContent(buffer, text), buffer[2]));
		}
		else if (!strncmp(buffer, "<p", 2)) {
			char description[64];
			char content[128];
			addTag(new Paragraph(findDescription(buffer, description), findContent(buffer, content)));
		}
		else if (!strncmp(buffer, "<img", 4)) {
			char description[64];
			char path[64];
			addTag(new Picture(findDescription(buffer, description), findPath(buffer, path)));
		}
		else if (!strncmp(buffer, "<iframe", 7)) {
			char description[64];
			char path[64];
			addTag(new Video(findDescription(buffer, description), findPath(buffer, path)));
		}
		else if (!strncmp(buffer, "<a", 2)) {
			char description[64];
			char link[64];
			char content[128];
			addTag(new Hyperlink(findDescription(buffer, description), findLink(buffer, link), findContent(buffer, content)));
		}
		else if (!strncmp(buffer, "<div", 4)) {
			char description[64];
			addTag(new Div(findDescription(buffer, description)));
				getTag().addTags(in);
			
		}

	} 
	while (strcmp(buffer, "</div>"));
}

Tag & Div::getTag()
{
	return *content[size - 1];
}




