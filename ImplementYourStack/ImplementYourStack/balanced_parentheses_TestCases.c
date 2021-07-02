/*****************************************************************************
* Module: Balanced Parentheses Module Test
* File Name: balanced_parentheses_TestCases.c
* Description: Source file for Balanced Parentheses Module Test Cases
* Author: Mohamed Hisham Wagdy
* Date: 2/7/2021
******************************************************************************/
#include <assert.h>
#include "balanced_parentheses.h"

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: check the pull API prints the correct message on empty stack and the
*			   stack size is still 0.
************************************************************************************/
void TestCase1(void)
{
	/* Balanced Cases */
	assert(strcmp(balancedParentheses("(2*3+(5/2+(4*3)))"), BALANCED_MESSAGE) == 0);
	assert(strcmp(balancedParentheses("3"), BALANCED_MESSAGE) == 0);
	assert(strcmp(balancedParentheses("({2+3}*(4+5))"), BALANCED_MESSAGE) == 0);
	assert(strcmp(balancedParentheses("{}"), BALANCED_MESSAGE) == 0);
	assert(strcmp(balancedParentheses("()"), BALANCED_MESSAGE) == 0);
	assert(strcmp(balancedParentheses("({})"), BALANCED_MESSAGE) == 0);
	assert(strcmp(balancedParentheses("((){})"), BALANCED_MESSAGE) == 0);

	/* Not Balanced Cases */
	assert(strcmp(balancedParentheses("{({2+10}}*11}"), NOT_BALANCED_MESSAGE) == 0);
	assert(strcmp(balancedParentheses("({3)}"), NOT_BALANCED_MESSAGE) == 0);
	assert(strcmp(balancedParentheses("(}"), NOT_BALANCED_MESSAGE) == 0);
	assert(strcmp(balancedParentheses("({}"), NOT_BALANCED_MESSAGE) == 0);
	assert(strcmp(balancedParentheses("}{)("), NOT_BALANCED_MESSAGE) == 0);

}


void main(void)
{
	TestCase1();

	/* if no assertion error happened, print all tests passed message. */
	printf("All test cases passed successfully! :))\n");
}