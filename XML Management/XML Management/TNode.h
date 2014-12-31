#ifndef TNODE_H
#define TNODE_H

#include "DLList.h"
#include "Tag.h"
#include <ostream>

class TNode
{
public:
	TNode(const Tag &);// , const TNode *);

	//TNode* parent;
	DLList<TNode*> children;
	Tag data;

public:
	bool operator==(const char* other) { return data == other; }
	bool operator!=(const char* other) { return !(*this == other); }
	void sendMe(const TNode *, std::ostream &, int);

private:
	TNode(const TNode &);
	TNode& operator=(const TNode &);
};

#endif // TNODE_H