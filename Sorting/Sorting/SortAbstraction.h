#ifndef SORT_ABSTRACTION
#define SORT_ABSTRACTION

#include "Sorter.h"
#include <ctime>
#include <stdexcept>

template <typename T>

class SortAbstraction : public Sorter < T >
{
public:
	SortAbstraction();

public:
	virtual void sort(T *, size_t);
	virtual unsigned long long getSortTime() const;

protected:
	virtual void algorithm(T *, size_t) = 0;
	void swapIf(T &, T &);
	void swap(T &, T &);

protected:
	unsigned long long lastSortingTime;
};

template <typename T>
SortAbstraction<T>::SortAbstraction() : lastSortingTime(-1)
{  }

template <typename T>
void SortAbstraction<T>::sort(T* data, size_t size)
{
	if (!data || !size)
		throw std::invalid_argument("Null size or pointer found");

	clock_t start = clock();

	algorithm(data, size);

	clock_t end = clock();
	lastSortingTime = end - start;
}

template <typename T>
unsigned long long SortAbstraction<T>::getSortTime() const
{
	if (lastSortingTime == -1)
		throw std::exception("Sorting must be called first.");

	return lastSortingTime;
}

template <typename T>
void SortAbstraction<T>::swapIf(T& one, T& other)
{
	if (one > other)
		swap(one, other);
}

template <typename T>
void SortAbstraction<T>::swap(T& one, T& other)
{
	T courier = one;
	one = other;
	other = courier;
}

#endif // SORT_ABSTRACTION
