#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Tag.h"



Tag::Tag()
{
	descr = nullptr;
}

Tag::Tag(const char * cdesc)
{
	try {
		descr = new char[strlen(cdesc) + 1];
		strcpy(descr, cdesc);
	}
	catch (std::bad_alloc & e) {
		std::cout << "not enough memory to make copy\n";
		throw;
	}
}

Tag::Tag(const Tag & other)
{
	try {
		descr = new char[strlen(other.descr) + 1];
		strcpy(descr, other.descr);
	}
	catch (std::bad_alloc & e) {
		std::cout << "not enough memory to make copy\n";
		throw;
	}
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

bool Tag::isContainer()
{
	return false;
}

bool Tag::removeTag(const char *)
{
	return false;
}


void Tag::addTag(Tag * newTag)
{
}

void Tag::addTag(const char * tagType)
{
}

void Tag::addTags(std::ifstream &)
{
}

bool Tag::addToDiv(const char * devdesc, const char * tagType)
{
	return false;
}

bool Tag::findTag(const char * desc,Tag *& temp)
{
	return this;
}

Tag & Tag::getTag()
{
	return *this;
}

bool Tag::insert(int& search, int pos, Tag * temp)
{
	return false;
}



