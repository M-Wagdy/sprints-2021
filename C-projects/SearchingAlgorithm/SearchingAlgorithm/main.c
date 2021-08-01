/*****************************************************************************
* Module: Searching Algorithm Logic Module
* File Name: main.c
* Description: Main Source file Searching Algorithm
* Author: Mohamed Hisham Wagdy
* Date: 03/07/2021
******************************************************************************/
#include "search.h"

void main()
{
	while (1)
	{
		/* local variables */
		uint8_t size;
		uint8_t number;
		uint8_t index;
		uint32_t arr[255];

		/* get size of array */
		printf("Please enter the size of your array. (maximum size is 255): \n");
		scanf_s("%d", &size);

		/* check if valid array size */
		if (size > 255)
		{
			printf("you entered a number more than the maximum, making the entered size is 255! \n");
			size = 255;
		}

		/* take array elements */
		printf("enter your array elements delimited by spaces: \n");
		for (int i = 0; i < size; i++)
		{
			scanf_s("%d", &arr[i]);
		}

		/* get number to be searched */
		printf("enter the number to be searched: \n");
		scanf_s("%d", &number);

		/* search array for the number */
		index = binarySearch(arr, size, number);
		
		/* print to the user the number index */
		if (index == (uint8_t)NOT_FOUND)
		{
			printf("the entered number doesn't exist in the array. \n");
		}
		else
		{
			printf("this number is found in a sorted array in index %d \n", index);
		}
	}
}