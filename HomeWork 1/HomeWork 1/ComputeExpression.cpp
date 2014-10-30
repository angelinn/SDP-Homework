#include "ComputeExpression.h"
#include "ValidateExpression.h"
#include "operatorsConstants.h"
#include "Stack.h"
#include "Operator.h"
#include <iostream>


double ComputeExpression::compute(const char* fileName, const char* expression)
{
	static int counter = 0;

	std::ifstream readFile(fileName, std::ios::in);
	if (!readFile)
		throw std::exception("Cannot open file.");

	int operatorsArraySize = 0;
	Operator** operatorsDescription = readOperator(readFile, operatorsArraySize);

	if (!ValidateExpression::areBracketsValid(expression))
		throw std::exception("Brackets are not valid mathematically.");

	Stack<double> numbers;
	Stack<Operator*> operators;

	while (*expression)
	{
		Operator* oper = NULL;

		else if (isdigit(*expression))
		{
			numbers.push(fetchNumber(expression));
			continue;
		}

		else if (isOperator(*expression))
		{
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
				continue;
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
		}

		++expression;
	}

	while (!operators.isEmpty())
		numbers.push(calculate(numbers.pop(), numbers.pop(), operators.pop()));

	return numbers.pop();
}

void ComputeExpression::checkIfBrackets(Stack<double>& numbers, Stack<Operator*>& operators)
{

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