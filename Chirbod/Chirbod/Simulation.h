#ifndef SIMULATION_H
#define SIMULATION_H

#include "City.h"
#include <iostream>

class Simulation
{
public:
	Simulation(int, int, int, std::istream &);
	void start();

private:
	Simulation(const Simulation &);
	Simulation& operator=(const Simulation &);

private:


private:
	std::istream* input;
	City city;
};


#endif // SIMULATION_H
