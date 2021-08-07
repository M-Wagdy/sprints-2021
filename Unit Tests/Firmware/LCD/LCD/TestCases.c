/*
 * TestCases.c
 *
 * Created: 7/13/2021 5:25:47 PM
 *  Author: Mohamed Wagdy
 */

 /*- INCLUDES
 ----------------------------------------------*/
#include <stdio.h>
#include "Firmware/LCD/LCD.h"

 /*- LOCAL MACROS
 ------------------------------------------*/
#define NUMBER_OF_TESTCASES      (uint8_t)(11)
#define INVALID_CHANNEL          (uint8_t)(20)

 /*- LOCAL FUNCTIONS PROTOTYPES
 ----------------------------*/
void TestInit(void);
void TestSendCmd(void);
void TestSendChar(void);
void TestSendString(void);
void TestSetRowCol(void);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t* ptr_null;
static uint8_t u8_ID;
static uint8_t u8_PassedCounter = 0;
static LCD_ERROR_state_t LCD_ErrorState;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
#ifdef LCD_CH_0
extern const uint8_t LCD_CH_0_RS_PORT;
extern const uint8_t LCD_CH_0_RS_PIN;
extern const uint8_t LCD_CH_0_RW_PORT;
extern const uint8_t LCD_CH_0_RW_PIN;
extern const uint8_t LCD_CH_0_E_PORT;
extern const uint8_t LCD_CH_0_E_PIN;
extern const uint8_t LCD_CH_0_DATA_PORT;
extern const uint8_t LCD_CH_0_DATA_START_PIN;
#endif

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

/**
* @brief: This function tests init function.
*/
void TestInit(void)
{
   /* Invalid Channel */
   u8_ID = 1;
   LCD_ErrorState = LCD_Init(INVALID_CHANNEL);
   if (
      (LCD_ErrorState == E_LCD_INVALID_CH)
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
   LCD_ErrorState = LCD_Init(LCD_CH_0);
   if (
      (LCD_ErrorState == E_LCD_SUCCESS)
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
* @brief: This function tests Sending a Command to LCD.
*/
void TestSendCmd(void)
{
   /* Invalid Channel */
   u8_ID = 3;
   LCD_ErrorState = LCD_SendCommand(INVALID_CHANNEL, LCD_CLEAR);
   if (
      (LCD_ErrorState == E_LCD_INVALID_CH)
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
   LCD_ErrorState = LCD_SendCommand(LCD_CH_0, LCD_CLEAR);
   if (
      (LCD_ErrorState == E_LCD_SUCCESS)
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
* @brief: This function tests Sending a Char to LCD.
*/
void TestSendChar(void)
{
   /* Invalid Channel */
   u8_ID = 5;
   LCD_ErrorState = LCD_SendCharacter(INVALID_CHANNEL, 'a');
   if (
      (LCD_ErrorState == E_LCD_INVALID_CH)
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
   LCD_ErrorState = LCD_SendCharacter(LCD_CH_0, 'a');
   if (
      (LCD_ErrorState == E_LCD_SUCCESS)
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
* @brief: This function tests Sending a String to LCD.
*/
void TestSendString(void)
{
   /* Null Pointer */
   u8_ID = 7;
   LCD_ErrorState = LCD_SendString(LCD_CH_0, ptr_null);
   if (
      (LCD_ErrorState == E_LCD_NULL_PTR)
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   uint8_t String[3] = { 'a', 'b', '\0' };

   /* Invalid Channel */
   u8_ID = 8;
   LCD_ErrorState = LCD_SendString(INVALID_CHANNEL, String);
   if (
      (LCD_ErrorState == E_LCD_INVALID_CH)
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
   u8_ID = 9;
   LCD_ErrorState = LCD_SendString(LCD_CH_0, String);
   if (
      (LCD_ErrorState == E_LCD_SUCCESS)
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
* @brief: This function tests Setting cursor row and col of LCD.
*/
void TestSetRowCol(void)
{
   /* Invalid Channel */
   u8_ID = 10;
   LCD_ErrorState = LCD_SetToRowCol(INVALID_CHANNEL, 1,1);
   if (
      (LCD_ErrorState == E_LCD_INVALID_CH)
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
   u8_ID = 11;
   LCD_ErrorState = LCD_SetToRowCol(LCD_CH_0, 1,1);
   if (
      (LCD_ErrorState == E_LCD_SUCCESS)
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

   TestSendCmd();

   TestSendChar();

   TestSendString();

   TestSetRowCol();

   printf("%u/%u TestCases passed.\n", u8_PassedCounter, NUMBER_OF_TESTCASES);

   printf("Press Enter key to close this window . . . \n");

   getchar();
}