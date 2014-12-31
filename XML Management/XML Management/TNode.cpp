#include "TNode.h"

TNode::TNode(const Tag& item) : data(item)
{  }

void TNode::sendMe(const TNode* node, std::ostream& output, int tabulations)
{
	std::string empty_spaces = std::string(tabulations * 4, ' ');

	output << empty_spaces << node->data.getNameAndAttributes();
	if (node->data.getContent() != "")
		output << empty_spaces << node->data.getContent() << '\n';

	if (!node->data.isSelfClosing())
	{
		for (DLList<TNode*>::Iterator iter = node->children.begin(); iter; ++iter)
			sendMe((*iter), output, tabulations + 1);

		output << empty_spaces << "</" << node->data.getName() << ">\n";
	}
}