/*
 * TestCases.c
 *
 * Created: 8/12/2021 1:03:41 PM
 *  Author: Mohamed Wagdy
 */

 /*- INCLUDES
  ----------------------------------------------*/
#include <stdio.h>
#include "ROBOT_Control.h"

  /*- LOCAL MACROS
  ------------------------------------------*/
#define NUMBER_OF_TESTCASES			(uint8_t)(9)
#define INVALID_DIRECTION				(uint8_t)(20)
#define MOTOR_START_STATE           (uint8_t)(2)
#define MOTOR_FORWARD_STATE         (uint8_t)(3)
#define MOTOR_BACKWARD_STATE        (uint8_t)(4)
#define MOTOR_ROTATE_STATE          (uint8_t)(5)
#define MOTOR_DELAY_STATE           (uint8_t)(6)

  /*- LOCAL FUNCTIONS PROTOTYPES
  ----------------------------*/
static void TestInit(void);
static void TestUpdate(void);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t* ptr_null;
static uint8_t u8_ID;
static uint8_t u8_PassedCounter = 0;
static ERROR_STATE_t RC_ErrorState;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern uint8_t State;
extern double64_t d64_distance;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/**
* @brief: This function tests init function.
*/
void TestInit(void)
{
	/* Init */
	u8_ID = 1;
	RC_ErrorState = RC_Init();
	if (
		(RC_ErrorState == ERROR_OK)
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
static void TestUpdate(void)
{
	d64_distance = 53;
	/* Motor Start State */
	u8_ID = 2;
	RC_ErrorState = RC_Update();
	if (
		(RC_ErrorState == ERROR_OK) && (State == MOTOR_START_STATE)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Motor Forward State */
	u8_ID = 3;
	RC_ErrorState = RC_Update();
	if (
		(RC_ErrorState == ERROR_OK) && (State == MOTOR_FORWARD_STATE)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Return Operation State from Motor Forward State */
	u8_ID = 4;
	RC_ErrorState = RC_Update();
	if (
		(RC_ErrorState == ERROR_OK) && (State == OperationStarted)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	d64_distance = 50;
	/* Motor Rotate State */
	u8_ID = 5;
	/* Motor Start State */
	RC_ErrorState = RC_Update();
	/* Motor Rotate State */
	RC_ErrorState = RC_Update();
	if (
		(RC_ErrorState == ERROR_OK) && (State == MOTOR_ROTATE_STATE)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Motor Delay State */
	u8_ID = 6;
	RC_ErrorState = RC_Update();
	if (
		(RC_ErrorState == ERROR_OK) && (State == MOTOR_DELAY_STATE)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Return Operation State from Motor Delay State */
	u8_ID = 7;
	RC_ErrorState = RC_Update();
	if (
		(RC_ErrorState == ERROR_OK) && (State == OperationStarted)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	d64_distance = 47;
	/* Motor Backward State */
	u8_ID = 8;
	/* Motor Start State */
	RC_ErrorState = RC_Update();
	/* Motor Rotate State */
	RC_ErrorState = RC_Update();
	if (
		(RC_ErrorState == ERROR_OK) && (State == MOTOR_BACKWARD_STATE)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Return Operation State from Motor Backward State */
	u8_ID = 9;
	RC_ErrorState = RC_Update();
	if (
		(RC_ErrorState == ERROR_OK) && (State == OperationStarted)
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
	TestInit();

	TestUpdate();

	printf("%u/%u TestCases passed.\n", u8_PassedCounter, NUMBER_OF_TESTCASES);

	printf("Press Enter key to close this window . . . \n");

	getchar();
}