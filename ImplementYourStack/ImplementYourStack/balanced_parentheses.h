/*****************************************************************************
* Module: Balanced Parentheses Module
* File Name: balanced_parentheses.h
* Description: Header file for Balanced Parentheses Module
* Author: Mohamed Hisham Wagdy
* Date: 02/07/2021
******************************************************************************/

#ifndef BALANCED_PARENTHESES_H_
#define BALANCED_PARENTHESES_H_

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include "std_types.h"
#include "stack.h"

/******************************************************************************
 *                       Balanced Parentheses Macros                          *
 ******************************************************************************/

#define BALANCED_MESSAGE "Balanced"
#define NOT_BALANCED_MESSAGE "Not Balanced"
#define BALANCED_STATE (uint8_t)1
#define NOT_BALANCED_STATE (uint8_t)0

/******************************************************************************
 *                              Functions Prototypes                          *
 ******************************************************************************/

 /* Function to check if expression has balanced parentheses or not. */
uint8_t * balancedParentheses(uint8_t * expression);

#endif /* BALANCED_PARENTHESES_H_ */