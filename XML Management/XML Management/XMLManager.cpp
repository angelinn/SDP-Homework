#include "XMLManager.h"

XMLManager::XMLManager(std::ostream& out) : output(&out)
{  }

void XMLManager::addTag(const Tag& tag, const char* path)
{
	try
	{
		tags.insert(tag, path);
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
		tags.change(tag, path);
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
		tags.remove(path, cascadeDeletion);
	}
	catch (TreeException& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void XMLManager::print() const
{
	tags.send(*output);
}