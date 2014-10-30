#ifndef COMPUTE_EXPRESSION_H
#define COMPUTE_EXPRESSION_H

#include <fstream>
#include "Stack.h"

class Operator;

class ComputeExpression
{
public:
	ComputeExpression();
	~ComputeExpression();

public:
	double compute(const char*, const char*);

private:
	ComputeExpression(const ComputeExpression &);
	ComputeExpression& operator=(const ComputeExpression &);

private:
	void readOperator(std::ifstream &);

private:
	Stack<double> numbers;
	Stack<Operator*> operators;
	Operator** operatorsDescription;
	int operatorsArraySize;

private:
	void checkIfBrackets(const char *, Operator *);
	int checkIfOperator(const char *, Operator *);
	bool isOperator(char c);
	double calculate(double, double, const Operator *);
	double fetchNumber(const char *&);
};

#endif // COMPUTE_EXPRESSION_H
