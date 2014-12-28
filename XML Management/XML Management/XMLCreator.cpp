#include "XMLCreator.h"

void XMLCreator::insertTag(const char* tag, const char* in)
{
	if (!in)
		markers.insert(tag);
	else
		markers.insert(tag, in);
}

void XMLCreator::removeTag(const char* tag)
{

}