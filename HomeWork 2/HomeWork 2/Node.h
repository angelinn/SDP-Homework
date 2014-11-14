#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

template <typename T>

class Node
{
public:
	Node(Node<T> *, const T &, Node<T> *);
	Node(const Node<T> &);

	Node<T>* next;
	Node<T>* prev;
	T data;
};

template <typename T>
Node<T>::Node(Node<T>* nPrev, const T& item, Node<T>* nNext) : prev(nPrev), next(nNext), data(item)
{ }

template <typename T>
Node<T>::Node(const Node<T>& n)
{
	prev = n.prev ? new Node(*n.prev) : NULL;
	next = n.next ? new Node(*n.next) : NULL;

	data = n.data;
}

#endif // NODE_H
