#ifndef TAG_H
#define TAG_H

#include <string>
#include "DLList.h"
#include "Attribute.h"

class Tag
{
public:
	Tag(std::string, bool = false);
	Tag(std::string, std::string, bool = false);

public:
	std::string getName() const;
	std::string getContent() const;
	void setContent(const char *);

public:
	void addAttribute(const Attribute &);
	void changeAttribute(const Attribute &, const Attribute &);
	void removeAttribute(const Attribute &);

	bool isSelfClosing() const;

public:
	bool operator==(const char* str) const { return name == str; }
	bool operator!=(const char* str) const { return !(*this == str); }

	std::string getNameAndAttributes(bool) const;

private:
	std::string name;
	std::string content;
	bool selfClosing;
	DLList<Attribute> attributes;
};


#endif // TAG_H
