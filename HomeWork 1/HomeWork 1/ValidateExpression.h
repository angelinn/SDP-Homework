#ifndef VALIDATE_EXPRESSION_H
#define VALIDATE_EXPRESSION_H

class ValidateExpression
{
public:
	static bool isValid(const char *);

private:
	static bool areBracketsValid(const char *);
	static bool isThereSamePriorAndAssoc(const char *);
};


#endif // VALIDATE_EXPRESSION_H