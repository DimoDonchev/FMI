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
	for (int i = 0; i < other.cap; i++)
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
	for (int i = 0; i < size; i++)
	{
		temp[i] = Tags[i];
	}

	cap *= 2;

	delete[] Tags;
	Tags = temp;
}

void TagCollection::clear()
{
	for ( int i = 0; i < size; i++) {
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
	for (int i = 0; i < size; i++) {
		if (!strcmp(Tags[i]->getDescription(), desc)) {//if it finds a tag with such description we delete it and make every pointer after that to point to the next Tag
			delete Tags[i];
			int newsize = size - 1;
			for (int j = i; j < newsize; j++) {
				Tags[j] = Tags[j + 1];
			}
			Tags[newsize] = nullptr;
			size =newsize;
			return;
		}
	}
	for (int i = 0; i < size; i++) {//if we havent found the tag we search for it in the containers
		if (Tags[i]->isContainer()) {
			if (Tags[i]->removeTag(desc)) {
				return;
			}
			
		}
	}
	std::cout << "could not find Tag with such description\n";
}

void TagCollection::print()
{
	if (size > 0) {
		for (int i = 0; i < size; i++) {
			Tags[i]->print();
			std::cout << "\n";
		}
	}
	else return;
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
		std::cout << "Not a valid position\n";
		return;
	}

	Tag * temp=nullptr;
	for (int i = 0; i < size; i++) {
		if (!strcmp(Tags[i]->getDescription(), desc)) {
			temp = Tags[i]->clone();
			break;
		}
		if (Tags[i]->isContainer()) {
			if (Tags[i]->findTag(desc, temp)) {
				break;
			}
		}
	}

	if (temp == nullptr) {
		std::cout << "could not find tag with such description\n";
		return;
	}

	removeTag(desc);

	int search = 0;
	for (int i = 0; i < size; i++) {
		if (search == pos) {
			insert(temp, i);
			return;
		}
		if (Tags[i]->isContainer()) {
			if (Tags[i]->insert(search, pos, temp)) {
				return;
			}
		}
		search++;
	}

	//if we reach to here this means that pos>size
	//in that case we just insert it at the end
	insert(temp, size);
}

void TagCollection::insert(Tag * tag, int pos)
{
	if (size >= cap)resize();
	for (int i = size; i > pos; i--) {
		Tags[i] = Tags[i - 1];
	}
	Tags[pos] = tag;
	size++;
	return;
}

Tag & TagCollection::getTag()
{
	return *Tags[size - 1];
}

void TagCollection::addToDiv(const char * tagType)
{
	char divdesc[64];
	std::cout << "Enter Div description:";
	std::cin.getline(divdesc,64);
	for (int i = 0; i < size; i++) {//if it is a container we check if its descr==devdesc
		if (Tags[i]->isContainer()) {
			if (!strcmp(Tags[i]->getDescription(),divdesc)) {
				Tags[i]->addTag(tagType);
				return;
			}

		}
	}
	//if the div is not in the main page then it must be in some other div
	for (int i = 0; i < size; i++) {//for every div we check if there is a div inside which descr==devdesc
		if (Tags[i]->isContainer()) {
			if (Tags[i]->addToDiv(divdesc,tagType)) {
				return;
			}
		}
	}
	std::cout << "no div with such description exists\n";
}

int TagCollection::find(int pos)
{
	return -1;
}
