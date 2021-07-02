#include "balanced_parentheses.h"

void main()
{
	while (1)
	{
		char expression[100];
		printf("Please enter an expression (maximum 100 characters long)\n");
		fgets(expression, 100, stdin);
		printf("%s \n", balancedParentheses(expression));
	}
}