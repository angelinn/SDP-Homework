#include <crtdbg.h>
#include "XMLCreator.h"

int main()
{
	{
		XMLCreator creator;
		creator.insertTag("<xml>");
		creator.insertTag("<name>", "<xml>");
		creator.markers.print();

	}

	_CrtDumpMemoryLeaks();
}