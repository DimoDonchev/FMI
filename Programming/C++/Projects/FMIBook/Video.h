#ifndef __VIDEO__HEADER__
#define __VIDEO__HEADER__
#include "Tag.h"

class Video :public Tag
{
private:
	char* link;
public:
	Video(const char*, const char*);
	Video(const Video&);
	Video&operator=(const Video&);
	~Video();

	virtual void writeTag(std::ofstream&) override;
	virtual Tag* clone() const override;
	virtual void print() override;
};

#endif // !__VIDEO__HEADER__
