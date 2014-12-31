#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <string>

class Attribute
{
public:
	Attribute(const char* k) : key(k) {  }
	Attribute(const char* k, const char* v) : key(k), value(v) {  }

public:
	std::string getKey() const { return key; }
	std::string getValue() const { return value; }

	void setKey(const char* other) { key = other; }
	void setValue(const char* other) { key = other; }

private:
	std::string key;
	std::string value;
};


#endif // ATTRIBUTE_H
