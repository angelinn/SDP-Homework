#ifndef SIMULATION_H
#define SIMULATION_H

#include "Crossroad.h"
#include "GNode.h"

class Simulation
{
	typedef std::pair<int, int> simPair;
	static const int NEAR_RIVER_MULTIPLY = 2; // If the crossroad is near a river, it carries 2*C water

public:
	Simulation(std::istream &, std::ostream &);
	~Simulation();

public:
	void start();
	void printMatrix() const;

private:
	Simulation(const Simulation &);
	Simulation& operator=(const Simulation &);

private:
	void loadStreets(size_t, size_t, int);
	void fillGraph();
	simPair* getSimulationDetails();

private:
	void addNodeIf(GNode *&, GNode *&);
	void water(int);
	void leak(GNode *, double);
	bool checkForEnd();

private:
	std::istream& input;
	std::ostream& output;

	int simulationsCount;
	size_t height;
	size_t width;
	std::vector<GNode*> graph;
};

#endif // SIMULATION_H
