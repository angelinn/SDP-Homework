#include <iostream>
#include "ComputeExpression.h"
#include "ValidateExpression.h"

int main()
{
	try
	{
		ComputeExpression a;
		std::cout << std::fixed << a.compute("test.txt", "4378 c -1960 z ( 4064 ) n 1386 w ( -607 ) o -2002 d ( -589 w -4549 ) o ( 2992 ) v ( 2722 h ( -1800 n -3402 k ( -594 ) e -4408 r -3959 p 3843 i ( -1072 ) f ( 2494 f ( -2416 g -4575 ) v 1598 ) t ( -439 n 4333 d 3653 ) ) )") << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}