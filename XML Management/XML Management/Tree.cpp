#include "Tree.h"

typedef std::pair<std::string, std::string> string_pair;
typedef DLList<TNode*>::Iterator ListIterator;
typedef void(Tree::*attributeFunction)(const Attribute &, const ListIterator &, const char *);

Tree::Iterator::Iterator(TNode* curr)
{
	nodes.enqueue(curr);
}

const Tree::Iterator& Tree::Iterator::operator++() const
{
	TNode* current = nodes.dequeue();
	for (ListIterator iter = current->children.begin(); iter; ++iter)
		nodes.enqueue((*iter));

	return *this;
}

Tree::Iterator& Tree::Iterator::operator++()
{
	return const_cast<Tree::Iterator&> (static_cast<const Tree::Iterator &> (*this).operator++());
}

bool Tree::Iterator::operator==(const Iterator& other) const
{
	return nodes.peek() == other.nodes.peek();
}

bool Tree::Iterator::operator!=(const Iterator& other) const
{
	return !((*this) == other);
}

Tag& Tree::Iterator::operator*()
{
	if (nodes.peek())
		return nodes.peek()->data;

	throw TreeException("No element selected!");
}

Tag Tree::Iterator::operator*() const
{
	if (nodes.peek())
		return nodes.peek()->data;

	throw TreeException("No element selected!");
}

Tree::Iterator Tree::begin() const
{
	return Iterator(root);
}

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

void Tree::insertTag(const Tag& item, std::string& path)
{
	if (!root)
	{
		if (path.find("/") == std::string::npos)
		{
			root = new TNode(item);
			return;
		}
		throw InvalidTreeOperation("Wrong Path inserted.");
	}
	DLList<TNode*> resultNodes;

	getLastNode(path.c_str(), root, resultNodes);

	for (ListIterator iter = resultNodes.begin(); iter; ++iter)
		(*iter)->children.pushBack(new TNode(item));
}

string_pair Tree::getParentPath(std::string& path)
{
	std::string workPath(path);

	size_t lastBackslash = workPath.rfind("/");


	if (lastBackslash == std::string::npos)
		throw TreeException("Something went wrong with string splitting.");

	std::string parent(workPath, 0, lastBackslash);
	std::string child(workPath, lastBackslash + 1, workPath.size() - 1);
	
	return string_pair(parent, child);
}

void Tree::changeTag(const Tag& item, std::string& path)
{
	if (!root)
		throw EmptyTreeOperation("No tags to change.");

	DLList<TNode*> resultNodes;
	getLastNode(path.c_str(), root, resultNodes);

	for (ListIterator iter = resultNodes.begin(); iter; ++iter)
		(*iter)->data = item;

}

void Tree::removeTag(std::string& path, bool cascadeDelete)
{
	if (!root)
		throw EmptyTreeOperation("No tags to remove.");
	
	if (root->data.getName() == path)
	{
		if (!root->children.isEmpty() && !cascadeDelete)
			throw CascadeDeleteWarning("There are more tags inside. Please delete them first.");

		deleteTree(root);
		return;
	}

	string_pair pair = getParentPath(path);

	std::string& parent = pair.first;
	std::string& child = pair.second;

	DLList<TNode*> resultNodes;
	getLastNode(parent.c_str(), root, resultNodes);

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

void Tree::addAttribute(const Attribute& attribute, std::string& path)
{
	manipulateAttribute(attribute, path, &Tree::addAttributeInIterator);
}

void Tree::changeAttribute(std::string& oldAttribute, const Attribute& newAttribute, std::string& path)
{
	manipulateAttribute(newAttribute, path, &Tree::changeAttributeInIterator, oldAttribute.c_str());
}

void Tree::removeAttribute(const Attribute& attribute, std::string& path)
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
		}
		return;
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

void Tree::manipulateAttribute(const Attribute& attribute, std::string& path, attributeFunction workAttribute, const char* oldAttribute)
{
	if (!root)
		throw EmptyTreeOperation("tree is empty");

	DLList<TNode*> resultNodes;
	getLastNode(path.c_str(), root, resultNodes);

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

	(*iter)->data.changeAttribute(static_cast<std::string>(oldAttribute), newAttribute);
}

void Tree::removeAttributeInIterator(const Attribute& attribute, const ListIterator& iter, const char* oldAttribute)
{
	(*iter)->data.removeAttribute(attribute);
}

void Tree::send(std::ostream& output, bool pretty) const
{
	if (root)
	{
		int tabulations = 0;
		root->sendMe(root, output, tabulations, pretty);
	}
}