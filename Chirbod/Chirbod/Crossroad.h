#ifndef CROSSROAD_H
#define CROSSROAD_H

struct Crossroad
{
	int altitude;
	static int carryingCapacity;
	double rainAmount;
};

int Crossroad::carryingCapacity = -1;

#endif // CROSSROAD_H
