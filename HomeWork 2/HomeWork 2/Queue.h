#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"
#include <stdexcept>

template <typename T>
class Queue
{
public:
	Queue();
	~Queue();

public:
	int getSize() const { return count; }
	bool isEmpty() const { return !count; }
	void enqueue(const T &);
	T dequeue();

private:
	Queue(const Queue &);
	Queue& operator=(const Queue &);

private:
	int count;

	Node<T>* first;
	Node<T>* last;

	Node<T>* getAt(int);
};

template <typename T>
Queue<T>::Queue() : first(NULL), last(NULL), count(0)
{ }

template <typename T>
Queue<T>::~Queue()
{
	while (!isEmpty())
		dequeue();
}

template <typename T>
void Queue<T>::enqueue(const T& element)
{
	Node<T>* newFirst = new Node<T>(element, first);
	first = newFirst;

	++count;
	if (count == 1)
		last = first;
}

template <typename T>
Node<T>* Queue<T>::getAt(int position)
{
	if (position >= count)
		throw std::out_of_range("Invalid position!");

	Node<T>* result = first;
	while (position > 0)
	{
		result = result->next;
		--position;
	}

	return result;
}

template <typename T>
T Queue<T>::dequeue()
{
	if (isEmpty())
		throw std::exception("Queue is empty!");

	Node<T>* preLast = getAt(count - 2);
	preLast->next = NULL;

	T data = last->data;
	delete last;
	last = preLast;

	--count;
	return data;
}

#endif // QUEUE_H
