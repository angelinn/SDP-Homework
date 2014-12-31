#ifndef XML_MANAGER_H
#define XML_MANAGER_H

#include "Tree.h"
#include "Tag.h"

class XMLManager
{
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
	void addTag(const Tag &, std::string &);
	void changeTag(const Tag &, std::string &);
	void removeTag(std::string &, bool = false);

public:
	void addAttribute(const Attribute &, std::string &);
	void changeAttribute(std::string &, const Attribute &, std::string &);
	void removeAttribute(const Attribute &, std::string &);

	void print(std::ostream &, bool) const;
private:
	Tree tags;
};

#endif // XML_MANAGER_H