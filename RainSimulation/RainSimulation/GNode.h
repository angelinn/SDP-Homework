#ifndef GNODE_H
#define GNODE_H

#include "Crossroad.h"
#include <vector>

struct GNode
{
	GNode(int item, int nearRiver = 0)
	{
		value.altitude = item;
		value.nearRiver = nearRiver;
	}

	Crossroad value;
	std::vector<GNode*> neighbours;
};


#endif // GNODE_H
