#include "City.h"
#include <iostream>

int Crossroad::carryingCapacity = -1;

City::City() : map(NULL), height(0), width(0)
{  }

City::City(const City& other) : City()
{
	copyFrom(other);
}

City& City::operator=(const City& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

City::~City()
{
	free();
}

void City::copyFrom(const City& other)
{
	height = other.height;
	width = other.width;
	allocate();

	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			map[i][j] = other.map[i][j];
}

void City::allocate()
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

void City::free()
{
	for (int i = 0; i < height; ++i)
		delete[] map[i];

	delete[] map;
}

void City::create(int m, int n, int c, std::istream& input)
{
	height = m;
	width = n;
	Crossroad::carryingCapacity = c;
	allocate();

	enterMe(input);
}

void City::enterMe(std::istream& input)
{
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			input >> map[i][j].altitude;
}

void City::bombAll(int i, int j)
{
	Crossroad& current = map[i][j];

	if (!i || i == width - 1)
	{
		current.currentWater -= 2 * Crossroad::carryingCapacity;
		if (!j || j == height - 1)
			current.currentWater -= 2 * Crossroad::carryingCapacity;
	}

	DLList<Crossroad> neighbours;
	check()
		int lower = 0;
	if (check(i + 1, j, current))
		++lower;
	if (check(i - 1, j, current))
		++lower;
	if (check(i, j + 1, current))
		++lower;
	if (check(i, j - 1, current))
		++lower;

	double amount = Crossroad::carryingCapacity / lower;
	bomb(i + 1, j, amount, current);
	bomb(i - 1, j, amount, current);
	bomb(i, j + 1, amount, current);
	bomb(i, j - 1, amount, current);
}

void City::check(int i, int j, const Crossroad& current, const DLList<Crossroad>& neighbours)
{
	if (i - 1 >= 0)
	{

	}

	if (j - 1 >= 0)
	{

	}
	if (i < 0 && j < 0)
		return;

	if (map[i][j].altitude < current.altitude)
		neighbours.pushBack(map[i][j]);
}

void City::water(int c)
{
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			map[i][j].currentWater = c;
}

void City::workMe()
{
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			bomb(i, j);
}

void City::printMe(std::ostream& output) const
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
			output << map[i][j].currentWater << " ";

		output << '\n';
	}
}