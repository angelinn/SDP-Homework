#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include <vector>

template <typename T>
struct DirectedGraph
{
	T value;
	std::vector<GNode<T>*> neighbours;
};


#endif // DIRECTED_GRAPH_H
