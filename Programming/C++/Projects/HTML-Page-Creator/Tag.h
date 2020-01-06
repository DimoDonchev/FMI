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

	virtual void writeTag(std::ofstream&) = 0;
	virtual Tag* clone() const = 0;
	virtual void print() = 0;
};



#endif // !__TAG__HEADER__
