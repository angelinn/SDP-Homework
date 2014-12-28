#ifndef TREE_H
#define TREE_H

#include "TNode.h"
#include "InvalidTreeOperation.h"
#include <iostream>
#include <string>

template <typename T>
class Tree
{
public:
	Tree();
	~Tree();

public:
	void insertNext(const T &);
	bool insert(const T &, const T &, const TNode<T>* node = NULL);
	void insert(const T &);

	void print() const
	{
		std::cout << root->data << std::endl;
		for (DLList<TNode<T>*>::Iterator iter = root->children.begin(); iter; ++iter)
			std::cout << (*iter)->data << " ";
		std::cout << std::endl;
	}

private:
	Tree(const Tree<T> &);
	Tree<T>& operator=(const Tree<T> &);

private:
	TNode<T>* root;
	void deleteTree(TNode<T> *&);
};

template <typename T>
Tree<T>::Tree() : root(NULL)
{  }

template <typename T>
Tree<T>::~Tree()
{
	if (root)
		deleteTree(root);
}

template <typename T>
void Tree<T>::deleteTree(TNode<T>*& node)
{
	for (DLList<TNode<T>*>::Iterator iter = node->children.begin(); iter; ++iter)
		deleteTree(*iter);

	delete node;
	node = NULL;
}

template <typename T>
bool Tree<T>::insert(const T& item, const T& in, const TNode<T>* node)
{
	if (!root)
		root = new TNode<T>(item);
	else if (root->data == in)
	{
		root->children.pushBack(new TNode<T>(item));
		return true;
	}

	if (!root->children.isEmpty())
	{
		for (DLList<TNode<T>*>::Iterator iter = root->children.begin(); iter; ++iter)
			if (insert(item, in, *iter))
				break;
	}
	return false;
}

template <typename T>
void Tree<T>::insert(const T& item)
{
	if (!root)
		root = new TNode<T>(item);
	else
		throw InvalidTreeOperation("root not null");
}

template <typename T>
void Tree<T>::insertNext(const T& item)
{
	if (root)
		root->children.pushBack(item);
}


#endif // TREE_H