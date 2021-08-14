/*
 * TestCases.c
 *
 * Created: 7/13/2021 5:25:47 PM
 *  Author: Mohamed Wagdy
 */

 /*- INCLUDES
 ----------------------------------------------*/
#include <stdio.h>
#include "Firmware/Keypad/Keypad.h"

 /*- LOCAL MACROS
 ------------------------------------------*/
#define NUMBER_OF_TESTCASES      (uint8_t)(5)
#define INVALID_CHANNEL          (uint8_t)(20)

 /*- LOCAL FUNCTIONS PROTOTYPES
 ----------------------------*/
void TestInit(void);
void TestGetKeyValue(void);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t* ptr_null;
static uint8_t u8_ID;
static uint8_t u8_PassedCounter = 0;
static KEYPAD_ERROR_state_t KEYPAD_ErrorState;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
#ifdef KP_CH_0
extern const uint8_t KP_CH_0_COL_PORT;
extern const uint8_t KP_CH_0_COL_START_PIN;
extern const uint8_t KP_CH_0_ROW_PORT;
extern const uint8_t KP_CH_0_ROW_START_PIN;
extern const uint8_t KP_CH_0_MAP[KP_CH_0_ROWS][KP_CH_0_COLS];
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
   KEYPAD_ErrorState = KP_Init(INVALID_CHANNEL);
   if (
      (KEYPAD_ErrorState == E_KEYPAD_INVALID_CH)
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
   KEYPAD_ErrorState = KP_Init(KP_CH_0);
   if (
      (KEYPAD_ErrorState == E_KEYPAD_SUCCESS)
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
* @brief: This function tests Get Keypad pressed value.
*/
void TestGetKeyValue(void)
{
   /* Null Pointer */
   u8_ID = 3;
   KEYPAD_ErrorState = KP_GetPressedValue(KP_CH_0, ptr_null);
   if (
      (KEYPAD_ErrorState == E_KEYPAD_NULL_PTR)
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   uint8_t u8_data;

   /* Invalid Channel */
   u8_ID = 4;
   KEYPAD_ErrorState = KP_GetPressedValue(INVALID_CHANNEL, &u8_data);
   if (
      (KEYPAD_ErrorState == E_KEYPAD_INVALID_CH)
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
   u8_ID = 5;
   KEYPAD_ErrorState = KP_GetPressedValue(KP_CH_0, &u8_data);
   if (
      (KEYPAD_ErrorState == E_KEYPAD_SUCCESS) && (u8_data == 0)
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

   TestGetKeyValue();

   printf("%u/%u TestCases passed.\n", u8_PassedCounter, NUMBER_OF_TESTCASES);

   printf("Press Enter key to close this window . . . \n");

   getchar();
}