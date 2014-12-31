#include <crtdbg.h>
#include "CLI.h"

int main()
{
	try
	{
		CLI iface;
		iface.go();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	_CrtDumpMemoryLeaks();
}