#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Video.h"




Video::Video(const char * descr, const char *clink)
	:Tag(descr)
{
	try {
		link = new char[strlen(clink) + 1];
		strcpy(link, clink);
	}
	catch (std::bad_alloc & e) {
		std::cout << "not enough memory to make copy\n";
		throw;
	}
}

Video::Video(const Video &other)
	:Tag(other)
{
	try {
		link = new char[strlen(other.link) + 1];
		strcpy(link, other.link);
	}
	catch (std::bad_alloc & e) {
		std::cout << "not enough memory to make copy\n";
		throw;
	}
}

Video & Video::operator=(const Video & other)
{
	if (this != &other) {
		delete[] link;
		delete[] descr;

		descr = new char[strlen(other.descr) + 1];
		strcpy(descr, other.descr);

		link = new char[strlen(other.link) + 1];
		strcpy(link, other.link);
	}
	return *this;
}

Video::~Video()
{
	delete[] link;
}

void Video::writeTag(std::ofstream & out)
{
	
	out << "<iframe src=" << '"' << link << '"' << " descr="<<'"'<< descr <<'"' <<">" << "</iframe>";
}

Tag * Video::clone() const
{
	return new Video(*this);
}

void Video::print()
{
	std::cout << "<iframe src=\"" << link << "\"" << " descr=\"" << descr << "\">" << "</iframe>";
}
