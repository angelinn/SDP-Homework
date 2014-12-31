#include "Tree.h"

typedef std::pair<std::string, std::string> string_pair;
typedef DLList<TNode*>::Iterator ListIterator;
typedef void(Tree::*attributeFunction)(const Attribute &, const ListIterator &, const char *);

Tree::Tree() : root(NULL)
{  }

Tree::~Tree()
{
	if (root)
		deleteTree(root);
}

void Tree::deleteTree(TNode*& node)
{
	for (ListIterator iter = node->children.begin(); iter; ++iter)
		deleteTree(*iter);

	delete node;
	node = NULL;
}

void Tree::insertTag(const Tag& item, const char* path)
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
	for (ListIterator iter = resultNodes.begin(); iter; ++iter)
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

void Tree::changeTag(const Tag& item, const char* path)
{
	if (!root)
		throw EmptyTreeOperation("No tags to change.");

	DLList<TNode*> resultNodes;
	getLastNode(path, root, resultNodes);

	for (ListIterator iter = resultNodes.begin(); iter; ++iter)
		(*iter)->data = item;

}

void Tree::removeTag(const char* path, bool cascadeDelete)
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

	for (ListIterator piter = resultNodes.begin(); piter; ++piter)
	{
		for (ListIterator iter = (*piter)->children.begin(); iter; ++iter)
		{
			if ((*iter)->data.getName() == child)
			{
				if ((*iter)->children.getSize() && !cascadeDelete)
					throw CascadeDeleteWarning("There are more tags inside. Please delete them first.");

				ListIterator deleter = iter;
				++iter;
				(*piter)->children.popAt(deleter);
				--iter;
			}
		}
	}
}

void Tree::addAttribute(const Attribute& attribute, const char* path)
{
	manipulateAttribute(attribute, path, &Tree::addAttributeInIterator);
}

void Tree::changeAttribute(const char* oldAttribute, const Attribute& newAttribute, const char* path)
{
	manipulateAttribute(newAttribute, path, &Tree::changeAttributeInIterator, oldAttribute);
}

void Tree::removeAttribute(const Attribute& attribute, const char* path)
{
	manipulateAttribute(attribute, path, &Tree::removeAttributeInIterator);
}

void Tree::getLastNode(const char* path, TNode*& node, DLList<TNode*>& resultNodes)
{
	if (!path)
		throw TreeException("Path is empty.");

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
		for (ListIterator iter = node->children.begin(); iter; ++iter)
			getLastNode(slashPosition + 1, (*iter), resultNodes);
	}

	delete[] result;
	delete[] workPath;
}

void Tree::manipulateAttribute(const Attribute& attribute, const char* path, attributeFunction workAttribute, const char* oldAttribute)
{
	if (!root)
		throw EmptyTreeOperation("tree is empty");

	DLList<TNode*> resultNodes;
	getLastNode(path, root, resultNodes);

	for (ListIterator iter = resultNodes.begin(); iter; ++iter)
		(this->*workAttribute)(attribute, iter, oldAttribute);
}

void Tree::addAttributeInIterator(const Attribute& attribute, const ListIterator& iter, const char* oldAttribute)
{
	(*iter)->data.addAttribute(attribute);
}

void Tree::changeAttributeInIterator(const Attribute& newAttribute, const ListIterator& iter, const char* oldAttribute)
{
	if (!oldAttribute)
		throw InvalidTreeOperation("Old attribute is not present.");

	(*iter)->data.changeAttribute(oldAttribute, newAttribute);
}

void Tree::removeAttributeInIterator(const Attribute& attribute, const ListIterator& iter, const char* oldAttribute)
{
	(*iter)->data.removeAttribute(attribute);
}

void Tree::send(std::ostream& output) const
{
	if (root)
	{
		int tabulations = 0;
		root->sendMe(root, output, tabulations);
	}
}