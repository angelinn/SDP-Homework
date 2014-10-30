#include "ValidateExpression.h"
#include "operatorsConstants.h"

///
/// Checks if the brackets in the expression are mathematically valid
///
bool ValidateExpression::areBracketsValid(const char* expression)
{
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