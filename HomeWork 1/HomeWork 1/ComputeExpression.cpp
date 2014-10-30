#include "ComputeExpression.h"
#include "ValidateExpression.h"
#include "operatorsConstants.h"
#include "Stack.h"
#include "Operator.h"
#include <iostream>
#include <fstream>


double ComputeExpression::compute(const char* fileName, const char* expression)
{
	std::ifstream readFile(fileName, std::ios::in);
	if (!readFile)
		throw std::exception("Cannot open file.");

	int operatorsArraySize = 0;
	Operator** operatorsDescription = readOperator(readFile, operatorsArraySize);

	if (!ValidateExpression::areBracketsValid(expression))
		throw std::exception("Brackets are not valid mathematically.");

	while (*expression)
	{
		Stack<double> numbers;
		Stack<Operator*> operators;

		if (*expression == OPEN_BRACKET)
			operators.push(new Operator(OPEN_BRACKET, OPEN_BRACKET, -1, -1));

		else if (isdigit(*expression))
		{
			std::cout << fetchNumber(expression) << std::endl;
		}

		if (isOperator(*expression))
		{
			
			for (int i = 0; i < operatorsArraySize; ++i)
				if (*expression == operatorsDescription[i]->getLetter())
					Operator oper = Operator(*operatorsDescription[i]);

			if (operators.)
		}

		++expression;
	}


	return 0;
}

double ComputeExpression::fetchNumber(const char*& expression)
{
	char numberBuffer[1024];
	int i = 0;

	if (expression[-1] == SUBSTRACT)
	{
		numberBuffer[i] = SUBSTRACT;
		++i;
	}

	while (*expression != ' ' && *expression != '\0')
	{
		numberBuffer[i] = *expression;
		++i;
		++expression;
	}

	return atof(numberBuffer);
}

bool ComputeExpression::isOperator(char c)
{
	return isalpha(c);
}

double ComputeExpression::calculate(double left, double right, const Operator& op)
{
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

Operator** ComputeExpression::readOperator(std::ifstream& readFile, int& size)
{ 
	Operator** result = new Operator*[1024];
	char letter;
	char sign;
	int priority;
	int associativity;

	int i = 0;

	while(!readFile.eof())
	{
		readFile >> letter;
		readFile >> sign;
		readFile >> priority;
		readFile >> associativity;

		result[i] = new Operator(letter, sign, priority, associativity);
		++i;
	}

	size = i;
	return result;
}