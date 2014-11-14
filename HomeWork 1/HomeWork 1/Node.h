#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
public:
	Node(const T &);

public:
	T getData() const { return data; }
	const Node<T>* getNext() const { return next; }
	void setNext(Node<T>* nxt) { next = nxt; }

private:
	T data;
	Node<T>* next;
};

template <typename T>
Node<T>::Node(const T& newData) : next(NULL), data(newData)
{ }

#endif // NODE_H
