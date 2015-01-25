#include <iostream>
#include "Simulation.h"
#include <crtdbg.h>

int main()
{
	{
		Simulation sim(std::cin);
		sim.start();
	}
	_CrtDumpMemoryLeaks();

}