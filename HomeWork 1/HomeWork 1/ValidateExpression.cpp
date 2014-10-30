#include "ValidateExpression.h"

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