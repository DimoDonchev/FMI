#ifndef __HEADING__HEADER__
#define __HEADING__HEADER__
#include "Tag.h"

class Heading :public Tag
{
private:
	char size;
	char* content;
public:
	Heading(const char *,const char *,char size);
	Heading(const Heading&);
	Heading&operator=(const Heading&);
	~Heading();

	virtual void writeTag(std::ofstream&) override;
	virtual Tag* clone() const  override;
	virtual void print() override;
};

#endif // !__HEADING__HEADER__
