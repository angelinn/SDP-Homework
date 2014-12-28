#ifndef SORTER_H
#define SORTER_H

template<typename T>

class Sorter
{
public:
	virtual void sort(T * data, size_t count) = 0;
	virtual unsigned long long getSortTime() const = 0;
};

#endif // SORTER_H
