/*****************************************************************************
* Module: Balanced Parentheses Logic Module
* File Name: main.c
* Description: Main Source file Balanced Parentheses
* Author: Mohamed Hisham Wagdy
* Date: 2/7/2021
******************************************************************************/
#include "balanced_parentheses.h"

void main()
{
	while (1)
	{
		/* variable to store the expression entered by user */
		char expression[100];
		/* ask user to enter expression*/
		printf("Please enter an expression (maximum 100 characters long)\n");
		/* save expression entered by user in the array */
		fgets(expression, 100, stdin);
		/* print the result of the balancedParentheses API to the user */
		printf("%s \n", balancedParentheses(expression));
	}
}