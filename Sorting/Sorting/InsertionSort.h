#ifndef INSERTION_SORT
#define INSERTION_SORT

#include "SortAbstraction.h"

template <typename T>

class InsertionSort : public SortAbstraction< T >
{
public:
	InsertionSort();

private:
	virtual void algorithm(T *, size_t);
};

template <typename T>
InsertionSort<T>::InsertionSort() : SortAbstraction()
{  }

template <typename T>
void InsertionSort<T>::algorithm(T* data, size_t size)
{
	for (size_t i = 1; i < size; ++i)
	{
		T current(data[i]);
		size_t j = i;

		while (data[j - 1] > current)
		{
			data[j] = data[j - 1];
			--j;
		}
		data[j] = current;
	}
}

#endif // INSERTION_SORT
