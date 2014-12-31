#include <crtdbg.h>
#include "XMLManager.h"

//std::pair<std::string, std::string> getParentPath(const char*);

int main()
{
	try
	{
		XMLManager manager(std::cout);
		Attribute dsa("this", "very_good");
		Tag a("root", "Very root.");
		Tag b("person");
		Tag c("email", "MAIMUNKA@HOTMAIL.COM");
		manager.addTag(a, "");
		manager.addTag(b, "root");
		manager.addTag(c, "root/person");
		manager.addAttribute(dsa, "root/person/email");
		manager.changeAttribute(dsa.getKey().c_str(), "boomshakalaka", "root/person/email");
		manager.removeAttribute("boomshakalaka", "root/person/email");
		//manager.removeTag("root/person", true);
		manager.print();

		//const char* str = "root/email/job";
		//std::pair<std::string, std::string> pair = getParentPath(str);
		//std::cout << pair.first << " " << pair.second << std::endl;


	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	_CrtDumpMemoryLeaks();
}