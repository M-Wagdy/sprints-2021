/*****************************************************************************
* Module: Stack Module Test
* File Name: stack_TestCases.c
* Description: Source file for Stack Module Test Cases
* Author: Mohamed Hisham Wagdy
* Date: 2/7/2021
******************************************************************************/
#include <assert.h>
#include "stack.h"

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: check the pull API prints the correct message on empty stack and the
*			   stack size is still 0.
************************************************************************************/
void PullEmptyStack(void)
{
	pull();
	assert(strcmp(console_output, "Stack is empty, nothing to pop!") == 0);
	assert(stack_size == 0);
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: check the printStack API prints the correct message on empty stack and the
*			   stack size is still 0.
************************************************************************************/
void PrintEmptyStack(void)
{
	printStack();
	assert(strcmp(console_output, "Stack is empty, nothing to print!") == 0);
	assert(stack_size == 0);
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: check the push API stores the data in stack correctly and the
*			   stack size is increased to 1.
************************************************************************************/
void PushToStack(void)
{
	push(5);
	assert(head->data == 5);
	assert(stack_size == 1);
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: check the pull API returns the data in stack correctly and the
*			   stack size is decreased to 0 after pop.
************************************************************************************/
void PullFromStack(void)
{
	uint8_t pop_value = pull();
	assert(pop_value == 5);
	assert(stack_size == 0);
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: check the push API prints the correct message when stack is filled 
*			   and checks the stack size is maximum when the message was printed.
************************************************************************************/
void FillStack(void)
{
	for (int i = 1; i <= MAX_STACK_SIZE + 1; i++)
	{
		push(i);
	}
	assert(strcmp(console_output, "Stack Overflow will occur, reverting push!") == 0);
	assert(stack_size == MAX_STACK_SIZE);
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: check the printStack API prints all stack and doesn't change the 
*			   stack size, you should see the console to make sure the API printed
*			   from Max stack size to 1.
************************************************************************************/
void TestPrintStack(void)
{
	printStack();
	assert(stack_size == 10);
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: check the pull API pops data correctly and the stack size decreases
*			   on each pop.
************************************************************************************/
void PopAllStack(void)
{
	uint8_t pop_value;
	for (int i = MAX_STACK_SIZE; i >= 1; i--)
	{
		pop_value = pull();
		assert(pop_value == i);
		assert(stack_size == i-1);
	}
}

void main(void)
{
	/* malloc console output to be able to realloc in stack APIs */
	console_output = (char*)malloc(sizeof(char));

	/* test cases should be run in the excat order as they depend on each other. */
	PullEmptyStack();
	PrintEmptyStack();
	PushToStack();
	PullFromStack();
	FillStack();
	TestPrintStack();
	PopAllStack();

	/* free the memory allocated by console output variable. */
	free(console_output);

	/* if no assertion error happened, print all tests passed message. */
	printf("All test cases passed successfully! :))\n");
}