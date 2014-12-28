#ifndef INVALID_TREE_OPERATION
#define INVALID_TREE_OPERATION

#include <stdexcept>

class InvalidTreeOperation : public std::runtime_error
{
public:
	InvalidTreeOperation(const char* message) : runtime_error(message)
	{  }
};

#endif // INVALID_TREE_OPERATION_H