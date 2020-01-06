#ifndef __TAG__COLLECTION__HEADER__
#define __TAG__COLLECTION__HEADER__
#include "Tag.h"

class TagCollection
{
private:
	Tag * * Tags;
	int size;
	int cap;

private:
	void copyFrom(const TagCollection&);
	void resize();

public:
	TagCollection();
	TagCollection(const TagCollection&);
	TagCollection&operator=(const TagCollection&);
	~TagCollection();
	
	void clear();

	void addTag(Tag* newTag);
	void removeTag(char* desc);
	void print();
	void write(std::ofstream& out);
	void moveTo(int pos, char * desc);
};

#endif // !__TAG__COLLECTION__HEADER__
