#ifndef QUEUE_H
#define QUEUE_H

#include "DLList.h"
#include <stdexcept>

template <typename T>
class Queue
{
public:
	int getSize() const { return list.getSize(); }
	bool isEmpty() const { return list.isEmpty(); }

public:
	void clear();
	void enqueue(const T &);
	T dequeue();
	T& peek();

private:
	DLList<T> list;
};

template <typename T>
void Queue<T>::clear()
{
	list.clear();
}

template <typename T>
void Queue<T>::enqueue(const T& element)
{
	list.pushFront(element);
}

template <typename T>
T Queue<T>::dequeue()
{
	return list.popBack();
}

template <typename T>
T& Queue<T>::peek()
{
	return list.peek();
}

#endif // QUEUE_H
