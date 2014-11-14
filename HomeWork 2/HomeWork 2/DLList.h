#ifndef DOUBLY_LINKED_DLList
#define DOUBLY_LINKED_DLList

#include "Node.h"
#include <stdexcept>

template <typename T>

class DLList
{
public:
	DLList();
	~DLList();

public:
	int getSize() { return count; }
	bool isEmpty() { return !count; }
	void clear();

public:
	void pushFront(const T &);
	void pushBack(const T &);
	void pushAt(const T &, int);

	T popFront();
	T popBack();
	T popAt(int);

public:
	T& operator[](int);
	const T& operator[](int) const;

private:
	int count;
	Node<T>* first;
	Node<T>* last;

	Node<T>* getAt(int);
};

template <typename T>
DLList<T>::DLList() : first(NULL), last(NULL), count(0)
{ }

template <typename T>
DLList<T>::~DLList()
{
	clear();
}

template <typename T>
void DLList<T>::clear()
{
	while (!isEmpty())
		popBack();
}

template <typename T>
Node<T>* DLList<T>::getAt(int position)
{
	if (position < 0 || position > count)
		throw std::out_of_range("Invalid index!");

	Node<T>* result = NULL;
	if (position < count / 2)
	{
		result = first;
		while (position > 0)
		{
			result = result->next;
			--position;
		}
	}

	else
	{
		result = last;
		while (position < count)
		{
			result = result->prev;
			++position;
		}
	}

	return result;
}

template <typename T>
void DLList<T>::pushFront(const T& element)
{
	if (!count)
	{
		first = new Node<T>(NULL, element, NULL);
		last = first;
	}
	else
	{
		first->prev = new Node<T>(NULL, element, first);
		first = first->prev;
	}
	++count;
}

template <typename T>
void DLList<T>::pushBack(const T& element)
{
	if (!count)
	{
		last = new Node<T>(NULL, element, NULL);
		first = last;
	}
	else
	{
		last->next = new Node<T>(last, element, NULL);
		last = last->next;
	}
	++count;
}

template <typename T>
void DLList<T>::pushAt(const T& element, int position)
{
	if (position < 0 || position > count)
		throw std::out_of_range("Invalid index!");

	if (!position)
		pushFront(element);
	else if (position == count)
		pushBack(element);

	else
	{
		Node<T>* link = getAt(position - 1);
		Node<T>* newElement = new Node<T>(link, element, link->next);
		link->next->prev = newElement;
		link->next = newElement;
		++count;
	}
}

template <typename T>
T DLList<T>::popFront()
{
	if (isEmpty())
		throw std::exception("DLList is empty!");

	T result = first->data;
	Node<T>* courier = first;


	first = first->next;
	courier->next = NULL;

	delete courier;
	--count;

	if (isEmpty())
		last = NULL;
	else
		first->prev = NULL;

	return result;
}

template <typename T>
T DLList<T>::popBack()
{
	if (isEmpty())
		throw std::exception("DLList is empty!");

	if (count == 1)
		return popFront();

	Node<T>* preLast = getAt(count - 1);
	T data = last->data;
	preLast->next = NULL;
	last->prev = NULL;
	delete last;

	last = preLast;
	--count;

	return data;
}

template <typename T>
T DLList<T>::popAt(int position)
{
	if (position < 0 || position >= count)
		throw std::out_of_range("Invalid position!");

	if (!position)
		return popFront();

	if (position == count - 1)
		return popBack();

	Node<T>* preTarget = getAt(position - 1);
	Node<T>* target = preTarget->next;

	T data = target->data;
	preTarget->next = target->next;
	preTarget->next->prev = preTarget;

	target->next = NULL;
	target->prev = NULL;

	delete target;
	--count;
	if (!preTarget->next)
		last = preTarget;

	return data;
}

#endif // DOUBLE_LINKED_DLList
