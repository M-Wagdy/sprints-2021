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
static void TestNotInit(void);
static void TestInit(void);
static void TestSendChar(void);
static void TestReceiveChar(void);
static void TestReceiveString(void);
static void TestReceiveString(void);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t* ptr_null;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

/**
* @brief: This function calls all driver function except for init before
* initialization to make sure it returns not init error.
*/
void TestNotInit(void)
{
	SPI_ERROR_state_t error_state;

	/* call UART_sendChar before initialization */
	error_state = SPI_SendChar('a');
	assert(error_state == E_SPI_NOT_INIT);
	error_state = E_SPI_SUCCESS;

	uint8_t data[10];
	/* call UART_readChar before initialization */
	error_state = SPI_ReadChar(&data);
	assert(error_state == E_SPI_NOT_INIT);
	error_state = E_SPI_SUCCESS;

	/* call UART_sendString before initialization */
	error_state = SPI_Send(&data);
	assert(error_state == E_SPI_NOT_INIT);
	error_state = E_SPI_SUCCESS;

	/* call UART_readString before initialization */
	error_state = SPI_Read(&data);
	assert(error_state == E_SPI_NOT_INIT);
}

/**
* @brief: This function tests init function.
*/
void TestInit(void)
{
	SPI_ERROR_state_t error_state;

	/* initialize with invalid baud rate */
	error_state = SPI_Init();
	assert(error_state == E_SPI_SUCCESS);
	/* make sure data is written correctly in registers */
	assert(SPI_CONTROL_R == SPI_CONTROL_MASK);
	assert(PORTB_DATA == 0x10);
	assert(PORTB_DIR == 0xB0);

	/* call init function agan after initialization */
	error_state = SPI_Init();
	assert(error_state == E_SPI_INIT_BEFORE);
}

/**
* @brief: This function tests sending character.
*/
void TestSendChar(void)
{
	/* sets empty buffer bit in register */
	SPI_STATUS_R |= SPI_TRANSMIT_COMPLETE_BIT;

	SPI_ERROR_state_t error_state;
	error_state = SPI_SendChar('a');
	assert(error_state == E_SPI_SUCCESS);
	/* make sure write data is written in the register */
	assert(SPI_DATA_R == 'a');
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
	error_state = SPI_ReadChar(ptr_null);
	assert(error_state == E_SPI_NULL_PTR);

	uint8_t data;
	error_state = SPI_ReadChar(&data);
	assert(error_state == E_SPI_SUCCESS);
	assert(data == 'b');
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
	error_state = SPI_Send(ptr_null);
	assert(error_state == E_SPI_NULL_PTR);

	error_state = SPI_Send("dawdwwaz");
	assert(error_state == E_SPI_SUCCESS);
	assert(SPI_DATA_R == 'z');
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
	error_state = SPI_Read(ptr_null);
	assert(error_state == E_SPI_NULL_PTR);

	uint8_t data[10];
	error_state = SPI_Read(&data);
	assert(error_state == E_SPI_SUCCESS);
	assert(data[0] == NEW_LINE);
	/* make sure end of string character is inserted at the end of the string */
	assert(data[1] == END_OF_STRING);
}

/**
* @brief: This function tests selecting a slave.
*/
void TestSelectSlave(void)
{
	SPI_ERROR_state_t error_state;
	/* test sending invalid channel number to the function */
	error_state = SPI_SelectSlave(20);
	assert(error_state == E_SPI_INVALID_SS_CH);

	error_state = SPI_SelectSlave(SS_CH_0);
	assert(error_state == E_SPI_SUCCESS);
	assert(PORTB_DATA == 0x00);
}

/**
* @brief: This function tests unselecting a slave.
*/
void TestUnselectSlave(void)
{
	SPI_ERROR_state_t error_state;
	/* test sending invalid channel number to the function */
	error_state = SPI_UnselectSlave(20);
	assert(error_state == E_SPI_INVALID_SS_CH);

	error_state = SPI_UnselectSlave(SS_CH_0);
	assert(error_state == E_SPI_SUCCESS);
	assert(PORTB_DATA == 0x10);
}

/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function runs all test cases.
*/
void main(void)
{
	TestNotInit();

	TestInit();

	TestSendChar();

	TestReceiveChar();

	TestSendString();

	TestReceiveString();

	TestSelectSlave();

	TestUnselectSlave();
	
	/* prints if no assertion error was raised */
	printf("all tests passed successfully!\n");
}