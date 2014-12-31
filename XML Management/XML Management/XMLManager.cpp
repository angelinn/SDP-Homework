#include "XMLManager.h"

void XMLManager::addTag(const Tag& tag, std::string & path)
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

void XMLManager::workTag(DLList<std::string>& command, XMLManager::STATUS status)
{
	std::string oldName, name, content, path;

	if (status == REMOVE)
	{
		path = command.popFront();
		if (command.popFront().compare("true"))
			removeTag(path, true);
		else
			removeTag(path);
	}
	else
	{
		name = command.popFront();
		content = command.popFront();
		path = command.popFront();

		// Проверява дали тагът е самозатварящ се
		Tag tag("", "");
		if (name.find("/") != std::string::npos)
		{
			name.pop_back();
			tag = Tag(name, content, true);
		}
		else
			tag = Tag(name, content);

		if (status == ADD)
			addTag(tag, path);
		else
			changeTag(tag, path);
	}
}

void XMLManager::workAttributes(DLList<std::string>& commands, XMLManager::STATUS status)
{
	std::string oldName, name, value, path;
	switch (status)
	{
	case ADD:
	{
		name = commands.popFront();
		value = commands.popFront();
		path = commands.popFront();

		Attribute attr(name, value);
		tags.addAttribute(attr, path);
		break;
	}
	case CHANGE:
	{
		oldName = commands.popFront();
		name = commands.popFront();
		value = commands.popFront();
		path = commands.popFront();

		Attribute attr(name, value);
		tags.changeAttribute(oldName, attr, path);
		break;
	}
	case REMOVE:
	{
		name = commands.popFront();
		path = commands.popFront();

		tags.removeAttribute(name, path);
		break;
	}
	}
	if (!commands.isEmpty())
		throw std::exception("Something went really wrong ..");
}

void XMLManager::changeTag(const Tag& tag, std::string & path)
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

void XMLManager::removeTag(std::string & path, bool cascadeDeletion)
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

void XMLManager::addAttribute(const Attribute& attribute, std::string & path)
{
	tags.addAttribute(attribute, path);
}

void XMLManager::changeAttribute(std::string & oldAttribute, const Attribute& newAttribute, std::string & path)
{
	tags.changeAttribute(oldAttribute, newAttribute, path);
}

void XMLManager::removeAttribute(const Attribute& attribute, std::string & path)
{
	tags.removeAttribute(attribute, path);
}

void XMLManager::print(std::ostream& output, bool pretty) const
{
	tags.send(output, pretty);
}