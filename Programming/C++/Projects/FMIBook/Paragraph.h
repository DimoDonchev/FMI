#ifndef __PARAGRAPH__HEADER__
#define __PARAGRAPH__HEADER__
#include "Tag.h"

class Paragraph : public Tag
{
private:
	char* content;
public:
	Paragraph(const char*,const char*);
	Paragraph(const Paragraph&);
	Paragraph&operator=(const Paragraph&);
	~Paragraph();

	virtual void writeTag(std::ofstream&)override;
	virtual Tag* clone() const override;
	virtual void print() override;
};

#endif // !__PARAGRAPH__HEADER__
