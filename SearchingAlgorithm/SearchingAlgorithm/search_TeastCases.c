/*****************************************************************************
* Module: Search Module Test
* File Name: search_TestCases.c
* Description: Source file for Search Module Test Cases
* Author: Mohamed Hisham Wagdy
* Date: 03/07/2021
******************************************************************************/
#include <assert.h>
#include "search.h"

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: check the search API on different scenarios.
************************************************************************************/
void SearchTestCases(void)
{
	uint32_t arr[] = { 0,1,2,3,4,5,6,7,8,9 };
	/* test sorted array for an existing element */
	assert(binarySearch(arr, 10, 5) == 5);
	/* test sorted array for a not existing element */
	assert(binarySearch(arr, 10, 30) == (uint8_t)NOT_FOUND);

	uint32_t unsorted_arr[] = { 9,8,5,1,3,2,6,0,4,7 };
	/* test unsorted array for an existing element */
	assert(binarySearch(unsorted_arr, 10, 3) == 3);
	/* test unsorted array for a not existing element */
	assert(binarySearch(unsorted_arr, 10, 90) == (uint8_t)NOT_FOUND);

}

void main(void)
{
	/* run all test cases */
	SearchTestCases();

	/* if no assertion error happened, print all tests passed message. */
	printf("All test cases passed successfully! :))\n");
}