#include "ValidateExpression.h"
#include <iostream>
#include <cstring>
#include "Stack.h"

bool ValidateExpression::areBracketsValid(const char* expression)
{
	const char OPEN_BRACKET = '(';
	const char CLOSE_BRACKET = ')';

	int bracketsCount = 0;

	while (*expression)
	{
		if (*expression == OPEN_BRACKET)
			++bracketsCount;
		else if (*expression == CLOSE_BRACKET)
			--bracketsCount;

		if (bracketsCount < 0)
			return false;

		++expression;
	}

	return !bracketsCount;
}

bool ValidateExpression::isThereSamePriorAndAssoc(const char* expression)
{
	return true;
}

bool ValidateExpression::isValid(const char* expression)
{
	return areBracketsValid(expression);
}