#ifndef COUNTING_SORT_H
#define COUNTING_SORT_H

#include "SortAbstraction.h"

template <typename T>

class CountingSort : public SortAbstraction < T >
{
public:
	CountingSort();

private:
	virtual void algorithm(T *, size_t);

	int maxKey(T *, size_t);
	int key(const T &) const;
};

template <typename T>
CountingSort<T>::CountingSort() : SortAbstraction()
{  }

template <typename T>
void CountingSort<T>::algorithm(T* data, size_t size)
{
	int max = maxKey(data, size);

	int* counter = new int[max + 1];
	memset(counter, 0, sizeof(int) * (max + 1));

	for (size_t i = 0; i < size; ++i)
		++counter[key(data[i])];

	for (int i = 1; i <= max; ++i)
		counter[i] += counter[i - 1];

	T* sorted = new T[size];

	size_t i = size;
	size_t position = 0;

	while (i--)
	{
		position = --counter[key(data[i])];
		sorted[position] = data[i];
	}

	for (size_t i = 0; i < size; ++i)
		data[i] = sorted[i];

	delete[] counter;
	delete[] sorted;
}

template <typename T>
int CountingSort<T>::maxKey(T* data, size_t size)
{
	int max = 0;

	int nextKey = 0;

	for (size_t i = 0; i < size; ++i)
	{
		nextKey = key(data[i]);
		if (nextKey > max)
			max = nextKey;
	}

	return max;
}

template <typename T>
int CountingSort<T>::key(const T& value) const
{
	return static_cast<int> (value);
}


#endif // COUNTING_SORT_H
