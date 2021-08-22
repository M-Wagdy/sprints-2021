/*
 * TestCases.c
 *
 * Created: 8/12/2021 1:03:41 PM
 *  Author: Mohamed Wagdy
 */

 /*- INCLUDES
  ----------------------------------------------*/
#include <stdio.h>
#include "STEERING.h"

  /*- LOCAL MACROS
  ------------------------------------------*/
#define NUMBER_OF_TESTCASES		(uint8_t)(5)
#define INVALID_DIRECTION			(uint8_t)(20)

  /*- LOCAL FUNCTIONS PROTOTYPES
  ----------------------------*/
static void TestBeforeInit(void);
static void TestInit(void);
static void TestMove(void);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t* ptr_null;
static uint8_t u8_ID;
static uint8_t u8_PassedCounter = 0;
static ERROR_STATE_t Steering_ErrorState;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/**
* @brief: This function tests Calling Functions before initialization.
*/
void TestBeforeInit(void)
{
	/* Move Before Init */
	u8_ID = 1;
	Steering_ErrorState = STEERING_Move(STEERING_FORWARD);
	if (
		(Steering_ErrorState == ERROR_NOK)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}
}

/**
* @brief: This function tests init function.
*/
void TestInit(void)
{
	/* First Init */
	u8_ID = 2;
	Steering_ErrorState = STEERING_Init();
	if (
		(Steering_ErrorState == ERROR_OK)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Re-init */
	u8_ID = 3;
	Steering_ErrorState = STEERING_Init();
	if (
		(Steering_ErrorState == ERROR_NOK)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}
}

/**
* @brief: This function tests Move API.
*/
static void TestMove(void)
{
	/* Invalid Direction */
	u8_ID = 4;
	Steering_ErrorState = STEERING_Move(INVALID_DIRECTION);
	if (
		(Steering_ErrorState == ERROR_NOK)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Valid Direction*/
	u8_ID = 5;
	Steering_ErrorState = STEERING_Move(STEERING_FORWARD);
	if (
		(Steering_ErrorState == ERROR_OK)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}
}

/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function runs all test cases.
*/
void main(void)
{
	TestBeforeInit();

	TestInit();

	TestMove();

	printf("%u/%u TestCases passed.\n", u8_PassedCounter, NUMBER_OF_TESTCASES);

	printf("Press Enter key to close this window . . . \n");

	getchar();
}