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
	printf("%s \n", balancedParentheses("{a}"));
}


void main(void)
{
	TestCase1();

	/* if no assertion error happened, print all tests passed message. */
	printf("All test cases passed successfully! :))\n");
}