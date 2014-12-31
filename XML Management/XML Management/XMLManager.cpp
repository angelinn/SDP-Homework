#include "XMLManager.h"

XMLManager::XMLManager(std::ostream& out) : output(&out)
{  }

void XMLManager::addTag(const Tag& tag, const char* path)
{
	try
	{
		tags.insertTag(tag, path);
	}
	catch (TreeException& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void XMLManager::changeTag(const Tag& tag, const char* path)
{
	try
	{
		tags.changeTag(tag, path);
	}
	catch (TreeException& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void XMLManager::removeTag(const char* path, bool cascadeDeletion)
{
	try
	{
		tags.removeTag(path, cascadeDeletion);
	}
	catch (TreeException& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void XMLManager::addAttribute(const Attribute& attribute, const char* path)
{
	tags.addAttribute(attribute, path);
}

void XMLManager::changeAttribute(const char* oldAttribute, const Attribute& newAttribute, const char* path)
{
	tags.changeAttribute(oldAttribute, newAttribute, path);
}

void XMLManager::removeAttribute(const Attribute& attribute, const char* path)
{
	tags.removeAttribute(attribute, path);
}

void XMLManager::print() const
{
	tags.send(*output);
}