/*****************************************************************************
* Module: Sort Module
* File Name: sort.h
* Description: Header file for Sort Module
* Author: Mohamed Hisham Wagdy
* Date: 03/07/2021
******************************************************************************/

#ifndef SORT_H_
#define SORT_H_

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include "std_types.h"

/******************************************************************************
 *                                 Sort Macros                               *
 ******************************************************************************/

#define SORTED (uint8_t)1
#define NOT_SORTED (uint8_t)0

/******************************************************************************
 *                              Functions Prototypes                          *
 ******************************************************************************/

/* Function to sort an arry. */
void sort(uint32_t * arr, uint8_t size);

/* Function to check if an array is sorted */
uint8_t is_sorted(uint32_t * arr, uint8_t size);

#endif /* SORT_H_ */