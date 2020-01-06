#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Paragraph.h"



Paragraph::Paragraph(const char* descr,const char * ccontent)
	:Tag(descr)
{
	try {
		content = new char[strlen(ccontent) + 1];
		strcpy(content, ccontent);
	}
	catch (std::bad_alloc & e) {
		std::cout << "not enough memory to make copy\n";
		throw;
	}
}

Paragraph::Paragraph(const Paragraph & other)
	:Tag(other)
{
	try {
		content = new char[strlen(other.content) + 1];
		strcpy(content, other.content);
	}
	catch (std::bad_alloc & e) {
		std::cout << "not enough memory to make copy\n";
		throw;
	}
}

Paragraph & Paragraph::operator=(const Paragraph & other)
{
	if (this != &other) {
		delete[] content;
		delete[] descr;

		descr = new char[strlen(other.descr) + 1];
		strcpy(descr, other.descr);

		content = new char[strlen(other.content) + 1];
		strcpy(content, other.content);
	}
	return *this;
}


Paragraph::~Paragraph()
{
	delete[] content;
}

void Paragraph::writeTag(std::ofstream & out)
{
	out << "<p descr="<<'"' << descr << '"'<< ">" << content << "</p>";
}

Tag * Paragraph::clone() const
{
	return new Paragraph(*this);
}

void Paragraph::print()
{
	std::cout << "<p descr=\"" << descr << "\">" << content << "</p>";
}
