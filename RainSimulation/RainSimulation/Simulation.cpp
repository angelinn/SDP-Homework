#include "Simulation.h"
#include <iostream>

typedef std::pair<double, int> simPair;
int Crossroad::carryingCapacity = 0;

Simulation::Simulation(std::istream& stream) : input(stream), simulationsCount(0)
{  }

Simulation::~Simulation()
{
	size_t graphSize = graph.size();

	for (size_t i = 0; i < graphSize; ++i)
		delete graph[i];
}

void Simulation::load(size_t m, size_t n, int c)
{
	int courier = 0;
	size_t size = m * n;
	int nearRiver = 0;

	for (size_t i = 0; i < m; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			if (i == 0 || i == m - 1)
				nearRiver += 2;
			if (j == 0 || j == n - 1)
				nearRiver += 2;


			std::cin >> courier;
			graph.push_back(new GNode(courier, nearRiver));
			nearRiver = 0;
		}
	}

	fillGraph(m, n);

	Crossroad::carryingCapacity = c;
}

void Simulation::fillGraph(size_t height, size_t width)
{
	int vectorCounter = 0;
	GNode* current = NULL;

	for (size_t i = 0; i < height; ++i)
	{
		for (size_t j = 0; j < width; ++j)
		{
			current = graph[width * i + j];

			if (i == 0)
				bombNodeIf(current, graph[width * (i + 1) + j]);
			else if (i == height - 1)
				bombNodeIf(current, graph[width * (i - 1) + j]);
			else
			{
				bombNodeIf(current, graph[width * (i + 1) + j]);
				bombNodeIf(current, graph[width * (i - 1) + j]);
			}

			if (j == 0)
				bombNodeIf(current, graph[width * i + j + 1]);
			else if (j == width - 1)
				bombNodeIf(current, graph[width * i + j - 1]);
			else
			{
				bombNodeIf(current, graph[width * i + j + 1]);
				bombNodeIf(current, graph[width * i + j - 1]);
			}
		}
	}

	for (size_t i = 0; i < height * width; ++i)
	{
		std::cout << graph[i]->value.altitude << " - ";
		for (size_t j = 0; j < graph[i]->neighbours.size(); ++j)
		{
			std::cout << graph[i]->neighbours[j]->value.altitude << " ";
		}
		std::cout << std::endl;
	}
}

void Simulation::bombNodeIf(GNode*& current, GNode*& versus)
{
	if (current->value.altitude > versus->value.altitude)
		current->neighbours.push_back(versus);
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
	int m = 0, n = 0, c = 0;

	input >> m >> n >> c;
	load(m, n, c);
	simPair* simulationDetails = getSimulationDetails();


	int turns = 0;
	int waterToFall = 0;
	size_t graphSize = graph.size();
	size_t neighbourSize = 0;

	for (int simulationNum = 0; simulationNum < simulationsCount; ++simulationNum)
	{
		water(static_cast<int>(simulationDetails[simulationNum].first));
		turns = simulationDetails[simulationNum].second;

		for (int turn = 0; turn < turns; ++turn)
		{
			for (size_t i = 0; i < graphSize; ++i)
			{
				if (graph[i]->value.nearRiver)
					graph[i]->value.currentWater -= Crossroad::carryingCapacity * graph[i]->value.nearRiver;

				neighbourSize = graph[i]->neighbours.size();

				for (size_t j = 0; j < neighbourSize; ++j)
				{
					graph[i]->neighbours[j]->value.currentWater += Crossroad::carryingCapacity;
					graph[i]->value.currentWater -= Crossroad::carryingCapacity;
				}

				//std::cout << "K: " << i << std::endl;
				//printMatrix(m, n);
				//std::cout << std::endl;
			}
		}

		printMatrix(m, n);
	}


	delete[] simulationDetails;
}

void Simulation::water(int waterToFall)
{
	size_t size = graph.size();
	for (size_t i = 0; i < size; ++i)
		graph[i]->value.currentWater = waterToFall;
}

void Simulation::printMatrix(size_t h, size_t w) const
{
	for (size_t i = 0; i < h; ++i)
	{
		for (size_t j = 0; j < w; ++j)
			std::cout << graph[w * i + j]->value.currentWater << " ";
		std::cout << std::endl;
	}
}