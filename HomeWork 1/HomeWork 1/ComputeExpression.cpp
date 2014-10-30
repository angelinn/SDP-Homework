#include "ComputeExpression.h"
#include "Operator.h"
#include <iostream>
#include <fstream>

int ComputeExpression::compute(const char* fileName, const char* expression)
{
	std::ifstream readFile(fileName, std::ios::in);

	Operator** operatorsDescription = readOperator(readFile);


	return 0;
}

Operator** ComputeExpression::readOperator(std::ifstream& readFile)
{ 
	Operator** result = new Operator*[1024];
	char letter;
	char sign;
	int priority;
	int associativity;

	for (int i = 0; !readFile.eof(); ++i)
	{
		readFile >> letter;
		readFile >> sign;
		readFile >> priority;
		readFile >> associativity;

		result[i] = new Operator(letter, sign, priority, associativity);
	}

	return result;
}