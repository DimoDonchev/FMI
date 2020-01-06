#ifndef __PICTURE__HEADER__
#define __PICTURE__HEADER__
#include "Tag.h"

class Picture :	public Tag
{
private:
	char* path;
public:
	Picture(const char*, const char*);
	Picture(const Picture&);
	Picture&operator=(const Picture&);
	~Picture();

	virtual void writeTag(std::ofstream&)override;
	virtual Tag* clone() const override;
	virtual void print() override;
};

#endif // !__PICTURE__HEADER__
