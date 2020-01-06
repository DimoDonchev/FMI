#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "TagCollection.h"



void TagCollection::copyFrom(const TagCollection& other)
{
	size = other.size;
	cap = other.cap;
	try { Tags = new Tag*[other.size]; }
	catch (std::bad_alloc & e) { 
		std::cout << "not enough memory to make copy\n"; 
		throw; 
	}
	for (unsigned int i = 0; i < other.cap; i++)
	{
		Tags[i] = other.Tags[i]->clone();
	}
}

void TagCollection::resize()
{
	Tag ** temp = new (std::nothrow)Tag*[2 * cap];
	if (!temp) {
		std::cout << "not enough memory\n";
		return;
	}
	for (unsigned int i = 0; i < size; i++)
	{
		temp[i] = Tags[i];
	}

	cap *= 2;

	delete[] Tags;
	Tags = temp;
}

void TagCollection::clear()
{
	for (unsigned int i = 0; i < size; i++) {
		delete Tags[i];
	}
	delete[] Tags;
	Tags = nullptr;
}

TagCollection::TagCollection()
	:size(0), cap(2)
{
	try {
		Tags = new Tag*[cap];
	}
	catch (std::bad_alloc & e) {
		std::cout << "not enough memory to create TagCollection\n";
		throw;
	}
}
TagCollection::TagCollection(const TagCollection & other)
{
	copyFrom(other);
}

TagCollection & TagCollection::operator=(const TagCollection & other)
{
	if (this != &other) {
		clear();
		copyFrom(other);
	}
	return *this;
}


TagCollection::~TagCollection()
{
	clear();
}


void TagCollection::addTag(Tag * newTag)
{
	if (!newTag) {
		std::cout << "not enough memory to make new post\n";
		return;
	}

	if(Tags==nullptr){
		Tags = new Tag*[cap];
	}

	if (size >= cap)
	{
		resize();
	}


	Tags[size] = newTag;
	size++;
}

void TagCollection::removeTag(char * desc)	
{	
	for (unsigned int i = 0; i < size; i++) {
		if (!strcmp(Tags[i]->getDescription(), desc)) {//if it finds a tag with such description we delete it and make every pointer after that to point to the next Tag
			delete Tags[i];
			for (int j = i; j < size - 1; j++) {
				Tags[j] = Tags[j + 1];
			}
			size -= 1;
			return;
		}
	}
	std::cout << "could not find Tag with such description\n";
}

void TagCollection::print()
{
	std::cout << "<!DOCTYPE html>\n<html>\n<head> </head>\n<body>\n";
	for (int i = 0; i < size; i++) {
		Tags[i]->print();
		std::cout << "\n<br>\n";
	}
	std::cout << "</body>\n</html>\n";
}

void TagCollection::write(std::ofstream & out)
{
	if (size == 0)return;
	for (int i = 0; i < size; i++) {
		Tags[i]->writeTag(out);
		out << "\n<br>\n";
	}
}

void TagCollection::moveTo( int pos, char * desc)
{
	if (pos < 0) {
		std::cout << "Please enter a valid position\n";
		return;
	}

	int from = -1;
	for (int i = 0; i < size; i++) {
		if(!strcmp(Tags[i]->getDescription(),desc)){
			from = i;
			break;
		}
	}

	if (from < 0) {
		std::cout << "could not find Tag with such description\n";
		return;
	}

	if (from > pos) {
		Tag* temp = Tags[from];
		for (int i = from; i > pos; i--) {
			Tags[i] = Tags[i - 1];
		}
		Tags[pos] = temp;
	}
	else if (from < pos) {
		Tag* temp = Tags[from];
		for (int i = from; i > pos; i++) {
			Tags[i] = Tags[i + 1];
		}
		Tags[pos] = temp;
	}
	else {
		std::cout << "This Tag is already in that position\n";
	}
}
