#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <string>

class Attribute
{
public:
	Attribute(std::string& k) : key(k) {  }
	Attribute(std::string& k, std::string& v) : key(k), value(v) {  }

public:
	std::string getKey() const { return key; }
	std::string getValue() const { return value; }

	void setKey(std::string& other) { key = other; }
	void setValue(std::string& other) { key = other; }

private:
	std::string key;
	std::string value;
};


#endif // ATTRIBUTE_H
