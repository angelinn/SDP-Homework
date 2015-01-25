#include <iostream>
#include "Simulation.h"
#include <crtdbg.h>
#include <fstream>
#include <ctime>

int main()
{
	{
		// Fill path here or use std::cin for vs input
		const char* PATH = "C:\\Users\\Angelin\\Desktop\\sts.txt";

		std::ifstream inFile(PATH, std::ios::in);

		Simulation sim(inFile, std::cout);
		clock_t start, end;
		try
		{
			start = clock();
			sim.start();
			end = clock();

			std::cout << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
		}
		catch (std::exception e)
		{
			std::cerr << e.what() << std::endl;
			inFile.close();
		}

		inFile.close();
	}

	_CrtDumpMemoryLeaks();
	return 0;
}