/*****************************************************************************
* Module: Search Module
* File Name: search.h
* Description: Header file for Search Module
* Author: Mohamed Hisham Wagdy
* Date: 03/07/2021
******************************************************************************/

#ifndef SEARCH_H_
#define SEARCH_H_

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include "std_types.h"
#include "sort.h"

/******************************************************************************
 *                                 Search Macros                               *
 ******************************************************************************/

#define NOT_FOUND (uint8_t)-1

 /******************************************************************************
  *                              Functions Prototypes                          *
  ******************************************************************************/

/* Function to search an arry for an element. */
uint8_t binarySearch(uint32_t * arr, uint8_t size, uint32_t number);

#endif /* SEARCH_H_ */