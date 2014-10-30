#ifndef COMPUTE_EXPRESSION_H
#define COMPUTE_EXPRESSION_H

#include <fstream>
#include "Stack.h"

class Operator;

class ComputeExpression
{
public:
	ComputeExpression();

public:
	double compute(const char*, const char*);

private:
	void readOperator(std::ifstream &);

private:
	Stack<double> numbers;
	Stack<Operator*> operators;
	Operator** operatorsDescription;
	int operatorsArraySize;

private:
	void checkIfBrackets(const char *);
	int checkIfOperator(const char *);
	bool isOperator(char c);
	double calculate(double, double, const Operator *);
	double fetchNumber(const char *&);
};

#endif // COMPUTE_EXPRESSION_H
