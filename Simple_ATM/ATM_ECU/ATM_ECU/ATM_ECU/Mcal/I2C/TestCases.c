/*
 * TestCases.c
 *
 * Created: 7/16/2021 9:35:06 AM
 *  Author: Mohamed Wagdy
 */

 /*- INCLUDES
 ----------------------------------------------*/
#include <assert.h>
#include <stdio.h>
#include "I2C.h"

 /*- LOCAL MACROS
 ------------------------------------------*/

 /*- LOCAL FUNCTIONS PROTOTYPES
 ----------------------------*/
static void TestInit(void);
static void TestEnableInterrupt(void);
static void TestDisableInterrupt(void);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t* ptr_null;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

/**
* @brief: This function tests init function.
*/
void TestInit(void)
{
	I2C_ERROR_state_t error_state;

	/* initialize with invalid channel */
	error_state = I2C_Init(255);
	assert(error_state == E_I2C_INVALID_CH);

	/* initialize */
	error_state = I2C_Init(I2C_CH_0);
	assert(error_state == E_I2C_SUCCESS);
	
	/* make sure data is written correctly in registers */
	assert(I2C_CONTROL_R == I2C_CH_0_CONTROL_MASK);
}

/**
* @brief: This function tests enabling an interrupt.
*/
void TestEnableInterrupt(void)
{
	I2C_CONTROL_R &= ~(I2C_INTERRUPT_EN);
	I2C_ERROR_state_t error_state;

	/* invalid spi channel */
	error_state = I2C_EnableInterrupt(20);
	assert(error_state == E_I2C_INVALID_CH);
	assert(!(I2C_CONTROL_R & I2C_INTERRUPT_EN));

	error_state = I2C_EnableInterrupt(I2C_CH_0);
	assert(error_state == E_I2C_SUCCESS);
	assert((I2C_CONTROL_R & I2C_INTERRUPT_EN));
}

/**
* @brief: This function tests disabling an interrupt.
*/
void TestDisableInterrupt(void)
{
	I2C_CONTROL_R |= (I2C_INTERRUPT_EN);

	I2C_ERROR_state_t error_state;

	/* invalid spi channel */
	error_state = I2C_DisableInterrupt(20);
	assert(error_state == E_I2C_INVALID_CH);
	assert((I2C_CONTROL_R & I2C_INTERRUPT_EN));

	error_state = I2C_DisableInterrupt(I2C_CH_0);
	assert(error_state == E_I2C_SUCCESS);
	assert(!(I2C_CONTROL_R & I2C_INTERRUPT_EN));
}

/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function runs all test cases.
*/
void main(void)
{
	TestInit();

	TestEnableInterrupt();

	TestDisableInterrupt();

	/* prints if no assertion error was raised */
	printf("all tests passed successfully!\n");
}