#ifndef OPERATOR_H
#define OPERATOR_H

class Operator
{
public:
	Operator(char, char, int, int);

public:
	char getLetter() const { return letter; }
	char getSign() const { return sign; }
	int getPriority() const { return priority; }
	int getAssociativity() const { return associativity; }

private:
	char letter;
	char sign;
	int priority;
	int associativity;
};


#endif // OPERATOR_H
