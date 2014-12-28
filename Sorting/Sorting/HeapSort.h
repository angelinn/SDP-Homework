#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include "SortAbstraction.h"

template <typename T>

class HeapSort : public SortAbstraction < T >
{
public:
	HeapSort();

public:
	virtual void algorithm(T *, size_t);
};

template <typename T>
HeapSort<T>::HeapSort() : SortAbstraction()
{  }

template <typename T>
void HeapSort<T>::algorithm(T* data, size_t size)
{

}

#endif // HEAP_SORT_H
