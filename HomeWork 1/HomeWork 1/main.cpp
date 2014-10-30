#include <iostream>
#include "ComputeExpression.h"
#include "ValidateExpression.h"

int main()
{
	std::cout << std::boolalpha << ValidateExpression::isValid("31 a (( 5 b 32 f 10 e -230 ) c 324 d 17") << std::endl;


	return 0;
}