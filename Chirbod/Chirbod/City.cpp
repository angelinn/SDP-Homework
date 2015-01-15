#include "City.h"
#include <iostream>

City::City(int m, int n, int c) : map(NULL), height(m), width(n)
{
	Crossroad::carryingCapacity = c;

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

City::~City()
{
	free();
}

void City::enterMe(std::istream& input)
{
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			input >> map[i][j].altitude;
}