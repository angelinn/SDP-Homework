#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

#include "DNode.h"
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
	class Iterator
	{
	public:
		Iterator& operator++();
		const Iterator& operator++() const;

		bool operator==(const Iterator &) const;
		bool operator!=(const Iterator &) const;
		T operator*() const;

	private:
		Iterator(DNode<T> *);

	private:
		mutable DNode<T>* current;

		friend class DLList;
	};

	Iterator begin()
	{
		return Iterator(first);
	}

	Iterator end()
	{
		return Iterator(last);
	}

private:
	DLList(const DLList &);
	DLList& operator=(const DLList &);

private:
	int count;
	DNode<T>* first;
	DNode<T>* last;

	DNode<T>* getAt(int);
};

template <typename T>
DLList<T>::Iterator::Iterator(DNode<T>* curr) : current(curr)
{  }

template <typename T>
const typename DLList<T>::Iterator& DLList<T>::Iterator::operator++() const
{
	if (current)
		current = current->next;

	return *this;
}

template <typename T>
typename DLList<T>::Iterator& DLList<T>::Iterator::operator++()
{
	return const_cast<DLList<T>::Iterator&> (static_cast<const DLList<T>::Iterator &> (*this).operator++());
}

template <typename T>
bool DLList<T>::Iterator::operator==(const Iterator& other) const
{
	return current == other.current;
}

template <typename T>
bool DLList<T>::Iterator::operator!=(const Iterator& other) const
{
	return ! ((*this) == other);
}

template <typename T>
T typename DLList<T>::Iterator::operator*() const
{
	if (current)
		return current->data;

	throw std::exception("No element selected.");
}

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
DNode<T>* DLList<T>::getAt(int position)
{
	if (position >= count)
		throw std::out_of_range("Invalid index!");

	DNode<T>* result = NULL;
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
		while (position < count - 1)
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
		first = new DNode<T>(NULL, element, NULL);
		last = first;
	}
	else
	{
		first->prev = new DNode<T>(NULL, element, first);
		first = first->prev;
	}
	++count;
}

template <typename T>
void DLList<T>::pushBack(const T& element)
{
	if (!count)
	{
		last = new DNode<T>(NULL, element, NULL);
		first = last;
	}
	else
	{
		last->next = new DNode<T>(last, element, NULL);
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
		DNode<T>* link = getAt(position - 1);
		DNode<T>* newElement = new DNode<T>(link, element, link->next);
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
	DNode<T>* courier = first;


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

	DNode<T>* preLast = getAt(count - 2);
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

	DNode<T>* preTarget = getAt(position - 1);
	DNode<T>* target = preTarget->next;

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

//template <typename T>
//const T& DLList<T>::operator[](int index) const
//{
//	return getAt(index - 1)->data;
//}
//
//template <typename T>
//T& DLList<T>::operator[](int index)
//{
//	return const_cast<T &> (static_cast<const DLList<T>> (*this)[index]);
//}

#endif // DOUBLE_LINKED_DLList
