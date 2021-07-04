/*****************************************************************************
* Module: Stack Module
* File Name: stack.c
* Description: Source file for Stack Module
* Author: Mohamed Hisham Wagdy
* Date: 02/07/2021
******************************************************************************/

#include "stack.h"

/* string to save console data to be printed and can be used in test cases. */
char * console_output;

/* current stack size */
uint8_t stack_size = 0;

/* initialize head pointer */
node * head = 0;

/************************************************************************************
* Parameters (in): u8_data - data to be pushed to stack.
* Parameters (out): None
* Return value: None
* Description: saves data to stack and increment stack size by 1.
************************************************************************************/
void push(uint8_t u8_data)
{
	/* check if stack if full */
	if (stack_size >= MAX_STACK_SIZE)
	{
		console_output = (char *)realloc(console_output, strlen("Stack Overflow will occur, reverting push!") + 1);
		strcpy(console_output, "Stack Overflow will occur, reverting push!");
		printf("%s \n", console_output);
		return;
	}

	/* append new node on the top of stack */
	node * new_node = (node *)malloc(sizeof(node));
	new_node->next = head;
	new_node->data = u8_data;
	
	/* make stack point points to the new nodew */
	head = new_node;
	/* increment stack size*/
	stack_size++;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: value - value on top of the stack
* Description: Pops the data on top of stack and decrement stack size by 1.
************************************************************************************/
uint8_t pull()
{
	/* check if stack if empty */
	if (stack_size == EMPTY_STACK)
	{
		console_output = (char *)realloc(console_output, strlen("Stack is empty, nothing to pop!") + 1);
		strcpy(console_output, "Stack is empty, nothing to pop!");
		printf("%s \n", console_output);
		return EMPTY_STACK;
	}

	/* copy top node on stack to local variable */
	node * temp_node = head;
	/* get data in the top node */
	uint8_t value = temp_node->data;
	/* point stack pointer to the next node */
	head = temp_node->next;
	/* free the allocated memory for the top node */
	free(temp_node);
	/* decrement stack size */
	stack_size--;
	/* return value that was on the top node. */
	return value;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: prints all the stack where each value is printed in new line.
************************************************************************************/
void printStack()
{
	node * temp_node = head;

	/* check if stack is empty */
	if (head == 0)
	{
		console_output = (char *)realloc(console_output, strlen("Stack is empty, nothing to print!") + 1);
		strcpy(console_output, "Stack is empty, nothing to print!");
		printf("%s \n", console_output);
	}

	/* print all stack content */
	while (temp_node != 0)
	{
		printf("%d\n", temp_node->data);
		temp_node = temp_node->next;
	}
}