#ifndef CLI_H
#define CLI_H

#include "Simulation.h"
#include <iostream>

class CLI
{
public:
	CLI(int m, int n, int c) : sim(m, n, c, std::cin)
	{  }

private:
	Simulation sim;
};

#endif // CLI_H