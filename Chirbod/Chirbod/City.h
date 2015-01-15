#ifndef CITY_H
#define CITY_H

#include "Crossroad.h"

class City
{
public:
	City(int, int, int);
	~City();

public:
	void enterMe(std::istream &);

private:
	City(const City &);
	City& operator=(const City &);

private:
	void free();

private:
	Crossroad** map;
	int height;
	int width;
};


#endif // CITY_H
