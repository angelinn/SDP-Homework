#ifndef CROSSROAD_H
#define CROSSROAD_H

struct Crossroad
{
	int altitude;
	int nearRiver; // nearRiver holds if the crossroad is near river from one side (it'd be 1) or two sides (it'd be 2)
	double currentWater;
	static int carryingCapacity;
};

#endif // CROSSROAD_H
