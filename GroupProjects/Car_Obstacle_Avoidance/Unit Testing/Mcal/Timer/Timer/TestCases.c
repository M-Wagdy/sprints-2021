/*
 * TestCases.c
 *
 * Created: 7/22/2021 9:35:06 AM
 *  Author: Mohamed Wagdy
 */

 /*- INCLUDES
 ----------------------------------------------*/
#include <stdio.h>
#include "Timer.h"

 /*- LOCAL MACROS
 ------------------------------------------*/
#define NUMBER_OF_TESTCASES		(uint8_t)(19)
#define INVALID_CHANNEL				(uint8_t)(20)
#define  CLK_BITS                (uint8_t)( 0x07 )

 /*- LOCAL FUNCTIONS PROTOTYPES
 ----------------------------*/
static void TestInit(void);
static void TestStart(void);
static void TestStop(void);
static void TestGetStatus(void);
static void TestDelayUs(void);
static void TestDelayMs(void);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t* ptr_null;
static uint8_t u8_ID;
static uint8_t u8_PassedCounter = 0;
static ERROR_STATE_t Timer_ErrorState;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern const STR_TIMER_config_t gastr_Timer_Config[TIMERS_NUMBER];

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/**
* @brief: This function tests init function.
*/
void TestInit(void)
{
	/* Invalid Channel */
	u8_ID = 1;
	Timer_ErrorState = TIM_Init(INVALID_CHANNEL);
	if (
		(Timer_ErrorState == TIMER_E_INVALID_CH_NUM)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Valid Channel*/
	u8_ID = 2;
	Timer_ErrorState = TIM_Init(TIMER_0);
	if (
		(Timer_ErrorState == ERROR_OK) && (TCCR0 == gastr_Timer_Config[TIMER_0].u8_mode) &&
		(TIMSK == gastr_Timer_Config[TIMER_0].u8_interrupt_mode)
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
* @brief: This function tests Timer start API.
*/
static void TestStart(void)
{
	/* Invalid Channel */
	u8_ID = 3;
	Timer_ErrorState = TIM_Start(INVALID_CHANNEL, 20);
	if (
		(Timer_ErrorState == TIMER_E_INVALID_CH_NUM)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Valid Channel*/
	u8_ID = 4;
	Timer_ErrorState = TIM_Start(TIMER_0, 20);
	if (
		(Timer_ErrorState == ERROR_OK) && (TCNT0 == 20)
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
* @brief: This function tests Stopping a timer.
*/
void TestStop(void)
{
	/* Invalid Channel */
	u8_ID = 5;
	Timer_ErrorState = TIM_Stop(INVALID_CHANNEL);
	if (
		(Timer_ErrorState == TIMER_E_INVALID_CH_NUM)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Valid Channel*/
	u8_ID = 6;
	Timer_ErrorState = TIM_Stop(TIMER_0);
	if (
		(Timer_ErrorState == ERROR_OK) && !(TCCR0 & CLK_BITS)
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
* @brief: This function tests getting status of timer.
*/
void TestGetStatus(void)
{
	/* Null Pointer */
	u8_ID = 7;
	Timer_ErrorState = TIM_GetStatus(TIMER_0, ptr_null);
	if (
		(Timer_ErrorState == TIMER_E_NULL_PTR)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	uint8_t u8_State;

	/* Invalid Channel*/
	u8_ID = 8;
	Timer_ErrorState = TIM_GetStatus(INVALID_CHANNEL, &u8_State);
	if (
		(Timer_ErrorState == TIMER_E_INVALID_CH_NUM)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Remove Flags */
	TIFR = 0x00;

	/* Valid Channel */
	u8_ID = 9;
	Timer_ErrorState = TIM_GetStatus(TIMER_0, &u8_State);
	if (
		(Timer_ErrorState == TIMER_E_PENDING)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* OverFlow Flag */
	TIFR = TIMER_0_OVERFLOW_FLAG;

	u8_ID = 10;
	Timer_ErrorState = TIM_GetStatus(TIMER_0, &u8_State);
	if (
		(Timer_ErrorState == ERROR_OK) && (u8_State == TIMER_OVERFLOW_FLAG)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Compare Flag when mode is Normal mode */
	TIFR = TIMER_0_COMPARE_FLAG;

	u8_ID = 11;
	Timer_ErrorState = TIM_GetStatus(TIMER_0, &u8_State);
	if (
		(Timer_ErrorState == TIMER_E_PENDING)
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
* @brief: This function tests using timer to delay microseconds.
*/
void TestDelayUs(void)
{
	/* Invalid Channel */
	u8_ID = 12;
	Timer_ErrorState = TIM_DelayUs(INVALID_CHANNEL, 20);
	if (
		(Timer_ErrorState == TIMER_E_INVALID_CH_NUM)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}
	
	/* Clear Registers */
	TCNT0 = 0x00;
	/* Clear Clock Bits */
	TCCR0 &= ~(CLK_BITS);

	u8_ID = 13;
	Timer_ErrorState = TIM_DelayUs(TIMER_0, 1000);
	if (
		(Timer_ErrorState == TIMER_E_PENDING) && (TCCR0 == gastr_Timer_Config[TIMER_0].u8_prescale)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* On 8MHz and 8 Prescale Should Have 5 Timer ovelflows flags, one was in the ID 13 */
	u8_ID = 14;
	TIFR |= TIMER_0_OVERFLOW_FLAG;
	for (uint8_t u8_Counter = 0; u8_Counter < 4; u8_Counter++)
	{
		Timer_ErrorState = TIM_DelayUs(TIMER_0, 1000);
	}
	if (
		(Timer_ErrorState == ERROR_OK)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Make sure it returned to pending state again */
	u8_ID = 15;
	TIFR &= ~(TIMER_0_OVERFLOW_FLAG);
	Timer_ErrorState = TIM_DelayUs(TIMER_0, 1000);
	if (
		(Timer_ErrorState == TIMER_E_PENDING)
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
* @brief: This function tests using timer to delay milliseconds.
*/
void TestDelayMs(void)
{
	/* Invalid Channel */
	u8_ID = 16;
	Timer_ErrorState = TIM_DelayMs(INVALID_CHANNEL, 20);
	if (
		(Timer_ErrorState == TIMER_E_INVALID_CH_NUM)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Clear Registers */
	TCNT0 = 0x00;
	/* Clear Clock Bits */
	TCCR0 &= ~(CLK_BITS);

	u8_ID = 17;
	Timer_ErrorState = TIM_DelayMs(TIMER_0, 5);
	if (
		(Timer_ErrorState == TIMER_E_PENDING) && (TCCR0 == gastr_Timer_Config[TIMER_0].u8_prescale)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* On 8MHz and 8 Prescale Should Have 21 Timer ovelflows flags one in the ID 17*/
	u8_ID = 18;
	TIFR |= TIMER_0_OVERFLOW_FLAG;
	for (uint8_t u8_Counter = 0; u8_Counter < 20; u8_Counter++)
	{
		Timer_ErrorState = TIM_DelayMs(TIMER_0, 5);
	}
	if (
		(Timer_ErrorState == ERROR_OK)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Make sure it returned to pending state again */
	u8_ID = 19;
	TIFR &= ~(TIMER_0_OVERFLOW_FLAG);
	Timer_ErrorState = TIM_DelayMs(TIMER_0, 1000);
	if (
		(Timer_ErrorState == TIMER_E_PENDING)
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

	TestStart();

	TestStop();

	TestGetStatus();

	TestDelayUs();

	TestDelayMs();

	printf("%u/%u TestCases passed.\n", u8_PassedCounter, NUMBER_OF_TESTCASES);

	printf("Press Enter key to close this window . . . \n");

	getchar();
}