#include <iostream>
#include "ComputeExpression.h"
#include "ValidateExpression.h"

int main()
{
	ComputeExpression a;
	a.compute("test.txt", "2.321 + 345 + 12312213.23 + -213.1 + 1.4676");


	return 0;
}