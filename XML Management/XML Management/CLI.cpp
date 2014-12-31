#include "CLI.h"
#include <iostream>
#include <fstream>
#include <string>

const char* CLI::HELP_MESSAGE = "addtag {name} {content} {path} - adds a tag to the current path\n"
								"removetag {path} {true/false - delete all beneath this tag} - removes a tag\n"
								"changetag {new_name} {new_content} {path} - changes a current tag\n"
								"\naddattribute {name} {value} {path} - adds an attribute to the desired tag"
								"removeattribute {name} {path} - removes an attribute from the desired tag\n"
								"changeattribute {old_name} {new_name} {new_value} {path} - changes an attribute\n"
								"\nsend > {file} {true/false - pretty print} - sends the xml document to a file\n"
								"send {true/false - pretty print} - sends the xml document to the current interface\n";


void CLI::go()
{
	help();
	std::string buffer;
	DLList<std::string> result;

	while (true)
	{
		std::getline(std::cin, buffer);
		split(buffer, ' ', result);
		try
		{
			parseCommand(result);
		}
		catch (std::invalid_argument e)
		{
			std::cerr << e.what() << std::endl;
		}
		catch (TreeException e)
		{
			std::cerr << e.what() << std::endl;
		}
		catch (std::exception)
		{
			std::cerr << "Something isn't right!" << std::endl;
		}
		result.clear();
	}
}

void CLI::parseCommand(DLList<std::string>& command)
{
	std::string cmd = command.popFront();
	if (cmd.find("tag") != std::string::npos)
	{
		std::string firstPart(cmd, 0, cmd.find("tag"));
		if (!firstPart.compare("add"))
			manager.workTag(command, XMLManager::ADD);
		else if (!firstPart.compare("change"))
			manager.workTag(command, XMLManager::CHANGE);
		else if (!firstPart.compare("remove"))
			manager.workTag(command, XMLManager::REMOVE);
		else
			throw std::invalid_argument("Invalid command");
	}
	else if (cmd.find("attribute") != std::string::npos)
	{
		std::string firstPart(cmd, 0, cmd.find("attribute"));
		if (!firstPart.compare("add"))
			manager.workAttributes(command, XMLManager::ADD);
		else if (!firstPart.compare("change"))
			manager.workAttributes(command, XMLManager::CHANGE);
		else if (!firstPart.compare("remove"))
			manager.workAttributes(command, XMLManager::REMOVE);
		else
			throw std::invalid_argument("Invalid command");
	}
	else if (cmd.find("send") != std::string::npos)
	{
		std::string pretty(command.popBack());
		bool prettyPrint = false;
		if (!pretty.compare("true"))
			prettyPrint = true;

		if (command.isEmpty())
			manager.print(std::cout, prettyPrint);
		else
		{
			std::string path(command.popBack());
			saveToFile(path, prettyPrint);
		}
	}
	else if (!cmd.compare("help"))
		help();
}

void CLI::split(std::string& string, char delim, DLList<std::string>& result)
{
	std::string placeholder;

	for (size_t i = 0, j = 0; i < string.size(); ++i, ++j)
	{
		if (string[i] == delim)
		{
			if (!placeholder.compare("\"\""))
				result.pushBack("");
			else
				result.pushBack(placeholder);

			placeholder.clear();
			j = 0;
			continue;
		}
		placeholder.push_back(string[i]);

	}
	result.pushBack(placeholder);
}

void CLI::saveToFile(std::string& path, bool pretty) const
{
	std::ofstream output(path, std::ios::out);
	manager.print(output, pretty);
	output.close();
}

void CLI::help() const
{
	std::cout << HELP_MESSAGE << std::endl;
}