#include <iostream>
#include "InsertionSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "HeapSort.h"
#include "CountingSort.h"
#include "SorterTester.h"


int main()
{

	///
	/// Тестовете са върху int и double върху сортиран и разбъркан масив.
	///
	/// Сортировките, които биват тествани са merge, counting, quick и insertion.
	///
	/// Insertion се справя най-зле при голям разбъркан масив, но ако масивът е почти сортиран,
	/// успява да се справи за отрицателно време.
	///
	/// Counting sort за цели числа или обекти , които могат да бъдат каствани към int е много бърз и при 
	/// сортиран и при несортиран масив.
	///
	/// За данните, които съм дал, merge и quick се справят почти за едно и също време.
	///
	try
	{
		size_t count = 4;
		Sorter<int>** sorts = new Sorter<int>*[count] { new MergeSort<int>(), new CountingSort<int>(), 
												   new QuickSort<int>(), new InsertionSort<int>() };

		SorterTester<int> intTester(sorts, count);
		intTester.testUnsortedArray();
		intTester.getSummary(std::cout);
		intTester.testSortedArray();
		intTester.getSummary(std::cout);

		for (int i = 0; i < 4; ++i)
			delete sorts[i];

		Sorter<double>** dsorts = new Sorter<double>*[count] { new MergeSort<double>(), new CountingSort<double>(),
														   new QuickSort<double>(), new InsertionSort<double>() };
		SorterTester<double> doubleTester(dsorts, count);
		doubleTester.testUnsortedArray();
		doubleTester.getSummary(std::cout);
		doubleTester.testSortedArray();
		doubleTester.getSummary(std::cout);
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Unexpected error occured." << std::endl;
	}
}