#include "ComputeExpression.h"
#include "ValidateExpression.h"
#include "operatorsConstants.h"
#include "Stack.h"
#include "Operator.h"
#include <iostream>
///
/// C-tor to set the default values
///
ComputeExpression::ComputeExpression() : operatorsDescription(NULL), operatorsArraySize(0)
{ }

///
/// D-tor - Deletes the operators array
///
ComputeExpression::~ComputeExpression()
{
	for (int i = 0; i < operatorsArraySize; ++i)
		delete operatorsDescription[i];

	delete operatorsDescription;
}

///
/// Computes the given expression by the description of the operators in the given file name
///
double ComputeExpression::compute(const char* fileName, const char* expression)
{
	std::ifstream readFile(fileName, std::ios::in);
	if (!readFile)
		throw std::exception("Cannot open file.");

	readOperator(readFile);

	if (!ValidateExpression::areBracketsValid(expression))
		throw std::exception("Brackets are not valid mathematically.");

	Operator* oper = NULL;

	while (*expression)
	{
		checkIfBrackets(expression, oper);

		if (isdigit(*expression))
		{
			numbers.push(fetchNumber(expression));
			continue;
		}

		if (isOperator(*expression))
			while (checkIfOperator(expression, oper))
			{ }

		++expression;
	}

	while (!operators.isEmpty())
		numbers.push(calculate(numbers.pop(), numbers.pop(), operators.pop()));

	delete oper;
	return numbers.pop();
}

///
/// If the given element is an operator, the function decides what to do with it,
/// depending on the previous operator in the stack
///
int ComputeExpression::checkIfOperator(const char* expression, Operator* oper)
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

	//delete oper;
	return 0;
}

///
/// Checks if the current character is a bracket and decides what to do with it
///
void ComputeExpression::checkIfBrackets(const char* expression, Operator* oper)
{
	if (*expression == OPEN_BRACKET)
		operators.push(new Operator(OPEN_BRACKET, OPEN_BRACKET, -1, -1));

	else if (*expression == CLOSE_BRACKET)
	{
		while ((oper = operators.pop())->getSign() != OPEN_BRACKET)
			numbers.push(calculate(numbers.pop(), numbers.pop(), oper));
	}
}

///
/// Gets the number that starts with a digit from the expression
/// Works with -, and increases the expression pointer
///
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

///
/// Checks if the character is an operator
///
bool ComputeExpression::isOperator(char c)
{
	return isalpha(c);
}

///
/// Does the actual math calculation! Brrr, let's get outta here faster!
///
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

///
/// Reads the operators from the given file into the field called operatorsDescription
///
void ComputeExpression::readOperator(std::ifstream& readFile)
{  
	const int OPERATORS_SIZE = 1024;

	operatorsDescription = new Operator*[OPERATORS_SIZE];
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