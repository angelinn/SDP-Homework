#ifndef SIMULATION_H
#define SIMULATION_H

#include "Crossroad.h"
#include "DirectedGraph.h"

class Simulation
{
	typedef std::pair<double, int> simPair;

public:
	Simulation(std::istream &);

private:
	Simulation(const Simulation &);
	Simulation& operator=(const Simulation &);

public:
	void load(int, int, int);
	simPair* getSimulationDetails();
	void start();

private:
	void readCity();

private:
	int simulationsCount;
	std::istream& input;
	DirectedGraph<Crossroad> graph;
};

#endif // SIMULATION_H
