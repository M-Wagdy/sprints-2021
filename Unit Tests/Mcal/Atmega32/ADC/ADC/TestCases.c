/*
 * TestCases.c
 *
 * Created: 7/22/2021 9:35:06 AM
 *  Author: Mohamed Wagdy
 */

 /*- INCLUDES
 ----------------------------------------------*/
#include <assert.h>
#include <stdio.h>
#include "Mcal/Atmega32/ADC/ADC.h"

 /*- LOCAL MACROS
 ------------------------------------------*/
#define NUMBER_OF_TESTCASES		(uint8_t)(13)
#define INVALID_CHANNEL				(uint8_t)(20)

 /*- LOCAL FUNCTIONS PROTOTYPES
 ----------------------------*/
void CallBackFunc(void);
static void TestBeforeInit(void);
static void TestInit(void);
static void TestRead(void);
static void TestEnableInterrupt(void);
static void TestDisableInterrupt(void);
static void TestCallBack(void);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t* ptr_null;
static uint8_t u8_ID;
static uint8_t u8_PassedCounter = 0;
static ADC_ERROR_state_t ADC_ErrorState;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern const uint8_t ADC_REFERENCE_SELECTION;
extern const uint8_t ADC_CONTROL_MASK;
extern Ptr_VoidFuncVoid_t g_Callback;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

/**
 * @brief: Dummy function to set as callback function.
 */
void CallBackFunc(void)
{

}

/**
 * @brief: This function tests calling functions before initialization.
 */
void TestBeforeInit(void)
{
	uint16_t u16_data;
	
	u8_ID = 1;
	ADC_ErrorState = ADC_Read(ADC_CH_0, &u16_data);
	if (
		(ADC_ErrorState == E_ADC_NOT_INIT)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	u8_ID = 2;
	ADC_ErrorState = ADC_EnableInterrupt();
	if (
		(ADC_ErrorState == E_ADC_NOT_INIT)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	u8_ID = 3;
	ADC_ErrorState = ADC_DisableInterrupt();
	if (
		(ADC_ErrorState == E_ADC_NOT_INIT)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	u8_ID = 4;
	ADC_ErrorState = ADC_SetCallback(CallBackFunc);
	if (
		(ADC_ErrorState == E_ADC_NOT_INIT)
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
	/* initialize */
	u8_ID = 5;
	ADC_ErrorState = ADC_Init();
	if (
		(ADC_ErrorState == E_ADC_SUCCESS) && (ADC_MUX_R == ADC_REFERENCE_SELECTION) &&
		(ADC_CONTROL_AND_STATUS_R == ADC_CONTROL_MASK)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* initialize before */
	u8_ID = 6;
	ADC_ErrorState = ADC_Init();
	if (
		(ADC_ErrorState == E_ADC_INIT_BEFORE)
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
* @brief: This function tests reading from ADC.
*/
static void TestRead(void)
{
	uint16_t u16_data;

	/* Null Pointer */
	u8_ID = 7;
	ADC_ErrorState = ADC_Read(ADC_CH_0, ptr_null);
	if (
		(ADC_ErrorState == E_ADC_NULL_PTR)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Invalid Channel */
	u8_ID = 8;
	ADC_ErrorState = ADC_Read(INVALID_CHANNEL, &u16_data);
	if (
		(ADC_ErrorState == E_ADC_INVALID_CH)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Pre-set ADC readings data. */
	ADC_DATA_LOW_R = 0xFF;
	ADC_DATA_HIGH_R = 0x03;
	
	/* Read */
	u8_ID = 9;
	ADC_ErrorState = ADC_Read(ADC_CH_0, &u16_data);
	if (
		(ADC_ErrorState == E_ADC_SUCCESS) && (u16_data == 0x3FF)
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
* @brief: This function tests enabling an interrupt.
*/
void TestEnableInterrupt(void)
{
	/* Clear Interrupt Bit */
	ADC_CONTROL_AND_STATUS_R &= ~(ADC_INTERRUPT_EN);

	u8_ID = 10;
	ADC_ErrorState = ADC_EnableInterrupt();
	if (
		(ADC_ErrorState == E_ADC_SUCCESS) && (ADC_CONTROL_AND_STATUS_R & ADC_INTERRUPT_EN)
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
* @brief: This function tests disabling an interrupt.
*/
void TestDisableInterrupt(void)
{
	/* Set Interrupt Bit */
	ADC_CONTROL_AND_STATUS_R |= (ADC_INTERRUPT_EN);

	u8_ID = 11;
	ADC_ErrorState = ADC_DisableInterrupt();
	if (
		(ADC_ErrorState == E_ADC_SUCCESS) && !(ADC_CONTROL_AND_STATUS_R & ADC_INTERRUPT_EN)
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
* @brief: This function tests setting callback function.
*/
static void TestCallBack(void)
{
	/* Null Pointer */
	u8_ID = 12;
	ADC_ErrorState = ADC_SetCallback(ptr_null);
	if (
		(ADC_ErrorState == E_ADC_NULL_PTR)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Set Callback */
	u8_ID = 13;
	ADC_ErrorState = ADC_SetCallback(CallBackFunc);
	if (
		(ADC_ErrorState == E_ADC_SUCCESS) && (g_Callback == CallBackFunc)
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

	TestRead();

	TestEnableInterrupt();

	TestDisableInterrupt();

	TestCallBack();

	printf("%u/%u TestCases passed.\n", u8_PassedCounter, NUMBER_OF_TESTCASES);

	printf("Press Enter key to close this window . . . \n");

	getchar();
}