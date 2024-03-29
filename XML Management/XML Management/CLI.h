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
	void help() const;
	void split(std::string &, char, DLList<std::string> &);
	void parseCommand(DLList<std::string> &);
	void saveToFile(std::string &, bool) const;

	bool keepGoing;
	XMLManager manager;
};


#endif // CLI_H
