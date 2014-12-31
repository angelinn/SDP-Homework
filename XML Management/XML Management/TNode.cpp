#include "TNode.h"

TNode::TNode(const Tag& item) : data(item)
{  }

void TNode::sendMe(const TNode* node, std::ostream& output, int tabulations, bool pretty)
{
	std::string empty_spaces;
	std::string new_line;

	if (pretty)
	{
		empty_spaces = std::string(tabulations * 4, ' ');
		new_line = "\n";
	}

	output << empty_spaces << node->data.getNameAndAttributes(pretty);
	if (node->data.getContent() != "")
		output << empty_spaces << node->data.getContent() << new_line;

	if (!node->data.isSelfClosing())
	{
		for (DLList<TNode*>::Iterator iter = node->children.begin(); iter; ++iter)
			sendMe((*iter), output, tabulations + 1, pretty);

		output << empty_spaces << "</" << node->data.getName() << ">" << new_line;
	}
}