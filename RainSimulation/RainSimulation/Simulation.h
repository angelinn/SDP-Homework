#ifndef SIMULATION_H
#define SIMULATION_H

#include "Crossroad.h"
#include "GNode.h"

class Simulation
{
	typedef std::pair<double, int> simPair;

public:
	Simulation(std::istream &);
	~Simulation();

private:
	Simulation(const Simulation &);
	Simulation& operator=(const Simulation &);

public:
	void start();

private:
	void load(size_t, size_t, int);
	simPair* getSimulationDetails();
	void fillGraph(size_t, size_t);
	void bombNodeIf(GNode *&, GNode *&);
	void printMatrix(size_t, size_t) const;
	void water(int);

private:
	int simulationsCount;
	std::istream& input;
	std::vector<GNode*> graph;
};

#endif // SIMULATION_H
