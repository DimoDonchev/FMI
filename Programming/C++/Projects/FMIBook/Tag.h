#ifndef __TAG__HEADER__
#define __TAG__HEADER__
#include <fstream>
class Tag
{
	protected:

	char * descr;
	
public:
	Tag();
	Tag(const char*);
	Tag(const Tag&);
	Tag&operator=(const Tag&);
	virtual ~Tag();

	char* getDescription();
	virtual bool isContainer();
	virtual bool removeTag(const char *);
	virtual void addTag(Tag * newTag);
	virtual void addTag(const char * tagType);
	virtual void addTags(std::ifstream&);
	virtual bool addToDiv(const char *devdesc, const char * tagType);
	virtual bool findTag(const char * desc, Tag *& temp);
	virtual Tag& getTag();
	virtual bool insert(int& search, int pos, Tag* temp);

	virtual void writeTag(std::ofstream&) = 0;
	virtual Tag* clone() const = 0;
	virtual void print() = 0;
};



#endif // !__TAG__HEADER__
