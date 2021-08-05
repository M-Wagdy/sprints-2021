/*
 * TestCases.c
 *
 * Created: 7/13/2021 5:25:47 PM
 *  Author: Mohamed Wagdy
 */

 /*- INCLUDES
 ----------------------------------------------*/
#include <assert.h>
#include <stdio.h>
#include "Mcal/Atmega32/SPI/SPI.h"

 /*- LOCAL MACROS
 ------------------------------------------*/
#define NUMBER_OF_TESTCASES		(uint8_t)(24)
#define INVALID_CHANNEL				(uint8_t)(20)

 /*- LOCAL FUNCTIONS PROTOTYPES
 ----------------------------*/
static void TestInit(void);
static void TestSendChar(void);
static void TestReceiveChar(void);
static void TestSendString(void);
static void TestReceiveString(void);
static void TestEnableInterrupt(void);
static void TestDisableInterrupt(void);
static void TestSetCallback(void);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t* ptr_null;
static uint8_t u8_ID;
static uint8_t u8_PassedCounter = 0;
static SPI_ERROR_state_t SPI_ErrorState;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern const uint8_t SPI_CH_0_CONTROL_MASK;
extern Ptr_VoidFuncVoid_t g_Callback[SPI_NUMBERS];

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

/**
* @brief: This function tests init function.
*/
void TestInit(void)
{
	/* Invalid Channel */
	u8_ID = 1;
	SPI_ErrorState = SPI_Init(INVALID_CHANNEL);
	if (
		(SPI_ErrorState == E_SPI_INVALID_CH)
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
	u8_ID = 2;
	SPI_ErrorState = SPI_Init(SPI_CH_0);
	if (
		(SPI_ErrorState == E_SPI_SUCCESS) && (SPI_CONTROL_R == SPI_CH_0_CONTROL_MASK) &&
		(PORTB_DATA == 0x10) && (PORTB_DIR == 0xB0)
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
* @brief: This function tests sending character.
*/
void TestSendChar(void)
{
	/* sets empty buffer bit in register */
	SPI_STATUS_R |= SPI_TRANSMIT_COMPLETE_BIT;

	/* invalid spi channel */
	u8_ID = 3;
	SPI_ErrorState = SPI_TransmitChar(INVALID_CHANNEL, 'a', SPI_CH_0_SS_CH_0);
	if (
		(SPI_ErrorState == E_SPI_INVALID_CH)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* invalid slave line */
	u8_ID = 4;
	SPI_ErrorState = SPI_TransmitChar(SPI_CH_0, 'a', INVALID_CHANNEL);
	if (
		(SPI_ErrorState == E_SPI_INVALID_SS_CH)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Valid Channels */
	u8_ID = 5;
	SPI_ErrorState = SPI_TransmitChar(SPI_CH_0, 'a', SPI_CH_0_SS_CH_0);
	if (
		(SPI_ErrorState == E_SPI_SUCCESS) && (SPI_DATA_R == 'a') &&
		(PORTB_DATA == 0x10)
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
* @brief: This function tests receiving character.
*/
void TestReceiveChar(void)
{
	/* sets the received data in the register */
	SPI_DATA_R = 'b';
	/* sets receive completer bit in the status register */
	SPI_STATUS_R |= SPI_TRANSMIT_COMPLETE_BIT;

	/* Null Pointer */
	u8_ID = 6;
	SPI_ErrorState = SPI_ReceiveChar(SPI_CH_0, ptr_null, SPI_CH_0_SS_CH_0);
	if (
		(SPI_ErrorState == E_SPI_NULL_PTR) && (PORTB_DATA == 0x10) 
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	uint8_t data;

	/* invalid spi channel */
	u8_ID = 7;
	SPI_ErrorState = SPI_ReceiveChar(INVALID_CHANNEL, &data, SPI_CH_0_SS_CH_0);
	if (
		(SPI_ErrorState == E_SPI_INVALID_CH) 
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* invalid slave line */
	u8_ID = 8;
	SPI_ErrorState = SPI_ReceiveChar(SPI_CH_0, &data, INVALID_CHANNEL);
	if (
		(SPI_ErrorState == E_SPI_INVALID_SS_CH)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Valid channels */
	u8_ID = 9;
	SPI_ErrorState = SPI_ReceiveChar(SPI_CH_0, &data, SPI_CH_0_SS_CH_0);
	if (
		(SPI_ErrorState == E_SPI_SUCCESS) && (data == 'b') &&
		(PORTB_DATA == 0x10)
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
* @brief: This function tests sending a string.
*/
void TestSendString(void)
{
	/* sets empty buffer bit in register */
	SPI_STATUS_R |= SPI_TRANSMIT_COMPLETE_BIT;

	/* Null Pointer */
	u8_ID = 10;
	SPI_ErrorState = SPI_TransmitString(SPI_CH_0, ptr_null, SPI_CH_0_SS_CH_0);
	if (
		(SPI_ErrorState == E_SPI_NULL_PTR) && (PORTB_DATA == 0x10)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* invalid spi channel */
	u8_ID = 11;
	SPI_ErrorState = SPI_TransmitString(INVALID_CHANNEL, "dawdwwaz", SPI_CH_0_SS_CH_0);
	if (
		(SPI_ErrorState == E_SPI_INVALID_CH)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* invalid slave line */
	u8_ID = 12;
	SPI_ErrorState = SPI_TransmitString(SPI_CH_0, "dawdwwaz", INVALID_CHANNEL);
	if (
		(SPI_ErrorState == E_SPI_INVALID_SS_CH)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Valid Channels */
	u8_ID = 13;
	SPI_ErrorState = SPI_TransmitString(SPI_CH_0, "dawdwwaz", SPI_CH_0_SS_CH_0);
	if (
		(SPI_ErrorState == E_SPI_SUCCESS) && (SPI_DATA_R == 'z') &&
		(PORTB_DATA == 0x10)
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
* @brief: This function tests receiving a string.
*/
void TestReceiveString(void)
{
	/* sets the received data in the register */
	SPI_DATA_R = NEW_LINE;
	/* sets receive completer bit in the status register */
	SPI_STATUS_R |= SPI_TRANSMIT_COMPLETE_BIT;

	/* Null Pointer */
	u8_ID = 14;
	SPI_ErrorState = SPI_ReceiveString(SPI_CH_0, ptr_null, SPI_CH_0_SS_CH_0);
	if (
		(SPI_ErrorState == E_SPI_NULL_PTR) 
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	uint8_t data[10];

	/* invalid spi channel */
	u8_ID = 15;
	SPI_ErrorState = SPI_ReceiveString(INVALID_CHANNEL, &data, SPI_CH_0_SS_CH_0);
	if (
		(SPI_ErrorState == E_SPI_INVALID_CH)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* invalid slave line */
	u8_ID = 16;
	SPI_ErrorState = SPI_ReceiveString(SPI_CH_0, &data, INVALID_CHANNEL);
	if (
		(SPI_ErrorState == E_SPI_INVALID_SS_CH)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Valid Channels */
	u8_ID = 17;
	SPI_ErrorState = SPI_ReceiveString(SPI_CH_0, &data, SPI_CH_0_SS_CH_0);
	if (
		(SPI_ErrorState == E_SPI_SUCCESS) && (data[0] == NEW_LINE) && (data[1] == END_OF_STRING)
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
	/* Unset interrupt in control register */
	SPI_CONTROL_R &= ~(SPI_INTERRUPT_EN);

	/* invalid spi channel */
	u8_ID = 18;
	SPI_ErrorState = SPI_EnableInterrupt(INVALID_CHANNEL);
	if (
		(SPI_ErrorState == E_SPI_INVALID_CH) && !(SPI_CONTROL_R & SPI_INTERRUPT_EN)
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
	u8_ID = 19;
	SPI_ErrorState = SPI_EnableInterrupt(SPI_CH_0);
	if (
		(SPI_ErrorState == E_SPI_SUCCESS) && (SPI_CONTROL_R & SPI_INTERRUPT_EN)
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
	/* Set interrupt in control register */
	SPI_CONTROL_R |= (SPI_INTERRUPT_EN);

	/* invalid spi channel */
	u8_ID = 20;
	SPI_ErrorState = SPI_DisableInterrupt(INVALID_CHANNEL);
	if (
		(SPI_ErrorState == E_SPI_INVALID_CH) && (SPI_CONTROL_R & SPI_INTERRUPT_EN)
		)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	/* Valid channels */
	u8_ID = 21;
	SPI_ErrorState = SPI_DisableInterrupt(SPI_CH_0);
	if (
		(SPI_ErrorState == E_SPI_SUCCESS) && !(SPI_CONTROL_R & SPI_INTERRUPT_EN)
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
* @brief: This function tests setting a callback function.
*/
void TestSetCallback(void)
{
	/* Null Pointer */
	u8_ID = 22;
	SPI_ErrorState = SPI_SetCallback(SPI_CH_0, ptr_null);
	if (
		(SPI_ErrorState == E_SPI_NULL_PTR) && (g_Callback[SPI_CH_0] != TestInit)
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
	u8_ID = 23;
	SPI_ErrorState = SPI_SetCallback(INVALID_CHANNEL, TestInit);
	if (
		(SPI_ErrorState == E_SPI_INVALID_CH) && (g_Callback[SPI_CH_0] != TestInit)
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
	u8_ID = 24;
	SPI_ErrorState = SPI_SetCallback(SPI_CH_0, TestInit);
	if (
		(SPI_ErrorState == E_SPI_SUCCESS) && (g_Callback[SPI_CH_0] == TestInit)
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

	TestSendChar();

	TestReceiveChar();

	TestSendString();

	TestReceiveString();

	TestEnableInterrupt();

	TestDisableInterrupt();

	TestSetCallback();

	printf("%u/%u TestCases passed.\n", u8_PassedCounter, NUMBER_OF_TESTCASES);

	printf("Press Enter key to close this window . . . \n");

	getchar();
}