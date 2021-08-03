/*****************************************************************************
* Module: Sort Module
* File Name: sort.c
* Description: Source file for Sort Module
* Author: Mohamed Hisham Wagdy
* Date: 03/07/2021
******************************************************************************/

#include "sort.h"

/************************************************************************************
* Parameters (in): arr - array to be sorted.
*				   size - size of array
* Parameters (out): None
* Return value: None
* Description: sorts an array using insertion sort.
************************************************************************************/
void sort(uint32_t * arr, uint8_t size)
{
	/* insertion sort algorithm */
	for (int i = 1; i < size; i++)
	{
		uint8_t temp = arr[i];
		int j;
		for (j = i - 1; j >= 0; j--)
		{
			if (arr[j] > temp)
			{
				arr[j + 1] = arr[j];
			}
			else
			{
				break;
			}
		}
		arr[j + 1] = temp;
	}
}

/************************************************************************************
* Parameters (in): arr - array to be checked if it is a sorted array.
*				   size - size of arrays
* Parameters (out): None
* Return value: sorted_status - returns SORTED or NOT_SORTED if array is sorted or not.
* Description: check if a given array is sorted.
************************************************************************************/
uint8_t is_sorted(uint32_t * arr, uint8_t size)
{
	uint8_t sorted_status = SORTED;
	
	/* check if array is not sorted */
	for (int i = 1; i < size; i++)
	{
		if (arr[i] < arr[i - 1])
		{
			sorted_status = NOT_SORTED;
			break;
		}
	}
	return sorted_status;
}