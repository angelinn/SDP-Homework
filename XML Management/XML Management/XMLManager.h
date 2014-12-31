#ifndef XML_MANAGER_H
#define XML_MANAGER_H

#include "Tree.h"
#include "Tag.h"

class XMLManager
{
public:
	XMLManager(std::ostream &);

public:
	enum STATUS
	{
		ADD,
		CHANGE,
		REMOVE
	};


	void workTag(DLList<std::string> &, STATUS);
	void workAttributes(DLList<std::string> &, STATUS);

public:
	void addTag(const Tag &, const char *);
	void changeTag(const Tag &, const char *);
	void removeTag(const char *, bool = false);

public:
	void addAttribute(const Attribute &, const char *);
	void changeAttribute(const char *, const Attribute &, const char *);
	void removeAttribute(const Attribute &, const char *);

	void print() const;
private:
	std::ostream* output;
	Tree tags;
};

#endif // XML_MANAGER_H