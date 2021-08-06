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
#include "Mcal/Atmega32/UART/UART.h"

/*- LOCAL MACROS
------------------------------------------*/
#define MAX_STRING_SIZE       (uint16_t)(200)
#define INVALID_BAUD_RATE     (uint16_t)(4096)
#define EMPTY_BUFFER_BIT	   (uint8_t)(0x20)
#define RECEIVE_COMPLETE_BIT  (uint8_t)(0x80)
#define INVALID_CHANNEL       (uint8_t)(20)
#define INVALID_INT_TYPE      (uint8_t)(0)
#define NUMBER_OF_TESTCASES   (uint8_t)(34)

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/
void TestInit(void);
void TestSendChar(void);
void TestReceiveChar(void);
void TestReceiveString(void);
void TestReceiveString(void);
void TestEnableInterrupt(void);
void TestDisableInterrupt(void);
void TestSetCallback(void);
void TestFlushBuffer(void);
void TestSetData(void);
void TestGetData(void);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t* ptr_null;
static uint8_t u8_ID;
static uint8_t u8_PassedCounter = 0;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern const uint8_t UART_CH_0_CONTROL;
extern const uint8_t UART_CH_0_CONTROL_2;
extern uint16_t UART_CH_0_BaudRate;
extern Ptr_VoidFuncVoid_t g_TxCallback[UART_CH_NUMBER];
extern Ptr_VoidFuncVoid_t g_RxCallback[UART_CH_NUMBER];

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

