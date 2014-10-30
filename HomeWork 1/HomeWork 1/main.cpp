#include <iostream>
#include "ComputeExpression.h"
#include "ValidateExpression.h"

int main()
{
	try
	{
		ComputeExpression a;
		std::cout << a.compute("test.txt", /*"23 a 25 b (1 c 3) d 2");//*/" 2499 u ( -2618 u 2118 z ( -2772 ) z 4475 l ( -1637 o 1872 i ( -867 t ( 230 l ( -4232 m ( 1933 j -2163 v 595 y ( 3513 j ( -3573 a ( -3659 ) z 2935 l ( 2198 n ( 3798 y 2583 z -3926 c ( 350 a ( -2703 ) ) ) ) ) ) ) ) ) ) ) )") << std::endl;
		std::cout << "vs " << (double)(23 + 25 - (1 / 3) * 2) << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}