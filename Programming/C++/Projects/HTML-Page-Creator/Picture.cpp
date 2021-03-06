#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Picture.h"

Picture::Picture(const char * descr, const char * cpath)
	:Tag(descr)
{
	path = new char[strlen(cpath) + 1];
	strcpy(path, cpath);
}

Picture::Picture(const Picture & other)
	:Tag(other)
{
	path = new char[strlen(other.path) + 1];
	strcpy(path, other.path);
}

Picture & Picture::operator=(const Picture & other)
{
	if (this != &other) {
		delete[] path;
		delete[] descr;

		descr = new char[strlen(other.descr) + 1];
		strcpy(descr, other.descr);

		path = new char[strlen(other.path) + 1];
		strcpy(path, other.path);
	}
	return *this;
}

Picture::~Picture()
{
	delete[] path;
}

void Picture::writeTag(std::ofstream &out)
{
	out << "<img src="<<'"' << path << '"' <<" descr=" << '"' << descr << '"' << ">";
}

Tag * Picture::clone() const
{
	return new Picture(*this);
}

void Picture::print()
{
	std::cout << "img src=\"" << path << "\" descr=\"" << descr << "\">";
}
