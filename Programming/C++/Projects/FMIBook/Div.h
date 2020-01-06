#ifndef __DIV__HEADER__
#define __DIV__HEADER__

#include "Tag.h"
#include "Heading.h"
#include "Hyperlink.h"
#include "Paragraph.h"
#include "Picture.h"
#include "Video.h"
#include "utils.h"

class Div :	public Tag
{
private:
	Tag ** content;
	int size;
	int cap;

private:
	void copyFrom(const Div&);
	void resize();
public:

	Div(const char * );
	Div(const Div&);
	Div&operator=(const Div&);
	~Div();


	virtual bool isContainer() override;
	virtual bool removeTag(const char* ) override;
	virtual bool insert(int& search, int pos, Tag* temp) override;
	virtual bool addToDiv(const char *devdesc, const char * tagType) override;

	void clear();

	virtual void writeTag(std::ofstream&) override;
	virtual Tag* clone() const  override;
	virtual void print() override;
	virtual bool findTag(const char * desc, Tag *& temp) override;


	virtual void addTag(Tag * newTag) override;
	virtual void addTag(const char * tagType) override;
	virtual void addTags(std::ifstream&) override;
	virtual Tag& getTag() override;

};

#endif // !__DIV__HEADER__
