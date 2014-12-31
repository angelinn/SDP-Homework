#include <crtdbg.h>
#include "CLI.h"

//std::pair<std::string, std::string> getParentPath(const char*);

int main()
{
	try
	{
		CLI iface;
		iface.go();
		//XMLManager manager(std::cout);
		//Attribute dsa("this", "very_good");
		//Tag a("root");
		//Tag b("person");
		//Tag c("name", "Something");
		//Tag d("name", "One");
		//Tag e("email", true);
		//Tag f("name", "Two");
		//Tag g("email", "example@example.com");
		//manager.addTag(a, "");
		//manager.addTag(b, "root");
		//manager.addTag(c, "root/person");
		//manager.addTag(d, "root/person");
		//manager.addTag(e, "root/person");

		//manager.addTag(b, "root");
		//manager.addTag(f, "root/person");
		//manager.addTag(g, "root/person");
		//manager.addAttribute(dsa, "root/person/email");
		//manager.changeAttribute(dsa.getKey().c_str(), "boomshakalaka", "root/person/email");
		//manager.removeAttribute("boomshakalaka", "root/person/email");
		//manager.removeTag("root/person", true);
		//manager.print();

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