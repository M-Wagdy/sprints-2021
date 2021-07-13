/*
 * TestCases.c
 *
 * Created: 7/13/2021 5:25:47 PM
 *  Author: Mohamed Wagdy
 */ 
#include <assert.h>
#include <stdio.h>
#include "UART.h"

#define CLK_8_MHZ_9600_BAUD   (uint16_t)(51)
#define MAX_STRING_SIZE       (uint16_t)(200)
#define INVALID_BAUD_RATE     (uint16_t)(4096)
#define EMPTY_BUFFER_BIT	  (uint8_t)(0x20)
#define RECEIVE_COMPLETE_BIT  (uint8_t)(0x80)

uint8_t* ptr_null;

void TestNotInit(void)
{
   UART_ERROR_state_t error_state;

   error_state = UART_sendChar('a');
   assert(error_state == E_UART_NOT_INIT);
   error_state = E_UART_SUCCESS;

   error_state = UART_readChar('a');
   assert(error_state == E_UART_NOT_INIT);
   error_state = E_UART_SUCCESS;

   error_state = UART_readString('a');
   assert(error_state == E_UART_NOT_INIT);
   error_state = E_UART_SUCCESS;

   error_state = UART_sendString('a');
   assert(error_state == E_UART_NOT_INIT);
}

void TestInit(void)
{
   UART_ERROR_state_t error_state;
   
   error_state = UART_init(INVALID_BAUD_RATE);
   assert(error_state == E_UART_INVALID_BAUD_RATE);
   
   error_state = UART_init(CLK_8_MHZ_9600_BAUD);
   assert(error_state == E_UART_SUCCESS);
   assert(UART_CONTROL_R == 0x18);
   assert(UART_CONTROL_2_R == 0x86);
   assert(UART_BAUDRATE_LOW_R == CLK_8_MHZ_9600_BAUD);
   assert(UART_BAUDRATE_HIGH_R == 0x00);
   
   error_state = UART_init(CLK_8_MHZ_9600_BAUD);
   assert(error_state == E_UART_INIT_BEFORE);
}

void TestSendChar(void)
{
   UART_STATUS_R |= EMPTY_BUFFER_BIT;
	
   UART_ERROR_state_t error_state;
   error_state = UART_sendChar('a');

   assert(error_state == E_UART_SUCCESS);
   assert(UART_DATA_R== 'a');
}

void TestReceiveChar(void)
{
   UART_DATA_R = 'b';
   UART_STATUS_R |= RECEIVE_COMPLETE_BIT;

   UART_ERROR_state_t error_state;
   error_state = UART_readChar(ptr_null);
   assert(error_state == E_UART_NULL_PTR);

   uint8_t data;
   error_state = UART_readChar(&data);

   assert(error_state == E_UART_SUCCESS);
   assert(data == 'b');
}

void TestSendString(void)
{
   UART_STATUS_R |= EMPTY_BUFFER_BIT;

   UART_ERROR_state_t error_state;
   error_state = UART_sendString(ptr_null);
   assert(error_state == E_UART_NULL_PTR);

   error_state = UART_sendString("dawdwwaz");
   assert(error_state == E_UART_SUCCESS);
   assert(UART_DATA_R == 'z');
}

void TestReceiveString(void)
{
   UART_DATA_R = NEW_LINE;
   UART_STATUS_R |= RECEIVE_COMPLETE_BIT;

   UART_ERROR_state_t error_state;
   error_state = UART_readString(ptr_null);
   assert(error_state == E_UART_NULL_PTR);

   uint8_t data[10];
   error_state = UART_readString(&data);

   assert(error_state == E_UART_SUCCESS);
   assert(data[0] == NEW_LINE);
   assert(data[1] == END_OF_STRING);
}

void main(void)
{	
   TestNotInit();

   TestInit();

   TestSendChar();
   
   TestReceiveChar();

   TestSendString();

   TestReceiveString();
   
   printf("all tests passed successfully!\n");
}
