#include "CLI.h"
#include <iostream>
#include <string>

const char* CLI::HELP_MESSAGE = "addtag {name} {content} {path} - adds a tag to the current path\n"
								"removetag {path} {true/false - delete all beneath this tag} - removes a tag from the path\n"
								"changetag {new_name} {new_content} {path} - changes a current tag\n"
								"\naddattribute {name} {value} {path} - adds an attribute to the desired tag"
								"removeattribute {name} {path} - removes an attribute from the desired tag\n"
								"changeattribute {old_name} {new_name} {new_value} {path} - changes an attribute\n"
								"send > {file} - sends the xml document to a file\n"
								"send > console - sends the xml document to the current interface\n";


CLI::CLI(): manager(std::cout)
{  }

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
		catch (std::exception e)
		{
			std::cerr << e.what() << std::endl;
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
			throw std::exception("Invalid command");
	}
	else if (cmd.find("send"))
		manager.print();
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

void CLI::help()
{
	std::cout << HELP_MESSAGE << std::endl;
}