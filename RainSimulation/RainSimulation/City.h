#ifndef CITY_H
#define CITY_H

#include "Crossroad.h"
#include <iostream>

class City
{
public:
	City();
	City(const City &);
	City& operator=(const City &);
	~City();

public:
	void create(int, int, int, std::istream &);
	void enterMe(std::istream &);
	void workMe();
	void printMe(std::ostream &) const;
	void water(int);

private:
	void allocate();
	void copyFrom(const City &);
	void free();

private:
	Crossroad** map;
	int height;
	int width;
};


#endif // CITY_H
