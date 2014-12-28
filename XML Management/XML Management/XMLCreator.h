#ifndef XML_CREATOR_H
#define XML_CREATOR_H

#include "Tree.h"

class XMLCreator
{
public:
	void insertTag(const char *, const char * = NULL);
	void removeTag(const char *);

//private:
	Tree<std::string> markers;
};

#endif // XML_CREATOR_H