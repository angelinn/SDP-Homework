#ifndef SIMULATION_H
#define SIMULATION_H

#include "Crossroad.h"
#include <istream>

class Simulation
{
public:
	Simulation(int, int, int, std::istream &);

private:
	Simulation(const Simulation &);
	Simulation& operator=(const Simulation &);

private:
	int height;
	int width;
	void free();

private:
	Crossroad** map;
};


#endif // SIMULATION_H
