#ifndef SORT_TESTER_H
#define SORT_TESTER_H

template<typename T>

class SortTester 
{
public:
	SortTester(Sorter<T> ** sorters, int count) {}
	virtual void getSummary(std::ostream & out) = 0;
};

#endif // SORT_TESTER_H
