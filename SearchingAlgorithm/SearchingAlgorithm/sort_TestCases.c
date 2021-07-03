/*****************************************************************************
* Module: Sort Module Test
* File Name: sort_TestCases.c
* Description: Source file for Sort Module Test Cases
* Author: Mohamed Hisham Wagdy
* Date: 03/07/2021
******************************************************************************/
#include <assert.h>
#include "sort.h"

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: check the sort API on different arrays.
************************************************************************************/
void SortTestCases(void)
{
	/* empty array */
	uint32_t empty_array[1] = { 1 };
	sort(empty_array, 0);
	/* make sure value wasn't modified by sort */
	assert(empty_array[0] == 1);

	/* array of only one number */
	uint32_t size_one_array[1] = { 100 };
	sort(size_one_array, 1);
	assert(size_one_array[0] == 100);

	/* reverse array */
	uint32_t reverse_arr[] = { 9,8,7,6,5,4,3,2,1,0 };
	sort(reverse_arr, 10);
	for (int i = 0; i < 10; i++)
	{
		assert(reverse_arr[i] == i);
	}

	/* random array */
	uint32_t random_arr[] = { 1,2,5,6,4,3,7,9,8,0 };
	sort(random_arr, 10);
	for (int i = 0; i < 10; i++)
	{
		assert(random_arr[i] == i);
	}
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: check the is_sorted API cases.
************************************************************************************/
void IsSortedTestCases(void)
{
	/* variable to store the return value of is_sorted API */
	uint8_t sort_status;

	/* unsorted array */
	uint32_t not_sorted_arr[] = { 1,2,5,6,4,3,7,9,8,0 };
	sort_status = is_sorted(not_sorted_arr, 10);
	assert(sort_status == NOT_SORTED);
	
	/* sorted array */
	uint32_t sorted_arr[] = { 0,1,2,3,4,5 };
	sort_status = is_sorted(sorted_arr, 6);
	assert(sort_status == SORTED);
}


void main(void)
{
	/* run all test cases */
	SortTestCases();
	IsSortedTestCases();
	
	/* if no assertion error happened, print all tests passed message. */
	printf("All test cases passed successfully! :))\n");
}