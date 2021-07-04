/*****************************************************************************
* Module: Stack Module
* File Name: stack.h
* Description: Header file for Stack Module
* Author: Mohamed Hisham Wagdy
* Date: 02/07/2021
******************************************************************************/

#ifndef STACK_H_
#define STACK_H_

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include "std_types.h"

/******************************************************************************
 *                              Standard Data Types                           *
 ******************************************************************************/

/* stack node struct */
typedef struct {
	struct node * next;
	uint8_t data;
} node;

/******************************************************************************
 *                                 Stack Macros                               *
 ******************************************************************************/

#define MAX_STACK_SIZE (uint8_t)100
#define EMPTY_STACK (uint8_t)0

/******************************************************************************
 *                              External Variables                            *
 ******************************************************************************/

/* global variable used as a stack pointer. */
extern node * head;

/* global value store current value of stack to be used in unit testing. */
extern uint8_t stack_size;

/* global value storing last value printed to the console. */
extern char * console_output;

/******************************************************************************
 *                              Functions Prototypes                          *
 ******************************************************************************/

/* Function to push data to stack. */
void push(uint8_t u8_data);

/* Function to pop data on top of stack */
uint8_t pull();

/* Function to print the content of the stack. */
void printStack();

#endif /* STACK_H_ */