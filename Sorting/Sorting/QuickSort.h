#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "SortAbstraction.h"

template <typename T>

class QuickSort : public SortAbstraction < T >
{
public:
	QuickSort();

private:
	virtual void algorithm(T *, size_t);
	size_t partition(T *, size_t);
};

template <typename T>
QuickSort<T>::QuickSort() : SortAbstraction()
{  }

template <typename T>
void QuickSort<T>::algorithm(T* data, size_t size)
{
	if (size <= 1 || !data)
		return;
	
	size_t pos = partition(data, size);
	algorithm(data, pos);
	algorithm(data + pos, size - pos);
}

template <typename T>
size_t QuickSort<T>::partition(T* data, size_t size)
{
	if (size == 2)
	{
		swapIf(data[0], data[1]);
		return 1;
	}

	size_t middle = size / 2;

	swapIf(data[0], data[middle]);
	swapIf(data[0], data[size - 1]);
	swapIf(data[middle], data[size - 1]);
	swap(data[middle], data[size - 2]);

	T& pivot = data[size - 2];
	size_t left = 0;
	size_t right = size - 2;

	while (true)
	{
		while (data[++left] < pivot)
		{  }

		while (data[--right] > pivot)
		{
			if (left == right)
				break;
		}


		if (left >= right)
			break;

		swap(data[left], data[right]);
	}
	swap(data[left], pivot);
	return left;	
}

#endif // QUICK_SORT_H
