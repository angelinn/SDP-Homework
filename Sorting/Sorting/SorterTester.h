#ifndef SORTER_TEST_H
#define SORTER_TEST_H

#include "SortTester.h"
#include "Sorter.h"
#include <ostream>
#include <string>

template <typename T>

class SorterTester : public SortTester < T >
{
public:
	SorterTester(Sorter<T> ** sorters, int count);
	~SorterTester();

public:
	virtual void getSummary(std::ostream &);
	void testUnsortedArray();
	void testSortedArray();

private:
	SorterTester(const SorterTester &);
	SorterTester& operator=(const SorterTester &);

private:
	T* randomStuff;
	Sorter<T>** sorters;
	int count;

	T* generateData(size_t, bool=false);
	void copyArr(T *&, T *, size_t);

};

template <typename T>
SorterTester<T>::SorterTester(Sorter<T>** sorts, int cnt) : SortTester(sorts, cnt), sorters(sorts), count(cnt), randomStuff(NULL)
{  }

template <typename T>
SorterTester<T>::~SorterTester()
{
	delete[] randomStuff;
}

template <typename T>
void SorterTester<T>::testUnsortedArray()
{
	int top = rand() % 30000 + 20000;

	randomStuff = generateData(top);

	T* copy = new T[top];
	copyArr(copy, randomStuff,  top);

	for (int i = 0; i < count; ++i)
	{
		sorters[i]->sort(randomStuff, top);
		copyArr(randomStuff, copy, top);
	}

	delete[] copy;
}

template <typename T>
void SorterTester<T>::testSortedArray()
{
	int top = 100000;//rand() % 30000 + 20000;

	randomStuff = generateData(top, true);

	T* copy = new T[top];
	copyArr(copy, randomStuff, top);

	for (int i = 0; i < count; ++i)
	{
		sorters[i]->sort(randomStuff, top);
		copyArr(randomStuff, copy, top);
	}

	delete[] copy;
}

template <typename T>
void SorterTester<T>::copyArr(T*& dest, T* src, size_t size)
{
	if (dest)
	{
		delete[] dest;
		dest = new T[size];
	}

	for (int i = 0; i < size; ++i)
		dest[i] = src[i];
}

template <typename T>
T* SorterTester<T>::generateData(size_t size, bool sorted)
{
	T* result = new T[size];
	for (size_t i = 0; i < size; ++i)
	{
		T value = sorted ? i : size - i;
		if (typeid(T) == typeid(double))
			result[i] = value / 100.0;

		else if (typeid(T) == typeid(int))
			result[i] = value;
	}
	return result;
}

template <typename T>
void SorterTester<T>::getSummary(std::ostream& out)
{
	int bufferSize = 1024;

	char* summary = new char[bufferSize];
	strcpy(summary, "Sorting Tests: Sorting on ");
	strcat(summary, typeid(T).name());
	strcat(summary, "\n");


	char* intString = new char[bufferSize];
	for (int i = 0; i < count; ++i)
	{
		strcat(summary, "Sort[");
		_itoa(i, intString, 10);
		strcat(summary, intString);
		strcat(summary, "] took ");
		_itoa(sorters[i]->getSortTime(), intString, 10);
		strcat(summary, intString);
		strcat(summary, "\n");
	}
	out << summary;

	delete[] summary;
	delete[] intString;
}

#endif // INT_SORTER_TEST_H
