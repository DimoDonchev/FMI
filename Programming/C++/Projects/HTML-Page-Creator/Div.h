#ifndef __DIV__HEADER__
#define __DIV__HEADER__

#include "Tag.h"
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
	Div();
	Div(const Div&);
	Div&operator=(const Div&);
	~Div();

	void clear();

	virtual void writeTag(std::ofstream&) override;
	virtual Tag* clone() const  override;
	virtual void print() override;

	void addTag(Tag* newTag);
	void removeTag(char * desc);


};

#endif // !__DIV__HEADER__
