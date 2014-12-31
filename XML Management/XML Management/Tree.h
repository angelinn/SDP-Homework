#ifndef TREE_H
#define TREE_H

#include "TNode.h"
#include "TreeException.h"
#include <iostream>
#include <string>

typedef std::pair<std::string, std::string> string_pair;

class Tree
{
public:
	Tree();
	~Tree();

public:
	void insert(const Tag &, const char *);
	void remove(const char *, bool = false);
	void change(const Tag &, const char *);

	void send(std::ostream &) const;

private:
	Tree(const Tree &);
	Tree& operator=(const Tree &);

private:
	void getLastNode(const char *, TNode *&, DLList<TNode*> &);
	string_pair getParentPath(const char *);

private:
	TNode* root;
	void deleteTree(TNode *&);
};

#endif // TREE_H