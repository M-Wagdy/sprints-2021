/*
 * TestCases.c
 *
 * Created: 7/16/2021 9:35:06 AM
 *  Author: Mohamed Wagdy
 */

 /*- INCLUDES
 ----------------------------------------------*/
#include <stdio.h>
#include "Mcal/I2C/I2C.h"

 /*- LOCAL MACROS
 ------------------------------------------*/
#define NUMBER_OF_TESTCASES		(uint8_t)(28)
#define INVALID_CHANNEL				(uint8_t)(20)

 /*- LOCAL FUNCTIONS PROTOTYPES
 ----------------------------*/
void TestInit(void);
void TestSetSlaveAddr(void);
void TestStartCond(void);
void TestRepStartCond(void);
void TestWrite(void);
void TestReadAck(void);
void TestReadNoAck(void);
void TestStopCond(void);
void TestStatus(void);
void TestEnableInterrupt(void);
void TestDisableInterrupt(void);
void TestSetCallback(void);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t* ptr_null;
static uint8_t u8_ID;
static uint8_t u8_PassedCounter = 0;
static I2C_ERROR_state_t I2C_ErrorState;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern const uint8_t I2C_CH_0_CONTROL_MASK;
extern Ptr_VoidFuncVoid_t g_Callback[I2C_NUMBERS];

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

