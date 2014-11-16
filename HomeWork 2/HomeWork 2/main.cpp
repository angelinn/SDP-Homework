#include <iostream>
#include "Market.h"

int main()
{
	try
	{
		Client a;
		a.creditCard = 0;
		a.ID = -1;
		a.numberOfGoods = 2;

		Market kaufland(5);
		kaufland.AddClient(&a, 1);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}