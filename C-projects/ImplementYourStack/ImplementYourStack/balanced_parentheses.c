/*****************************************************************************
* Module: Balanced Parentheses Module
* File Name: balanced_parentheses.c
* Description: Source file for Balanced Parentheses Module
* Author: Mohamed Hisham Wagdy
* Date: 02/07/2021
******************************************************************************/

#include "balanced_parentheses.h"

/************************************************************************************
* Parameters (in): stack_pointer - location the stack pointer pointing to
* Parameters (out): None
* Return value: either 1 or 0 for "Balanced" or "Not Balanced" expression.
* Description: check if the parentheses in the stack are balanced or not.
************************************************************************************/
static uint8_t checkBalance(node * stack_pointer)
{
	/* while the stack is not empty */
	while (head != 0)
	{
		uint8_t current_stack_size = stack_size, par_1 = 0, par_2 = 0;
		uint8_t * temp_array = (uint8_t *)malloc(current_stack_size * sizeof(uint8_t));
		
		/* pop all parentheses stored in the stack to a local array. */
		for (int i = 0; i < current_stack_size; i++)
		{
			temp_array[i] = pull();
		}
		/* check if there is consecutive () or {} instances */
		for (int i = 0; i < current_stack_size - 1; i++)
		{
			if (
				(temp_array[i] == (uint8_t)')' && temp_array[i + 1] == (uint8_t)'(') ||
				(temp_array[i] == (uint8_t)'}' && temp_array[i + 1] == (uint8_t)'{')
				)
			{
				/* store the indecies of the consecutive () or {} instance */
				par_1 = i; 
				par_2 = i + 1;
				/* quit the for loop */
				break;
			}
		}
		/* if the two indecies are not exactly after each other */
		if ((par_2 - par_1) != 1)
		{
			/* then it is not balanced expression */
			return NOT_BALANCED_MESSAGE;
		}
		else
		{
			/* push all parentheses to the stack again while removing 
			   the consecutive parentheses that were found. */
			for (int i = current_stack_size - 1; i >= 0; i--)
			{
				if (i != par_1 && i != par_2)
				{
					push(temp_array[i]);
				}
			}
		}
		/* free the allocated memory */
		free(temp_array);
	}
	/* if the stack is empty then all parentheses had a closing parentheses 
	   next to it, so the expression is balanced. */
	return BALANCED_STATE;
}

/************************************************************************************
* Parameters (in): expression - expression to determine if balanced or not
* Parameters (out): None
* Return value: either "Balanced" or "Not Balanced" string.
* Description: push all parentheses in an expression to the stack and 
*			   call checkBalance to check if parentheses in the stack are 
*			   balanced or not.
************************************************************************************/
uint8_t * balancedParentheses(uint8_t * expression)
{
	uint8_t counter = 0;

	/* while expression character is not null for end of string. */
	while (expression[counter] != '\0')
	{
		/* if the character is one of these parentheses then push to the stack */
		if (
				expression[counter] == '{' || expression[counter] == '}' ||
				expression[counter] == '(' || expression[counter] == ')'
			)
		{
			push(expression[counter]);
		}
		counter++;
	}

	/* check if the parentheses are balanced or not */
	if (BALANCED_STATE == checkBalance(head))
	{
		return BALANCED_MESSAGE;
	}
	else
	{
		return NOT_BALANCED_MESSAGE;
	}
}