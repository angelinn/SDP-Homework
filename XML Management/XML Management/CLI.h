#ifndef CLI_H
#define CLI_H

#include "XMLManager.h"

class CLI
{
public:
	CLI();
	void go();

private:
	static const char* HELP_MESSAGE;

private:
	void help();
	void split(std::string &, char, DLList<std::string> &);
	void parseCommand(DLList<std::string> &);
	XMLManager manager;
};


#endif // CLI_H
