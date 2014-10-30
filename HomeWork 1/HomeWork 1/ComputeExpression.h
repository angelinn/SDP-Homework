#ifndef COMPUTE_EXPRESSION_H
#define COMPUTE_EXPRESSION_H

#include <fstream>

class Operator;

class ComputeExpression
{
public:
	int compute(const char*, const char*);

private:
	Operator** readOperator(std::ifstream &);
};

#endif // COMPUTE_EXPRESSION_H
