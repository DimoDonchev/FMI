#ifndef __PAGE__HEADER__
#define __PAGE__HEADER__
#include "TagCollection.h"
#include "Heading.h"
#include "Hyperlink.h"
#include "Paragraph.h"
#include "Picture.h"
#include "Video.h"
#include "Div.h"

class Page
{
private:
	TagCollection collection;
	char* filename;

public:
	Page();
	~Page();

	void clear();

	void load(char * filename);
	void addTag();
	void removeTag();
	void print();
	void moveTo();
	void save();
	void addToDiv();
};

#endif // !__PAGE__HEADER__
