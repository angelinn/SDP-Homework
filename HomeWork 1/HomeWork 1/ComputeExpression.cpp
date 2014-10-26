#include "ComputeExpression.h"
#include "Operator.h"
#include <iostream>
#include <fstream>

int ComputeExpression::compute(const char* fileName, const char* expression)
{
	std::ifstream readFile(fileName, std::ios::in);

	Operator a(readOperator(readFile));
	std::cout << a.getSign();

	return 0;
}

Operator ComputeExpression::readOperator(std::ifstream& readFile)
{
	char letter;
	char sign;
	int priority;
	int associativity;

	readFile >> letter;
	readFile >> sign;
	readFile >> priority;
	readFile >> associativity;

	return Operator(letter, sign, priority, associativity);
}