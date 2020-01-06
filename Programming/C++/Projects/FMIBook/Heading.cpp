#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Heading.h"



Heading::Heading(const char* cdesc,const char * ccontent,char csize)
	:Tag(cdesc)
{
	try {
		content = new char[strlen(ccontent) + 1];
		strcpy(content, ccontent);
		if (csize > '6')csize = '6';//the largest heading is 6
		size = csize;
	}
	catch (std::bad_alloc & e) {
		std::cout << "not enough memory to make copy\n";
		throw;
	}
}

Heading::Heading(const Heading & other)
	:Tag(other)
{
	try {
		content = new char[strlen(other.content) + 1];
		strcpy(content, other.content);
		size = other.size;
	}
	catch (std::bad_alloc & e) {
		std::cout << "not enough memory to make copy\n";
		throw;
	}
}

Heading & Heading::operator=(const Heading & other)
{
	if (this != &other) {
		delete[] content;
		delete[] descr;

		descr = new char[strlen(other.descr) + 1];
		strcpy(descr, other.descr);

		content = new char[strlen(other.content) + 1];
		strcpy(content, other.content);

		size = other.size;
	}

	return *this;
}


Heading::~Heading()
{
	delete[] content;
}

void Heading::writeTag(std::ofstream & out)
{
	out << "<h"<<size<<" descr="<<'"'<<descr<<'"'<<">"<< content << "</h"<<size<<">";
}

Tag * Heading::clone() const
{
	return new Heading(*this);
}

void Heading::print()
{
	std::cout << "<h" << size << " descr=\"" << descr << "\">" << content << "</h" << size << ">";
}
