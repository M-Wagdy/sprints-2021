/*****************************************************************************
* Module: Balanced Parentheses Module
* File Name: balanced_parentheses.c
* Description: Source file for Balanced Parentheses Module
* Author: Mohamed Hisham Wagdy
* Date: 02/07/2021
******************************************************************************/

#include "balanced_parentheses.h"

static uint8_t checkBalance(node * stack_pointer)
{
	while (head != 0)
	{
		uint8_t current_stack_size = stack_size, par_1 = 0, par_2 = 0;
		uint8_t * temp_array = (uint8_t *)malloc(current_stack_size * sizeof(uint8_t));
		
		for (int i = 0; i < current_stack_size; i++)
		{
			temp_array[i] = pull();
		}
		for (int i = 0; i < current_stack_size - 1; i++)
		{
			if (
				(temp_array[i] == (uint8_t)')' && temp_array[i + 1] == (uint8_t)'(') ||
				(temp_array[i] == (uint8_t)'}' && temp_array[i + 1] == (uint8_t)'{')
				)
			{
				par_1 = i; 
				par_2 = i + 1;
				break;
			}
		}
		if ((par_2 - par_1) != 1)
		{
			return NOT_BALANCED_MESSAGE;
		}
		else
		{
			for (int i = current_stack_size - 1; i >= 0; i--)
			{
				if (i != par_1 && i != par_2)
				{
					push(temp_array[i]);
				}
			}
		}
		free(temp_array);
	}
	return BALANCED_STATE;
}

uint8_t * balancedParentheses(uint8_t * expression)
{
	uint8_t counter = 0;

	while (expression[counter] != '\0')
	{
		if (
				expression[counter] == '{' || expression[counter] == '}' ||
				expression[counter] == '(' || expression[counter] == ')'
			)
		{
			push(expression[counter]);
		}
		counter++;
	}

	if (BALANCED_STATE == checkBalance(head))
	{
		return BALANCED_MESSAGE;
	}
	else
	{
		return NOT_BALANCED_MESSAGE;
	}
}