#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "Sorter.h"

template <typename T>
class MergeSort : public SortAbstraction < T >
{
public:
	MergeSort();

private:
	virtual void algorithm(T *, size_t);

	virtual void step(T *, int, int, T *);
	virtual void merge(T *, size_t, size_t, size_t, size_t, T *);
};

template <typename T>
MergeSort<T>::MergeSort() : SortAbstraction()
{  }

template <typename T>
void MergeSort<T>::algorithm(T* data, size_t size)
{
	int beg = 0;
	int end = size - 1;

	T* buffer = new T[size];
	step(data, beg, end, buffer);

	delete[] buffer;
}

template <typename T>
void MergeSort<T>::step(T* data, int beg, int end, T* buffer)
{
	if (beg < end)
	{
		size_t middle = (end + beg) / 2;

		step(data, beg, middle, buffer);
		step(data, middle + 1, end, buffer);
		merge(data, beg, middle, middle + 1, end, buffer);
	}
}

template <typename T>
void MergeSort<T>::merge(T* data, size_t firstStart, size_t firstEnd, size_t secondStart, size_t secondEnd, T* buffer)
{
	size_t firstStartCopy = firstStart;
	size_t secondStartCopy = secondStart;
	size_t bufferIndex = firstStart;

	while (firstStartCopy <= firstEnd && secondStartCopy <= secondEnd)
	{
		if (data[firstStartCopy] < data[secondStartCopy])
			buffer[bufferIndex++] = data[firstStartCopy++];
		else
			buffer[bufferIndex++] = data[secondStartCopy++];
	}

	while (firstStartCopy <= firstEnd)
		buffer[bufferIndex++] = data[firstStartCopy++];

	while (secondStartCopy <= secondEnd)
		buffer[bufferIndex++] = data[secondStartCopy++];

	for (size_t i = firstStart; i < secondEnd; ++i)
		data[i] = buffer[i];
}

#endif // MERGE_SORT_H
