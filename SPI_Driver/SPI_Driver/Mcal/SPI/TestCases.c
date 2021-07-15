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
#include "SPI.h"

 /*- LOCAL MACROS
 ------------------------------------------*/

 /*- LOCAL FUNCTIONS PROTOTYPES
 ----------------------------*/
static void TestInit(void);
static void TestSendChar(void);
static void TestReceiveChar(void);
static void TestReceiveString(void);
static void TestReceiveString(void);
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
	SPI_ERROR_state_t error_state;

	/* initialize with invalid channel */
	error_state = SPI_Init(255);
	assert(error_state == E_SPI_INVALID_CH);

	/* initialize */
	error_state = SPI_Init(SPI_CH_0);
	assert(error_state == E_SPI_SUCCESS);
	/* make sure data is written correctly in registers */
	assert(SPI_CONTROL_R == SPI_CH_0_CONTROL_MASK);
	assert(PORTB_DATA == 0x10);
	assert(PORTB_DIR == 0xB0);
}

/**
* @brief: This function tests sending character.
*/
void TestSendChar(void)
{
	/* sets empty buffer bit in register */
	SPI_STATUS_R |= SPI_TRANSMIT_COMPLETE_BIT;

	SPI_ERROR_state_t error_state;
	/* invalid spi channel */
	error_state = SPI_TransmitChar(20, 'a', SPI_CH_0_SS_CH_0);
	assert(error_state == E_SPI_INVALID_CH);

	/* invalid slave line */
	error_state = SPI_TransmitChar(SPI_CH_0, 'a', 20);
	assert(error_state == E_SPI_INVALID_SS_CH);

	error_state = SPI_TransmitChar(SPI_CH_0, 'a', SPI_CH_0_SS_CH_0);
	assert(error_state == E_SPI_SUCCESS);
	/* make sure write data is written in the register */
	assert(SPI_DATA_R == 'a');
	assert(PORTB_DATA == 0x10);
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

	SPI_ERROR_state_t error_state;
	/* test sending null pointer to the read character function */
	error_state = SPI_ReceiveChar(SPI_CH_0, ptr_null, SPI_CH_0_SS_CH_0);
	assert(error_state == E_SPI_NULL_PTR);
	assert(PORTB_DATA == 0x10);

	uint8_t data;

	/* invalid spi channel */
	error_state = SPI_ReceiveChar(20, &data, SPI_CH_0_SS_CH_0);
	assert(error_state == E_SPI_INVALID_CH);

	/* invalid slave line */
	error_state = SPI_ReceiveChar(SPI_CH_0, &data, 20);
	assert(error_state == E_SPI_INVALID_SS_CH);


	error_state = SPI_ReceiveChar(SPI_CH_0, &data, SPI_CH_0_SS_CH_0);
	assert(error_state == E_SPI_SUCCESS);
	assert(data == 'b');
	assert(PORTB_DATA == 0x10);

}

/**
* @brief: This function tests sending a string.
*/
void TestSendString(void)
{
	/* sets empty buffer bit in register */
	SPI_STATUS_R |= SPI_TRANSMIT_COMPLETE_BIT;

	SPI_ERROR_state_t error_state;
	/* test sending null pointer to the function */
	error_state = SPI_TransmitString(SPI_CH_0, ptr_null, SPI_CH_0_SS_CH_0);
	assert(error_state == E_SPI_NULL_PTR);
	assert(PORTB_DATA == 0x10);

	/* invalid spi channel */
	error_state = SPI_TransmitString(20, "dawdwwaz", SPI_CH_0_SS_CH_0);
	assert(error_state == E_SPI_INVALID_CH);

	/* invalid slave line */
	error_state = SPI_TransmitString(SPI_CH_0, "dawdwwaz", 20);
	assert(error_state == E_SPI_INVALID_SS_CH);

	error_state = SPI_TransmitString(SPI_CH_0, "dawdwwaz", SPI_CH_0_SS_CH_0);
	assert(error_state == E_SPI_SUCCESS);
	assert(SPI_DATA_R == 'z');
	assert(PORTB_DATA == 0x10);

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

	SPI_ERROR_state_t error_state;
	/* test sending null pointer to the function */
	error_state = SPI_ReceiveString(SPI_CH_0, ptr_null, SPI_CH_0_SS_CH_0);
	assert(error_state == E_SPI_NULL_PTR);

	uint8_t data[10];

	/* invalid spi channel */
	error_state = SPI_ReceiveString(20, &data, SPI_CH_0_SS_CH_0);
	assert(error_state == E_SPI_INVALID_CH);

	/* invalid slave line */
	error_state = SPI_ReceiveString(SPI_CH_0, &data, 20);
	assert(error_state == E_SPI_INVALID_SS_CH);

	error_state = SPI_ReceiveString(SPI_CH_0, &data, SPI_CH_0_SS_CH_0);
	assert(error_state == E_SPI_SUCCESS);
	assert(data[0] == NEW_LINE);
	/* make sure end of string character is inserted at the end of the string */
	assert(data[1] == END_OF_STRING);
}

/**
* @brief: This function tests enabling an interrupt.
*/
void TestEnableInterrupt(void)
{
	SPI_CONTROL_R &= ~(SPI_INTERRUPT_EN);
	SPI_ERROR_state_t error_state;

	/* invalid spi channel */
	error_state = SPI_EnableInterrupt(20);
	assert(error_state == E_SPI_INVALID_CH);
	assert(!(SPI_CONTROL_R & SPI_INTERRUPT_EN));

	error_state = SPI_EnableInterrupt(SPI_CH_0);
	assert(error_state == E_SPI_SUCCESS);
	assert((SPI_CONTROL_R & SPI_INTERRUPT_EN));
}

/**
* @brief: This function tests disabling an interrupt.
*/
void TestDisableInterrupt(void)
{
	SPI_CONTROL_R |= (SPI_INTERRUPT_EN);

	SPI_ERROR_state_t error_state;

	/* invalid spi channel */
	error_state = SPI_DisableInterrupt(20);
	assert(error_state == E_SPI_INVALID_CH);
	assert((SPI_CONTROL_R & SPI_INTERRUPT_EN));

	error_state = SPI_DisableInterrupt(SPI_CH_0);
	assert(error_state == E_SPI_SUCCESS);
	assert(!(SPI_CONTROL_R & SPI_INTERRUPT_EN));
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

	/* prints if no assertion error was raised */
	printf("all tests passed successfully!\n");
}