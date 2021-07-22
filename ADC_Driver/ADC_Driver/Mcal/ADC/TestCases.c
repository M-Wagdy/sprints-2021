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
#include "ADC.h"

 /*- LOCAL MACROS
 ------------------------------------------*/

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
	ADC_ERROR_state_t error_state;
	uint8_t data;
	

	error_state = ADC_Read(ADC_CH_0, &data);
	assert(error_state == E_ADC_NOT_INIT);

	error_state = ADC_EnableInterrupt();
	assert(error_state == E_ADC_NOT_INIT);

	error_state = ADC_DisableInterrupt();
	assert(error_state == E_ADC_NOT_INIT);

	error_state = ADC_SetCallback(CallBackFunc);
	assert(error_state == E_ADC_NOT_INIT);
}

/**
* @brief: This function tests init function.
*/
void TestInit(void)
{
	ADC_ERROR_state_t error_state;

	/* initialize */
	error_state = ADC_Init();
	assert(error_state == E_ADC_SUCCESS);
	assert(ADC_MUX_R == ADC_REFERENCE_SELECTION);
	assert(ADC_CONTROL_AND_STATUS_R == ADC_CONTROL_MASK);

	/* initialize before */
	error_state = ADC_Init();
	assert(error_state == E_ADC_INIT_BEFORE);
	
}

/**
* @brief: This function tests reading from ADC.
*/
static void TestRead(void)
{
	ADC_ERROR_state_t error_state;
	
	uint8_t data;

	/* Null Pointer */
	error_state = ADC_Read(ADC_CH_0, ptr_null);
	assert(error_state == E_ADC_NULL_PTR);

	/* Invalid Channel */
	error_state = ADC_Read(20, &data);
	assert(error_state == E_ADC_INVALID_CH);

	/* Read */

}

/**
* @brief: This function tests enabling an interrupt.
*/
void TestEnableInterrupt(void)
{
	ADC_CONTROL_AND_STATUS_R &= ~(ADC_INTERRUPT_EN);
	ADC_ERROR_state_t error_state;

	error_state = ADC_EnableInterrupt();
	assert(error_state == E_ADC_SUCCESS);
	assert((ADC_CONTROL_AND_STATUS_R & ADC_INTERRUPT_EN));
}

/**
* @brief: This function tests disabling an interrupt.
*/
void TestDisableInterrupt(void)
{
	ADC_CONTROL_AND_STATUS_R |= (ADC_INTERRUPT_EN);

	ADC_ERROR_state_t error_state;

	error_state = ADC_DisableInterrupt();
	assert(error_state == E_ADC_SUCCESS);
	assert(!(ADC_CONTROL_AND_STATUS_R & ADC_INTERRUPT_EN));
}

/**
* @brief: This function tests setting callback function.
*/
static void TestCallBack(void)
{
	ADC_ERROR_state_t error_state;

	/* Null Pointer */
	error_state = ADC_SetCallback(ptr_null);
	assert(error_state == E_ADC_NULL_PTR);

	/* Set Callback */
	error_state = ADC_SetCallback(CallBackFunc);
	assert(error_state == E_ADC_SUCCESS);
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

	/* prints if no assertion error was raised */
	printf("all tests passed successfully!\n");
}