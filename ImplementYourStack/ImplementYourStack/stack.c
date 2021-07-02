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
* Parameters (in): u8_data - dat to push to stack.
* Parameters (out): None
* Return value: None
* Description: saves data to stack and increment stack size by 1.
************************************************************************************/
void push(uint8_t u8_data)
{
	if (stack_size >= MAX_STACK_SIZE)
	{
		console_output = (char *)realloc(console_output, strlen("Stack Overflow will occur, reverting push!") + 1);
		strcpy(console_output, "Stack Overflow will occur, reverting push!");
		printf("%s \n", console_output);
		return;
	}

	node * new_node = (node *)malloc(sizeof(node));
	new_node->next = head;
	new_node->data = u8_data;
	
	head = new_node;
	
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
	if (stack_size == EMPTY_STACK)
	{
		console_output = (char *)realloc(console_output, strlen("Stack is empty, nothing to pop!") + 1);
		strcpy(console_output, "Stack is empty, nothing to pop!");
		printf("%s \n", console_output);
		return EMPTY_STACK;
	}

	node * temp_node = head;
	uint8_t value = temp_node->data;
	head = temp_node->next;
	free(temp_node);
	stack_size--;
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

	if (head == 0)
	{
		console_output = (char *)realloc(console_output, strlen("Stack is empty, nothing to print!") + 1);
		strcpy(console_output, "Stack is empty, nothing to print!");
		printf("%s \n", console_output);
	}

	while (temp_node != 0)
	{
		printf("%d\n", temp_node->data);
		temp_node = temp_node->next;
	}
}