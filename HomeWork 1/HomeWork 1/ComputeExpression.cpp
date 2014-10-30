#include "ComputeExpression.h"
#include "ValidateExpression.h"
#include "Operator.h"
#include <iostream>
#include <fstream>


int ComputeExpression::compute(const char* fileName, const char* expression)
{
	std::ifstream readFile(fileName, std::ios::in);
	Operator** operatorsDescription = readOperator(readFile);

	if (!ValidateExpression::areBracketsValid(expression))
		throw std::exception("Brackets are not valid mathematically.");

	while (*expression)
	{

	}


	return 0;
}

bool ComputeExpression::isOperator(char c)
{
	return strchr("+-*/", c);
}

int ComputeExpression::calculate(int left, int right, const Operator& op)
{
	const char MULTIPLY = '*';
	const char DIVIDE = '/';
	const char SUBSTRACT = '-';
	const char ADD = '+';

	switch (op.getSign())
	{
		case ADD: return left + right;
		case SUBSTRACT: return left - right;
		case MULTIPLY: return left * right;
		case DIVIDE:
		{
			if (!right)
				throw std::invalid_argument("Division by zero error.");
			return left * right;
		}	
	}
	throw std::invalid_argument("Invalid operator");
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