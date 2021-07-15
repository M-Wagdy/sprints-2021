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
#include "UART.h"

/*- LOCAL MACROS
------------------------------------------*/
#define MAX_STRING_SIZE       (uint16_t)(200)
#define INVALID_BAUD_RATE     (uint16_t)(4096)
#define EMPTY_BUFFER_BIT	  (uint8_t)(0x20)
#define RECEIVE_COMPLETE_BIT  (uint8_t)(0x80)

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
   UART_ERROR_state_t error_state;
   
   /* call UART_sendChar before initialization */
   error_state = UART_TransmitChar(UART_CH_0, 'a');
   assert(error_state == E_UART_NOT_INIT);
   error_state = E_UART_SUCCESS;
   
   uint8_t data[10];
   /* call UART_readChar before initialization */
   error_state = UART_ReceiveChar(UART_CH_0, &data);
   assert(error_state == E_UART_NOT_INIT);
   error_state = E_UART_SUCCESS;

   /* call UART_sendString before initialization */
   error_state = UART_TransmitString(UART_CH_0, 'a');
   assert(error_state == E_UART_NOT_INIT);
   error_state = E_UART_SUCCESS;

   /* call UART_readString before initialization */
   error_state = UART_ReceiveString(UART_CH_0, &data);
   assert(error_state == E_UART_NOT_INIT);
}

/**
* @brief: This function tests init function.
*/
void TestInit(void)
{
   UART_ERROR_state_t error_state;
   
   /* initialize with invalid baud rate */
   error_state = UART_Init();
   assert(error_state == E_UART_SUCCESS);
   /* make sure data is written correctly in registers */
   assert(UART_CONTROL_R == 0x18);
   assert(UART_CONTROL_2_R == 0x86);
   assert(UART_BAUDRATE_LOW_R == CLK_8_MHZ_9600_BAUD);
   assert(UART_BAUDRATE_HIGH_R == 0x00);
   
   /* call init function agan after initialization */
   error_state = UART_Init();
   assert(error_state == E_UART_INIT_BEFORE);
}

/**
* @brief: This function tests sending character.
*/
void TestSendChar(void)
{
   /* sets empty buffer bit in register */
   UART_STATUS_R |= EMPTY_BUFFER_BIT;
	
   UART_ERROR_state_t error_state;
   error_state = UART_TransmitChar(UART_CH_0, 'a');
   assert(error_state == E_UART_SUCCESS);
   /* make sure write data is written in the register */
   assert(UART_DATA_R== 'a');
}

/**
* @brief: This function tests receiving character.
*/
void TestReceiveChar(void)
{
   /* sets the received data in the register */
   UART_DATA_R = 'b';
   /* sets receive completer bit in the status register */
   UART_STATUS_R|= RECEIVE_COMPLETE_BIT;

   UART_ERROR_state_t error_state;
   /* test sending null pointer to the read character function */
   error_state = UART_ReceiveChar(UART_CH_0, ptr_null);
   assert(error_state == E_UART_NULL_PTR);

   uint8_t data;
   error_state = UART_ReceiveChar(UART_CH_0, &data);
   assert(error_state == E_UART_SUCCESS);
   assert(data == 'b');
}

/**
* @brief: This function tests sending a string.
*/
void TestSendString(void)
{
   /* sets empty buffer bit in register */
   UART_STATUS_R |= EMPTY_BUFFER_BIT;

   UART_ERROR_state_t error_state;
   /* test sending null pointer to the function */
   error_state = UART_TransmitString(UART_CH_0, ptr_null);
   assert(error_state == E_UART_NULL_PTR);

   error_state = UART_TransmitString(UART_CH_0, "dawdwwaz");
   assert(error_state == E_UART_SUCCESS);
   assert(UART_DATA_R == 'z');
}

/**
* @brief: This function tests receiving a string.
*/
void TestReceiveString(void)
{
   /* sets the received data in the register */
   UART_DATA_R = NEW_LINE;
   /* sets receive completer bit in the status register */
   UART_STATUS_R |= RECEIVE_COMPLETE_BIT;

   UART_ERROR_state_t error_state;
   /* test sending null pointer to the function */
   error_state = UART_ReceiveString(UART_CH_0, ptr_null);
   assert(error_state == E_UART_NULL_PTR);

   uint8_t data[10];
   error_state = UART_ReceiveString(UART_CH_0, &data);
   assert(error_state == E_UART_SUCCESS);
   assert(data[0] == NEW_LINE);
   /* make sure end of string character is inserted at the end of the string */
   assert(data[1] == END_OF_STRING);
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
   
   /* prints if no assertion error was raised */
   printf("all tests passed successfully!\n");
}
