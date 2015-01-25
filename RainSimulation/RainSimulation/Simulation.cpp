#include "Simulation.h"
#include <iostream>

typedef std::pair<int, int> simPair;
int Crossroad::carryingCapacity = 0;

Simulation::Simulation(std::istream& in, std::ostream& out) : input(in), output(out), simulationsCount(0), height(0), width(0)
{  }

Simulation::~Simulation()
{
	size_t graphSize = graph.size();

	for (size_t i = 0; i < graphSize; ++i)
		delete graph[i];
}

///
///  Puts the matrix numbers in a vector of nodes 
///  and sets the setting if they are near a river
///
void Simulation::loadStreets(size_t m, size_t n, int c)
{
	height = m;
	width = n;

	int courier = 0;
	int nearRiver = 0;

	for (size_t i = 0; i < height; ++i)
	{
		for (size_t j = 0; j < width; ++j)
		{
			if (i == 0 || i == height - 1)
				++nearRiver;
			if (j == 0 || j == width - 1)
				++nearRiver;


			input >> courier;
			graph.push_back(new GNode(courier, nearRiver));
			nearRiver = 0;
		}
	}

	fillGraph();

	Crossroad::carryingCapacity = c;
}

///
/// From the ready vector this method connects the graph (makes it directed)
///
void Simulation::fillGraph()
{
	GNode* current = NULL;

	for (size_t i = 0; i < height; ++i)
	{
		for (size_t j = 0; j < width; ++j)
		{
			current = graph[width * i + j];

			if (i == 0)
				addNodeIf(current, graph[width * (i + 1) + j]);
			else if (i == height - 1)
				addNodeIf(current, graph[width * (i - 1) + j]);
			else
			{
				addNodeIf(current, graph[width * (i + 1) + j]);
				addNodeIf(current, graph[width * (i - 1) + j]);
			}

			if (j == 0)
				addNodeIf(current, graph[width * i + j + 1]);
			else if (j == width - 1)
				addNodeIf(current, graph[width * i + j - 1]);
			else
			{
				addNodeIf(current, graph[width * i + j + 1]);
				addNodeIf(current, graph[width * i + j - 1]);
			}
		}
	}
}

///
/// If the versus node is lower than the current, adds it to current neighbours
///
void Simulation::addNodeIf(GNode*& current, GNode*& versus)
{
	if (current->value.altitude > versus->value.altitude)
		current->neighbours.push_back(versus);
}

///
/// Gets from the given input stream the water that will fall and the turns count
/// May throw a std::bad_alloc exception
///
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

///
/// The main method
///
void Simulation::start()
{
	int m = 0, n = 0, c = 0;

	input >> m >> n >> c;
	loadStreets(m, n, c);
	simPair* simulationDetails = getSimulationDetails();


	int turns = 0;
	double waterToFall = 0;
	size_t graphSize = graph.size();

	for (int simulationNum = 0; simulationNum < simulationsCount; ++simulationNum)
	{
		water(simulationDetails[simulationNum].first);
		turns = simulationDetails[simulationNum].second;

		for (int turn = 0; turn < turns; ++turn)
		{
			for (size_t i = 0; i < graphSize; ++i)
			{
				waterToFall = graph[i]->value.currentWater /
					(graph[i]->value.nearRiver + graph[i]->neighbours.size());

				if (waterToFall > Crossroad::carryingCapacity)
					leak(graph[i], Crossroad::carryingCapacity);
				else
					leak(graph[i], waterToFall);
			}

			if (checkForEnd())
				break;
		}
		printMatrix();
	}

	delete[] simulationDetails;
}

///
/// Checks if simulation needs to be stopped
///
bool Simulation::checkForEnd()
{
	size_t graphSize = graph.size();
	for (size_t i = 0; i < graphSize; ++i)
		if (graph[i]->value.currentWater && graph[i]->neighbours.size())
			return false;

	return true;
}

///
/// Method that adds and substracts water amount as needed
///
void Simulation::leak(GNode* node, double waterToLeak)
{
	size_t neighbourSize = node->neighbours.size();

	for (size_t i = 0; i < neighbourSize; ++i)
	{
		if (node->value.currentWater)
		{
			node->neighbours[i]->value.currentWater += waterToLeak;
			node->value.currentWater -= waterToLeak;

			if (node->value.currentWater < 0)
				node->value.currentWater = 0;
		}
	}

	// TO DO: Fix repetative Code
	node->value.currentWater -= node->value.nearRiver * 
		Crossroad::carryingCapacity * NEAR_RIVER_MULTIPLY;

	if (node->value.currentWater < 0)
		node->value.currentWater = 0;
}

///
/// Floods the city of Chirbod with water
///
void Simulation::water(int waterToFall)
{
	size_t size = graph.size();
	for (size_t i = 0; i < size; ++i)
		graph[i]->value.currentWater = waterToFall;
}

///
/// Prints the matrix in the given output stream in the constructor
///
void Simulation::printMatrix() const
{
	for (size_t i = 0; i < height; ++i)
	{
		for (size_t j = 0; j < width; ++j)
			output << graph[width * i + j]->value.currentWater << " ";

		output << std::endl;
	}
	output << std::endl;
}