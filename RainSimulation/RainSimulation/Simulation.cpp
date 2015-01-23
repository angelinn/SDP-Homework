#include "Simulation.h"
#include <iostream>

typedef std::pair<double, int> simPair;

Simulation::Simulation(std::istream& stream) : input(stream), simulationsCount(0)
{  }

void Simulation::load(int m, int n, int c)
{
	try
	{
		city = new int*[m];
		for (int i = 0; i < m; ++i)
			city[i] = new int[n];
	}
	catch (std::bad_alloc &)
	{
		free();
		throw;
	}

	Crossroad::carryingCapacity = c;
}

simPair* Simulation::getSimulationDetails()
{
	input >> simulationsCount;
	simPair* simulationDetails = NULL;

	try
	{
		simulationDetails = new simPair[simulationsCount];
	}
	catch (std::bad_alloc &)
	{
		delete[] simulationDetails;
		throw;
	}

	for (int i = 0; i < simulationsCount; ++i)
		input >> simulationDetails[i].first >> simulationDetails[i].second;

	return simulationDetails;
}

void Simulation::start()
{
	int m, n, c;
	input >> m >> n >> c;
	load(m, n, c);
	simPair* simulationDetails = getSimulationDetails();
	City original = city;

	int turns = 0;
	//int waterToFall = 0;

	for (int i = 0; i < simulationsCount; ++i)
	{
		if (i)
			city = original;

		city.water(simulationDetails[i].first);
		turns = simulationDetails[i].second;

		for (int j = 0; j < turns; ++j)
			city.workMe();

		city.printMe(std::cout);
	}


	delete[] simulationDetails;
}