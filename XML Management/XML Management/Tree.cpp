#include "Tree.h"

Tree::Tree() : root(NULL)
{  }

Tree::~Tree()
{
	if (root)
		deleteTree(root);
}

void Tree::deleteTree(TNode*& node)
{
	for (DLList<TNode*>::Iterator iter = node->children.begin(); iter; ++iter)
		deleteTree(*iter);

	delete node;
	node = NULL;
}

void Tree::insert(const Tag& item, const char* path)
{
	if (!root)
	{
		if (!strstr(path, "/"))
		{
			root = new TNode(item);
			return;
		}
		throw InvalidTreeOperation("Wrong Path inserted.");
	}
	DLList<TNode*> resultNodes;

	getLastNode(path, root, resultNodes);
	for (DLList<TNode*>::Iterator iter = resultNodes.begin(); iter; ++iter)
		(*iter)->children.pushBack(new TNode(item));
}

string_pair Tree::getParentPath(const char* path)
{
	std::string workPath(path);

	size_t lastBackslash = workPath.rfind("/");


	if (lastBackslash == std::string::npos)
		throw TreeException("Something went wrong with string splitting.");

	std::string parent(workPath, 0, lastBackslash);
	std::string child(workPath, lastBackslash + 1, workPath.size() - 1);
	
	return string_pair(parent, child);
}

void Tree::change(const Tag& item, const char* path)
{
	if (!root)
		throw EmptyTreeOperation("No tags to change.");

	DLList<TNode*> resultNodes;
	getLastNode(path, root, resultNodes);

	for (DLList<TNode*>::Iterator iter = resultNodes.begin(); iter; ++iter)
		(*iter)->data = item;

}

void Tree::remove(const char* path, bool cascadeDelete)
{
	if (!root)
		throw EmptyTreeOperation("No tags to remove.");
	
	if (root->data == path)
	{
		deleteTree(root);
		return;
	}

	string_pair pair = getParentPath(path);

	const char* parent = pair.first.c_str();
	std::string& child = pair.second;

	DLList<TNode*> resultNodes;
	getLastNode(parent, root, resultNodes);

	for (DLList<TNode*>::Iterator piter = resultNodes.begin(); piter; ++piter)
	{
		for (DLList<TNode*>::Iterator iter = (*piter)->children.begin(); iter; ++iter)
		{
			if ((*iter)->data.getName() == child)
			{
				if ((*iter)->children.getSize() && !cascadeDelete)
					throw CascadeDeleteWarning("There are more tags inside. Please delete them first.");

				DLList<TNode*>::Iterator deleter = iter;
				++iter;
				(*piter)->children.popAt(deleter);
				--iter;
			}
		}
	}
}

void Tree::getLastNode(const char* path, TNode*& node, DLList<TNode*>& resultNodes)
{
	char* workPath = new char[strlen(path) + 1];
	strcpy(workPath, path);

	char* slashPosition = strstr(workPath, "/");

	if (!slashPosition)
	{
		if (*node == path)
		{
			delete[] workPath;

			resultNodes.pushBack(node);
			return;
		}
		else
			throw InvalidTreeOperation("Unsupported tag entered.");
	}

	char* result = new char[strlen(workPath) + 1];

	int i = 0;
	while (workPath[i] != *slashPosition)
	{
		result[i] = workPath[i];

		++i;
	}
	result[i] = '\0';

	if (*node == result)
	{
		for (DLList<TNode*>::Iterator iter = node->children.begin(); iter; ++iter)
			getLastNode(slashPosition + 1, (*iter), resultNodes);
	}

	delete[] result;
	delete[] workPath;
}

void Tree::send(std::ostream& output) const
{
	if (root)
	{
		int tabulations = 0;
		root->sendMe(root, output, tabulations);
	}
}