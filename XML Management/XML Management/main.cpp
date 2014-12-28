#include <crtdbg.h>
#include "XMLCreator.h"

int main()
{
	{
		XMLCreator creator;
		creator.insertTag("<xml>");
		creator.insertTag("<name>", "<xml>");
		creator.insertTag("<ID>", "<xml>");
		creator.insertTag("<years>", "<name>");
		creator.markers.print();

	}

	_CrtDumpMemoryLeaks();
}