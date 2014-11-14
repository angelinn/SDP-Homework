#include <iostream>
#include "DLList.h"

int main()
{
	DLList<int> list;
	for (size_t i = 0; i < 1000; i++)
	{
		list.pushBack(i);
	}

	for (size_t i = 0; i < 1000; i++)
	{
		std::cout << list.popFront() << std::endl;
	}
}