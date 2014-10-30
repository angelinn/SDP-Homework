#include "ComputeExpression.h"
#include "ValidateExpression.h"
#include "operatorsConstants.h"
#include "Stack.h"
#include "Operator.h"
#include <iostream>

ComputeExpression::ComputeExpression() : operatorsDescription(NULL), operatorsArraySize(0)
{ }

double ComputeExpression::compute(const char* fileName, const char* expression)
{
	static int counter = 0;

	std::ifstream readFile(fileName, std::ios::in);
	if (!readFile)
		throw std::exception("Cannot open file.");

	readOperator(readFile);

	if (!ValidateExpression::areBracketsValid(expression))
		throw std::exception("Brackets are not valid mathematically.");

	while (*expression)
	{
		Operator* oper = NULL;

		checkIfBrackets(expression);

		if (isdigit(*expression))
		{
			numbers.push(fetchNumber(expression));
			continue;
		}

		if (isOperator(*expression))
			while (checkIfOperator(expression))
			{ }

		++expression;
	}

	while (!operators.isEmpty())
		numbers.push(calculate(numbers.pop(), numbers.pop(), operators.pop()));

	return numbers.pop();
}

int ComputeExpression::checkIfOperator(const char* expression)
{
	Operator* oper = NULL;

	for (int i = 0; i < operatorsArraySize; ++i)
	{
		if (*expression == operatorsDescription[i]->getLetter())
		{
			oper = new Operator(*operatorsDescription[i]);
			break;
		}
	}

	if (operators.isEmpty() || operators.peek()->getSign() == OPEN_BRACKET)
		operators.push(oper);

	else if (operators.peek()->getPriority() > oper->getPriority())
	{
		numbers.push(calculate(numbers.pop(), numbers.pop(), operators.pop()));
		return 1;
	}

	else if (operators.peek()->getPriority() < oper->getPriority())
		operators.push(oper);

	else if (operators.peek()->getAssociativity() == 1 && oper->getAssociativity() == 1)
		operators.push(oper);

	else if (operators.peek()->getAssociativity() == 0 && oper->getAssociativity() == 0)
	{
		numbers.push(calculate(numbers.pop(), numbers.pop(), operators.pop()));
		operators.push(oper);
	}

	else
		throw std::exception("Operators with same priority, but different associativity.");

	return 0;
}

void ComputeExpression::checkIfBrackets(const char* expression)
{
	Operator* oper = NULL;
	if (*expression == OPEN_BRACKET)
		operators.push(new Operator(OPEN_BRACKET, OPEN_BRACKET, -1, -1));

	else if (*expression == CLOSE_BRACKET)
	{
		while ((oper = operators.pop())->getSign() != OPEN_BRACKET)
			numbers.push(calculate(numbers.pop(), numbers.pop(), oper));
	}
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

	while (isdigit(*expression))
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

double ComputeExpression::calculate(double left, double right, const Operator* op)
{
	switch (op->getSign())
	{
		case ADD: return left + right;
		case SUBSTRACT: return left - right;
		case MULTIPLY: return left * right;
		case DIVIDE:
		{
			if (!right)
				throw std::invalid_argument("Division by zero error.");
			return left / right;
		}	
	}
	throw std::invalid_argument("Invalid operator");
}

void ComputeExpression::readOperator(std::ifstream& readFile)
{  
	operatorsDescription = new Operator*[1024];
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

		operatorsDescription[i] = new Operator(letter, sign, priority, associativity);
		++i;
	}

	operatorsArraySize = i;
}