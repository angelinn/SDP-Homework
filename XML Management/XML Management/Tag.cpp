#include "Tag.h"

Tag::Tag(const char* n, bool selfClose) : name(n), selfClosing(selfClose)
{  }

Tag::Tag(const char* n, const char* c, bool selfClose) : name(n), content(c), selfClosing(selfClose) 
{  }

std::string Tag::getName() const
{
	return name;
}

std::string Tag::getContent() const 
{
	return content;
}

void Tag::setContent(const char* c) 
{
	content = c; 
}

void Tag::addAttribute(const Attribute& attribute) 
{
	attributes.pushBack(attribute); 
}

void Tag::changeAttribute(const Attribute& old, const Attribute& newAttribute)
{
	for (DLList<Attribute>::Iterator iter = attributes.begin(); iter; ++iter)
	{
		if ((*iter).getKey() == old.getKey())
			(*iter) = newAttribute;
	}
}

void Tag::removeAttribute(const Attribute& attribute)
{
	for (DLList<Attribute>::Iterator iter = attributes.begin(); iter; ++iter)
	{
		if ((*iter).getKey() == attribute.getKey())
		{
			DLList<Attribute>::Iterator deleter = iter;
			++iter;
			attributes.popAt(deleter);
			--iter;
		}
	}
}

bool Tag::isSelfClosing() const
{
	return selfClosing;
}

std::string Tag::getNameAndAttributes() const
{
	std::string result;
	result += "<" + name;

	std::string finalizer = selfClosing ? "/>\n" : ">\n";

	if (attributes.isEmpty())
		result += finalizer;
	else
	{
		result += ' ';
		for (DLList<Attribute>::Iterator iter = attributes.begin(); iter;)
		{
			result += (*iter).getKey() + "=\"" + (*iter).getValue() + "\"";
			if (++iter)
				result += " ";
			else
				result += finalizer;
		}
	}

	return result;
}
