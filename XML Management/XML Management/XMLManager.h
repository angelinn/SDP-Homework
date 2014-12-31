#ifndef XML_MANAGER_H
#define XML_MANAGER_H

#include "Tree.h"
#include "Tag.h"

class XMLManager
{
public:
	XMLManager(std::ostream &);

public:
	void addTag(const Tag &, const char *);
	void changeTag(const Tag &, const char *);
	void removeTag(const char *, bool = false);

public:
	void addAttribute(const Attribute &, const char *);
	void changeAttribute(const Attribute &, const char *);

	void removeAttribute(const char *, const char *);

	void print() const;
private:
	std::ostream* output;
	Tree tags;
};

#endif // XML_MANAGER_H