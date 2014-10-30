#ifndef COMPUTE_EXPRESSION_H
#define COMPUTE_EXPRESSION_H

#include <fstream>

class Operator;

class ComputeExpression
{
public:
	double compute(const char*, const char*);

private:
	Operator** readOperator(std::ifstream &, int &);

private:
	bool isOperator(char c);
	double calculate(double, double, const Operator &);
	double fetchNumber(const char *&);
};

#endif // COMPUTE_EXPRESSION_H
