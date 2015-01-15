#include "Simulation.h"

Simulation::Simulation(int m, int n, int c, std::istream& stream) : map(NULL), height(m), width(n)
{
	try
	{
		map = new Crossroad*[height];
		for (int i = 0; i < height; ++i)
			map[i] = new Crossroad[width];
	}
	catch (std::bad_alloc &)
	{
		free();
		throw;
	}
}

void Simulation::free()
{
	for (int i = 0; i < height; ++i)
		delete[] map[i];

	delete[] map;
}