/**
* @brief: This function tests init function.
*/
void TestInit(void)
{
	/* initialize with invalid channel */
	u8_ID = 1;
	I2C_ErrorState = I2C_Init(INVALID_CHANNEL);
	if (
		(I2C_ErrorState == E_I2C_INVALID_CH)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* initialize with valid channel */
	u8_ID = 2;
	I2C_ErrorState = I2C_Init(I2C_CH_0);
	if (
		(I2C_ErrorState == E_I2C_SUCCESS) && (I2C_CONTROL_R == I2C_CH_0_CONTROL_MASK)
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
* @brief: This function tests setting slave address.
*/
void TestSetSlaveAddr(void)
{
	/* Invalid Channel */
	u8_ID = 3;
	I2C_ErrorState = I2C_SetSlaveAddress(INVALID_CHANNEL, 0x30);
	if (
		(I2C_ErrorState == E_I2C_INVALID_CH) && (I2C_SLAVE_ADDR_R != 0x30)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Valid Channel */
	u8_ID = 4;
	I2C_ErrorState = I2C_SetSlaveAddress(I2C_CH_0, 0x30);
	if (
		(I2C_ErrorState == E_I2C_SUCCESS) && (I2C_SLAVE_ADDR_R == 0x30)
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
* @brief: This function tests sending start condition.
*/
void TestStartCond(void)
{
	/* Unset Start bit */
	I2C_CONTROL_R &= ~(I2C_START_BIT);

	/* Invalid Channel */
	u8_ID = 5;
	I2C_ErrorState = I2C_Start(INVALID_CHANNEL);
	if (
		(I2C_ErrorState == E_I2C_INVALID_CH) && !(I2C_CONTROL_R & I2C_START_BIT)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Valid Channel */
	u8_ID = 6;
	I2C_ErrorState = I2C_Start(I2C_CH_0);
	if (
		(I2C_ErrorState == E_I2C_SUCCESS) && (I2C_CONTROL_R & I2C_START_BIT)
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
* @brief: This function tests sending repeated start condition.
*/
void TestRepStartCond(void)
{
	/* Unset Start bit */
	I2C_CONTROL_R &= ~(I2C_START_BIT);

	/* Invalid Channel */
	u8_ID = 7;
	I2C_ErrorState = I2C_RepeatedStart(INVALID_CHANNEL);
	if (
		(I2C_ErrorState == E_I2C_INVALID_CH) && !(I2C_CONTROL_R & I2C_START_BIT)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Valid Channel */
	u8_ID = 8;
	I2C_ErrorState = I2C_RepeatedStart(I2C_CH_0);
	if (
		(I2C_ErrorState == E_I2C_SUCCESS) && (I2C_CONTROL_R & I2C_START_BIT)
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
* @brief: This function tests writing.
*/
void TestWrite(void)
{
	/* Clear data register */
	I2C_DATA_R = 0x00;

	/* Invalid Channel */
	u8_ID = 9;
	I2C_ErrorState = I2C_Write(INVALID_CHANNEL, 'A');
	if (
		(I2C_ErrorState == E_I2C_INVALID_CH) && (I2C_DATA_R != 'A')
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Valid Channel */
	u8_ID = 10;
	I2C_ErrorState = I2C_Write(I2C_CH_0, 'A');
	if (
		(I2C_ErrorState == E_I2C_SUCCESS) && (I2C_DATA_R == 'A')
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
* @brief: This function tests reading with acknowledgement.
*/
void TestReadAck(void)
{
	/* Set data register */
	I2C_DATA_R = 'A';

	/* clear ack bit */
	I2C_CONTROL_R &= ~(I2C_ACK_EN);

	/* Null Pointer */
	u8_ID = 11;
	I2C_ErrorState = I2C_ReadAck(I2C_CH_0, ptr_null);
	if (
		(I2C_ErrorState == E_I2C_NULL_PTR) && (I2C_DATA_R == 'A')
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	uint8_t u8_data = 'B';
	/* Invalid Channel */
	u8_ID = 12;
	I2C_ErrorState = I2C_ReadAck(INVALID_CHANNEL, &u8_data);
	if (
		(I2C_ErrorState == E_I2C_INVALID_CH) && (u8_data == 'B')
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Valid Channel */
	u8_ID = 13;
	I2C_ErrorState = I2C_ReadAck(I2C_CH_0, &u8_data);
	if (
		(I2C_ErrorState == E_I2C_SUCCESS) && (u8_data == 'A') && (I2C_CONTROL_R & I2C_ACK_EN)
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
* @brief: This function tests reading with no acknowledgement.
*/
void TestReadNoAck(void)
{
	/* Set data register */
	I2C_DATA_R = 'A';

	/* set ack bit */
	I2C_CONTROL_R |= (I2C_ACK_EN);

	/* Null Pointer */
	u8_ID = 14;
	I2C_ErrorState = I2C_ReadNoAck(I2C_CH_0, ptr_null);
	if (
		(I2C_ErrorState == E_I2C_NULL_PTR) && (I2C_DATA_R == 'A')
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	uint8_t u8_data = 'B';
	/* Invalid Channel */
	u8_ID = 15;
	I2C_ErrorState = I2C_ReadNoAck(INVALID_CHANNEL, &u8_data);
	if (
		(I2C_ErrorState == E_I2C_INVALID_CH) && (u8_data == 'B')
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Valid Channel */
	u8_ID = 16;
	I2C_ErrorState = I2C_ReadNoAck(I2C_CH_0, &u8_data);
	if (
		(I2C_ErrorState == E_I2C_SUCCESS) && (u8_data == 'A') && !(I2C_CONTROL_R & I2C_ACK_EN)
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
* @brief: This function tests sending stop condition.
*/
void TestStopCond(void)
{
	/* Unset Start bit */
	I2C_CONTROL_R &= ~(I2C_STOP_BIT);

	/* Invalid Channel */
	u8_ID = 17;
	I2C_ErrorState = I2C_Stop(INVALID_CHANNEL);
	if (
		(I2C_ErrorState == E_I2C_INVALID_CH) && !(I2C_CONTROL_R & I2C_STOP_BIT)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Valid Channel */
	u8_ID = 18;
	I2C_ErrorState = I2C_Stop(I2C_CH_0);
	if (
		(I2C_ErrorState == E_I2C_SUCCESS) && !(I2C_CONTROL_R & I2C_STOP_BIT)
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
* @brief: This function tests getting I2C status.
*/
void TestStatus(void)
{
	/* Set data register */
	I2C_STATUS_R = 0xFF;

	/* Null Pointer */
	u8_ID = 19;
	I2C_ErrorState = I2C_Status(I2C_CH_0, ptr_null);
	if (
		(I2C_ErrorState == E_I2C_NULL_PTR) && (I2C_STATUS_R == 0xFF)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	uint8_t u8_data = 0x00;
	/* Invalid Channel */
	u8_ID = 20;
	I2C_ErrorState = I2C_Status(INVALID_CHANNEL, &u8_data);
	if (
		(I2C_ErrorState == E_I2C_INVALID_CH) && (u8_data == 0x00)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Valid Channel */
	u8_ID = 21;
	I2C_ErrorState = I2C_Status(I2C_CH_0, &u8_data);
	if (
		(I2C_ErrorState == E_I2C_SUCCESS) && (u8_data == 0xF8)
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
	/* Unset interrupt bit */
	I2C_CONTROL_R &= ~(I2C_INTERRUPT_EN);

	/* Invalid Channel */
	u8_ID = 22;
	I2C_ErrorState = I2C_EnableInterrupt(INVALID_CHANNEL);
	if (
		(I2C_ErrorState == E_I2C_INVALID_CH) && !(I2C_CONTROL_R & I2C_INTERRUPT_EN)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Valid Channel */
	u8_ID = 23;
	I2C_ErrorState = I2C_EnableInterrupt(I2C_CH_0);
	if (
		(I2C_ErrorState == E_I2C_SUCCESS) && (I2C_CONTROL_R & I2C_INTERRUPT_EN)
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
	/* Set interrupt bit */
	I2C_CONTROL_R |= (I2C_INTERRUPT_EN);

	/* Invalid Channel */
	u8_ID = 24;
	I2C_ErrorState = I2C_DisableInterrupt(INVALID_CHANNEL);
	if (
		(I2C_ErrorState == E_I2C_INVALID_CH) && (I2C_CONTROL_R & I2C_INTERRUPT_EN)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Valid Channel */
	u8_ID = 25;
	I2C_ErrorState = I2C_DisableInterrupt(I2C_CH_0);
	if (
		(I2C_ErrorState == E_I2C_SUCCESS) && !(I2C_CONTROL_R & I2C_INTERRUPT_EN)
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
void TestSetCallback(void)
{
	/* Null Pointer */
	u8_ID = 26;
	I2C_ErrorState = I2C_SetCallback(I2C_CH_0, ptr_null);
	if (
		(I2C_ErrorState == E_I2C_NULL_PTR) && (g_Callback[I2C_CH_0] != TestInit)
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
	u8_ID = 27;
	I2C_ErrorState = I2C_SetCallback(INVALID_CHANNEL, TestInit);
	if (
		(I2C_ErrorState == E_I2C_INVALID_CH) && (g_Callback[I2C_CH_0] != TestInit)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Valid Channel */
	u8_ID = 28;
	I2C_ErrorState = I2C_SetCallback(I2C_CH_0, TestInit);
	if (
		(I2C_ErrorState == E_I2C_SUCCESS) && (g_Callback[I2C_CH_0] == TestInit)
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

	TestSetSlaveAddr();

	TestStartCond();

	TestRepStartCond();
	
	TestWrite();
	
	TestReadAck();
	
	TestReadNoAck();
	
	TestStopCond();
	
	TestStatus();

	TestEnableInterrupt();

	TestDisableInterrupt();

	TestSetCallback();

	printf("%u/%u TestCases passed.\n", u8_PassedCounter, NUMBER_OF_TESTCASES);

	printf("Press Enter key to close this window . . . \n");
	
	getchar();
}