#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Tag.h"



Tag::Tag()
{
	descr = nullptr;
}

Tag::Tag(const char * cdesc)
{
	descr = new char[strlen(cdesc) + 1];
	strcpy(descr, cdesc);
}

Tag::Tag(const Tag & other)
{
	descr = new char[strlen(other.descr) + 1];
	strcpy(descr, other.descr);
}

Tag & Tag::operator=(const Tag & other)
{
	if (this != &other) {
		delete[] descr;
		descr = new char[strlen(other.descr) + 1];
		strcpy(descr, other.descr);
	}
	return *this;
}


Tag::~Tag()
{
	delete[] descr;
}

char * Tag::getDescription()
{
	return descr;
}
