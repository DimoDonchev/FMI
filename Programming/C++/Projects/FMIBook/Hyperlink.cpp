#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Hyperlink.h"

Hyperlink::Hyperlink(const char *descr, const char *clink, const char *ccontent)
	:Tag(descr)
{
	try {
		link = new char[strlen(clink) + 1];
		strcpy(link, clink);

		content = new char[strlen(ccontent) + 1];
		strcpy(content, ccontent);
	}
	catch (std::bad_alloc & e) {
		std::cout << "not enough memory to make copy\n";
		throw;
	}
}

Hyperlink::Hyperlink(const Hyperlink & other)
	:Tag(other)
{
	try {
		link = new char[strlen(other.link) + 1];
		strcpy(link, other.link);

		content = new char[strlen(other.content) + 1];
		strcpy(content, other.content);
	}
	catch (std::bad_alloc & e) {
		std::cout << "not enough memory to make copy\n";
		throw;
	}
}

Hyperlink & Hyperlink::operator=(const Hyperlink & other)
{
	if (this != &other) {
		delete[] descr;
		delete[] link;
		delete[] content;

		descr = new char[strlen(other.descr) + 1];
		strcpy(descr, other.descr);

		link = new char[strlen(other.link) + 1];
		strcpy(link, other.link);

		content = new char[strlen(other.content) + 1];
		strcpy(content, other.content);
	}
	return *this;
}

Hyperlink::~Hyperlink()
{
	delete[] link;
	delete[] content;
}

void Hyperlink::writeTag(std::ofstream & out)
{
	out << "<a href="<<'"' << link << '"'<<" descr="<<'"' << descr << '"'<<">" << content << "</a>";
}

Tag * Hyperlink::clone() const
{
	return new Hyperlink(*this);
}

void Hyperlink::print()
{
	std::cout << "a href=\"" << link << "\" descr=\"" << descr << "\">" << content << "</a>";
}
