/*****************************************************************************
* Module: Search Module
* File Name: search.c
* Description: Source file for Search Module
* Author: Mohamed Hisham Wagdy
* Date: 03/07/2021
******************************************************************************/

#include "search.h"

/************************************************************************************
* Parameters (in): arr - array to be searched.
*				   size - size of array
*				   number - number to be searched
* Parameters (out): None
* Return value: index - index of the found element in the array.
* Description: search a number in a given array and returns it's index.
************************************************************************************/
uint8_t binarySearch(uint32_t * arr, uint8_t size, uint32_t number)
{
	/* initialize found index to not found */
	uint8_t index = NOT_FOUND;
	
	/* check if array is sorted or not */
	uint8_t sorted_status = is_sorted(arr, size);
	
	/* sort array if not sorted */
	if (NOT_SORTED == sorted_status)
	{
		sort(arr, size);
	}

	/* initialize variables used in binary search */
	uint8_t start = 0, end = size, mid = size / 2;
	/* binary search algorithm */
	while (start != end && start < end)
	{
		if (number == arr[mid])
		{
			index = mid;
			break;
		}
		else if (number > arr[mid])
		{
			start = mid + 1;
			mid = (start + end) / 2;
		}
		else if (number < arr[mid])
		{
			end = mid - 1;
			mid = (start + end) / 2;
		}
		else
		{
			/* Do Nothing */
		}
	}
	if (number == arr[mid])
	{
		index = mid;
	}

	/* return found index */
	return index;
}