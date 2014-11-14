#include <iostream>
#include "DLList.h"
#include "Queue.h"
#include <ctime>


int main()
{
	try
	{
		DLList<int> list;
		Queue<int> queue;

		double start = time(NULL);
		for (size_t i = 0; i < 1000; i++)
		{
			//list.pushFront(i);
			queue.enqueue(i);
		}

		for (size_t i = 0; i < 1000; i++)
		{
			std::cout << queue.dequeue() << std::endl;//list.popBack() << std::endl;
		}
		double end = time(NULL);
		std::cout << "it took " << end - start << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}