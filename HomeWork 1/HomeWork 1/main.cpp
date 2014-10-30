#include <iostream>
#include "ComputeExpression.h"
#include "ValidateExpression.h"

int main(int argc, char* argv[])
{
	try
	{
		ComputeExpression computingMachine;
		std::cout << std:: fixed << computingMachine.compute(argv[1], argv[2]);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}