/**
* @brief: This function tests init function.
*/
void TestInit(void)
{
   UART_ERROR_state_t UART_ErrorState;   

   /* Invalid Channel */
   u8_ID = 1;
   UART_ErrorState = UART_Init(INVALID_CHANNEL);
   if (
      (UART_ErrorState == E_UART_INVALID_CH) 
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   /* Invalid Baud */
   u8_ID = 2;
   UART_CH_0_BaudRate = MAX_BAUD_VALUE + 1;
   UART_ErrorState = UART_Init(UART_CH_0);
   /* make sure data is written correctly in registers */
   if (
      (UART_ErrorState == E_UART_INVALID_BAUD_RATE) 
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   /* initialize with Correct data */
   u8_ID = 3;
   UART_CH_0_BaudRate = CLK_8_MHZ_9600_BAUD;
   UART_ErrorState = UART_Init(UART_CH_0);
   /* make sure data is written correctly in registers */
   if (
      (UART_ErrorState == E_UART_SUCCESS) && (UART_CONTROL_R == UART_CH_0_CONTROL) && (UART_CONTROL_2_R == UART_CH_0_CONTROL_2) &&
	   (UART_BAUDRATE_LOW_R == (uint8_t)UART_CH_0_BaudRate) && (UART_BAUDRATE_HIGH_R == (uint8_t)(UART_CH_0_BaudRate>>8) )
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
   UART_STATUS_R |= EMPTY_BUFFER_BIT;
   
   UART_ERROR_state_t UART_ErrorState;

   /* Test Valid Channel */
   u8_ID = 4;
   UART_ErrorState = UART_TransmitChar(UART_CH_0, 'a');
   /* make sure write data is written in the register */
   if (
      (UART_ErrorState == E_UART_SUCCESS) && (UART_DATA_R == 'a') 
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   /* Test Invalid Channel */
   u8_ID = 5;
   UART_ErrorState = UART_TransmitChar(INVALID_CHANNEL, 'a');
   /* make sure correct return status */
   if (
      (UART_ErrorState == E_UART_INVALID_CH)
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
   UART_DATA_R = 'b';
   /* sets receive completer bit in the status register */
   UART_STATUS_R|= RECEIVE_COMPLETE_BIT;

   UART_ERROR_state_t UART_ErrorState;
   /* Null Pointer */
   u8_ID = 6;
   UART_ErrorState = UART_ReceiveChar(UART_CH_0, ptr_null);
   if (
      (UART_ErrorState == E_UART_NULL_PTR)
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
   /* Invalid Channel */
   u8_ID = 7;
   UART_ErrorState = UART_ReceiveChar(INVALID_CHANNEL, &data);
   if (
      (UART_ErrorState == E_UART_INVALID_CH)
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   /* get data */
   u8_ID = 8;
   UART_ErrorState = UART_ReceiveChar(UART_CH_0, &data);
   if (
      (UART_ErrorState == E_UART_SUCCESS) && (data == 'b')
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
   UART_STATUS_R |= EMPTY_BUFFER_BIT;

   UART_ERROR_state_t UART_ErrorState;
   /* Null Pointer */
   u8_ID = 9;
   UART_ErrorState = UART_TransmitString(UART_CH_0, ptr_null);
   if (
      (UART_ErrorState == E_UART_NULL_PTR)
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
   u8_ID = 10;
   UART_ErrorState = UART_TransmitString(INVALID_CHANNEL, "adw");
   if (
      (UART_ErrorState == E_UART_INVALID_CH)
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   /* Correct Data */
   u8_ID = 11;
   UART_ErrorState = UART_TransmitString(UART_CH_0, "dawdwwaz");
   if (
      (UART_ErrorState == E_UART_SUCCESS) && (UART_DATA_R == 'z')
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
   UART_DATA_R = NEW_LINE;
   /* sets receive completer bit in the status register */
   UART_STATUS_R |= RECEIVE_COMPLETE_BIT;

   UART_ERROR_state_t UART_ErrorState;
   /* Null Pointer */
   u8_ID = 12;
   UART_ErrorState = UART_ReceiveString(UART_CH_0, ptr_null);
   if (
      (UART_ErrorState == E_UART_NULL_PTR)
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
   /* Invalid Channel */
   u8_ID = 13;
   UART_ErrorState = UART_ReceiveString(INVALID_CHANNEL, &data);
   if (
      (UART_ErrorState == E_UART_INVALID_CH)
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   /* Correct data */
   u8_ID = 14;
   UART_ErrorState = UART_ReceiveString(UART_CH_0, &data);
   if (
      (UART_ErrorState == E_UART_SUCCESS) && (data[0] == NEW_LINE) && (data[1] == END_OF_STRING)
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
* @brief: This function tests enabling interrupts.
*/
void TestEnableInterrupt(void)
{
   /* Remove interrupt bits from control register */
   UART_CONTROL_R &= ~(TX_INT | RX_INT);

   UART_ERROR_state_t UART_ErrorState;
   
   /* Invalid interrupt type */
   u8_ID = 15;
   UART_ErrorState = UART_EnableInterrupt(UART_CH_0, INVALID_INT_TYPE);
   if (
      (UART_ErrorState == E_UART_INVALID_INT_TYPE)
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   /* Invalid channel */
   u8_ID = 16;
   UART_ErrorState = UART_EnableInterrupt(INVALID_CHANNEL, RX_INT);
   if (
      (UART_ErrorState == E_UART_INVALID_CH)
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   /* enable RX interrupt */
   u8_ID = 17;
   UART_ErrorState = UART_EnableInterrupt(UART_CH_0, RX_INT);
   if (
      (UART_ErrorState == E_UART_SUCCESS) && (UART_CONTROL_R & RX_INT)
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   /* enable TX interrupt */
   u8_ID = 18;
   UART_ErrorState = UART_EnableInterrupt(UART_CH_0, TX_INT);
   if (
      (UART_ErrorState == E_UART_SUCCESS) && (UART_CONTROL_R & TX_INT)
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
* @brief: This function tests disabling interrupts.
*/
void TestDisableInterrupt(void)
{
   /* Set interrupt bits from control register */
   UART_CONTROL_R |= (TX_INT | RX_INT);

   UART_ERROR_state_t UART_ErrorState;

   /* Invalid interrupt type */
   u8_ID = 19;
   UART_ErrorState = UART_DisableInterrupt(UART_CH_0, INVALID_INT_TYPE);
   if (
      (UART_ErrorState == E_UART_INVALID_INT_TYPE)
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   /* Invalid channel */
   u8_ID = 20;
   UART_ErrorState = UART_DisableInterrupt(INVALID_CHANNEL, RX_INT);
   if (
      (UART_ErrorState == E_UART_INVALID_CH)
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   /* disable RX interrupt */
   u8_ID = 21;
   UART_ErrorState = UART_DisableInterrupt(UART_CH_0, RX_INT);
   if (
      (UART_ErrorState == E_UART_SUCCESS) && !(UART_CONTROL_R & RX_INT)
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   /* disable TX interrupt */
   u8_ID = 22;
   UART_ErrorState = UART_DisableInterrupt(UART_CH_0, TX_INT);
   if (
      (UART_ErrorState == E_UART_SUCCESS) && !(UART_CONTROL_R & TX_INT)
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
   UART_ERROR_state_t UART_ErrorState;

   /* Invalid interrupt type */
   u8_ID = 23;
   UART_ErrorState = UART_SetCallback(UART_CH_0, INVALID_INT_TYPE, TestInit);
   if (
      (UART_ErrorState == E_UART_INVALID_INT_TYPE)
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   /* Invalid channel */
   u8_ID = 24;
   UART_ErrorState = UART_SetCallback(INVALID_CHANNEL, RX_INT, TestInit);
   if (
      (UART_ErrorState == E_UART_INVALID_CH)
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   /* Null Pointer */
   u8_ID = 25;
   UART_ErrorState = UART_SetCallback(UART_CH_0, RX_INT, ptr_null);
   if (
      (UART_ErrorState == E_UART_NULL_PTR)
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   /* Set RX interrupt callback */
   u8_ID = 26;
   UART_ErrorState = UART_SetCallback(UART_CH_0, RX_INT, TestInit);
   if (
      (UART_ErrorState == E_UART_SUCCESS) && (g_RxCallback[UART_CH_0] == TestInit)
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   /* Set TX interrupt callback */
   u8_ID = 27;
   UART_ErrorState = UART_SetCallback(UART_CH_0, TX_INT, TestInit);
   if (
      (UART_ErrorState == E_UART_SUCCESS) && (g_TxCallback[UART_CH_0] == TestInit)
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
* @brief: This function tests flushing receiver buffer.
*/
void TestFlushBuffer(void)
{
   /* Remove receive complete bit in the status register */
   UART_STATUS_R &= ~(RECEIVE_COMPLETE_BIT);

   UART_ERROR_state_t UART_ErrorState;

   /* Invalid channel */
   u8_ID = 28;
   UART_ErrorState = UART_FlushReceiveBuffer(INVALID_CHANNEL);
   if (
      (UART_ErrorState == E_UART_INVALID_CH)
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   /* Valid channel */
   u8_ID = 29;
   UART_ErrorState = UART_FlushReceiveBuffer(UART_CH_0);
   if (
      (UART_ErrorState == E_UART_SUCCESS)
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
* @brief: This function tests set data API.
*/
void TestSetData(void)
{
   /* Clear data register */
   UART_DATA_R = 0x00;

   UART_ERROR_state_t UART_ErrorState;

   /* Test Valid Channel */
   u8_ID = 30;
   UART_ErrorState = UART_SetData(UART_CH_0, 'a');
   /* make sure write data is written in the register */
   if (
      (UART_ErrorState == E_UART_SUCCESS) && (UART_DATA_R == 'a')
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   /* Clear data register */
   UART_DATA_R = 0x00;

   /* Test Invalid Channel */
   u8_ID = 31;
   UART_ErrorState = UART_TransmitChar(INVALID_CHANNEL, 'a');
   /* make sure correct return status */
   if (
      (UART_ErrorState == E_UART_INVALID_CH) && (UART_DATA_R == 0x00)
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
* @brief: This function tests get data API.
*/
void TestGetData(void)
{
   /* sets the received data in the register */
   UART_DATA_R = 'b';

   UART_ERROR_state_t UART_ErrorState;
   
   /* Null Pointer */
   u8_ID = 32;
   UART_ErrorState = UART_GetData(UART_CH_0, ptr_null);
   if (
      (UART_ErrorState == E_UART_NULL_PTR)
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   uint8_t data = 'a';
   /* Invalid Channel */
   u8_ID = 33;
   UART_ErrorState = UART_GetData(INVALID_CHANNEL, &data);
   if (
      (UART_ErrorState == E_UART_INVALID_CH) && (data == 'a')
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   /* get data */
   u8_ID = 34;
   UART_ErrorState = UART_GetData(UART_CH_0, &data);
   if (
      (UART_ErrorState == E_UART_SUCCESS) && (data == 'b')
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
   
   TestFlushBuffer();

   TestSetData();
   
   TestGetData();
   
   /* prints if no assertion error was raised */
   printf("%u/%u TestCases passed.\n", u8_PassedCounter, NUMBER_OF_TESTCASES);
}
