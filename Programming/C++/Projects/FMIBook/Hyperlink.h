#ifndef __IMAGE__HEADER__
#define __IMAGE__HEADER__
#include "Tag.h"

class Hyperlink :public Tag
{
private:
	char* link;
	char* content;
public:
	Hyperlink(const char*,const char*,const char*);
	Hyperlink(const Hyperlink&);
	Hyperlink&operator=(const Hyperlink&);
	~Hyperlink();

	virtual void writeTag(std::ofstream&) override;
	virtual Tag* clone() const override;
	virtual void print() override;
};

#endif // !__IMAGE__HEADER__
