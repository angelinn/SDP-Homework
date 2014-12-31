#ifndef TREE_H
#define TREE_H

#include "TNode.h"
#include "TreeException.h"
#include <iostream>
#include <string>

class Tree
{
public:
	Tree();
	~Tree();

	typedef std::pair<std::string, std::string> string_pair;
	typedef DLList<TNode*>::Iterator ListIterator;
	typedef void(Tree::*attributeFunction)(const Attribute &, const ListIterator &, const char *);

public:
	void insertTag(const Tag &, const char *);
	void removeTag(const char *, bool = false);
	void changeTag(const Tag &, const char *);

	void send(std::ostream &) const;

	void addAttribute(const Attribute &, const char *);
	void changeAttribute(const char *, const Attribute &, const char *);
	void removeAttribute(const Attribute &, const char *);

private:
	Tree(const Tree &);
	Tree& operator=(const Tree &);

private:
	void manipulateAttribute(const Attribute &, const char *, attributeFunction, const char * = NULL);
	void addAttributeInIterator(const Attribute &, const ListIterator &, const char *);
	void changeAttributeInIterator(const Attribute &, const ListIterator &, const char *);
	void removeAttributeInIterator(const Attribute &, const ListIterator &, const char *);

private:
	void getLastNode(const char *, TNode *&, DLList<TNode*> &);
	string_pair getParentPath(const char *);

private:
	TNode* root;
	void deleteTree(TNode *&);
};

#endif // TREE_H