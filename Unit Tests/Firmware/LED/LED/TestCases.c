/*
 * TestCases.c
 *
 * Created: 7/13/2021 5:25:47 PM
 *  Author: Mohamed Wagdy
 */

 /*- INCLUDES
 ----------------------------------------------*/
#include <stdio.h>
#include "Firmware/LED/LED.h"

 /*- LOCAL MACROS
 ------------------------------------------*/
#define NUMBER_OF_TESTCASES      (uint8_t)(15)
#define INVALID_CHANNEL          (uint8_t)(20)

 /*- LOCAL FUNCTIONS PROTOTYPES
 ----------------------------*/
void TestNotInit(void);
void TestInit(void);
void TestLEDOff(void);
void TestLEDOn(void);
void TestLEDToggle(void);
void TestLEDStatus(void);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t* ptr_null;
static uint8_t u8_ID;
static uint8_t u8_PassedCounter = 0;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
#ifdef LED_CH_1
extern const uint8_t LED_CH_1_PORT;
extern const uint8_t LED_CH_1_PIN;
#endif
#ifdef LED_CH_2
extern const uint8_t LED_CH_2_PORT;
extern const uint8_t LED_CH_2_PIN;
#endif
#ifdef LED_CH_3
extern const uint8_t LED_CH_3_PORT;
extern const uint8_t LED_CH_3_PIN;
#endif

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/**
* @brief: This function tests Calling all APIs before initialization.
*/
void TestNotInit(void)
{
   LED_ERROR_state_t LED_ErrorState;

   /* Calling all APIs before initialization */
   u8_ID = 1;
   LED_ErrorState = LED_On(LED_CH_1);
   if (
      (LED_ErrorState == E_LED_NOT_INIT)
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   u8_ID = 2;
   LED_ErrorState = LED_Off(LED_CH_1);
   if (
      (LED_ErrorState == E_LED_NOT_INIT)
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   u8_ID = 3;
   LED_ErrorState = LED_Toggle(LED_CH_1);
   if (
      (LED_ErrorState == E_LED_NOT_INIT)
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
   u8_ID = 4;
   LED_ErrorState = LED_Status(LED_CH_1, &data);
   if (
      (LED_ErrorState == E_LED_NOT_INIT)
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
* @brief: This function tests init function.
*/
void TestInit(void)
{
   LED_ERROR_state_t LED_ErrorState;

   /* Not init before */
   u8_ID = 5;
   LED_ErrorState = LED_Init();
   if (
      (LED_ErrorState == E_LED_SUCCESS)
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   /* Initialized before */
   u8_ID = 6;
   LED_ErrorState = LED_Init();
   if (
      (LED_ErrorState == E_LED_INIT_BEFORE)
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
* @brief: This function tests Led off API.
*/
void TestLEDOff(void)
{
   LED_ERROR_state_t LED_ErrorState;
 
   /* Invalid Channel */
   u8_ID = 7;
   LED_ErrorState = LED_Off(INVALID_CHANNEL);
   if (
      (LED_ErrorState == E_LED_INVALID_CH_NO)
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
   LED_ErrorState = LED_Off(LED_CH_1);
   if (
      (LED_ErrorState == E_LED_SUCCESS)
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
* @brief: This function tests LED on API.
*/
void TestLEDOn(void)
{
   LED_ERROR_state_t LED_ErrorState;

   /* Invalid Channel */
   u8_ID = 9;
   LED_ErrorState = LED_On(INVALID_CHANNEL);
   if (
      (LED_ErrorState == E_LED_INVALID_CH_NO)
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
   LED_ErrorState = LED_On(LED_CH_1);
   if (
      (LED_ErrorState == E_LED_SUCCESS)
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
* @brief: This function tests LED Toggle API.
*/
void TestLEDToggle(void)
{
   LED_ERROR_state_t LED_ErrorState;

   /* Invalid Channel */
   u8_ID = 11;
   LED_ErrorState = LED_Toggle(INVALID_CHANNEL);
   if (
      (LED_ErrorState == E_LED_INVALID_CH_NO)
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
   u8_ID = 12;
   LED_ErrorState = LED_Toggle(LED_CH_1);
   if (
      (LED_ErrorState == E_LED_SUCCESS)
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
* @brief: This function tests LED Status API.
*/
void TestLEDStatus(void)
{
   LED_ERROR_state_t LED_ErrorState;

   /* Null Pointer */
   u8_ID = 13;
   LED_ErrorState = LED_Status(LED_CH_1, ptr_null);
   if (
      (LED_ErrorState == E_LED_NULL_PTR)
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   uint8_t data = 0;
   /* Invalid Channel */
   u8_ID = 14;
   LED_ErrorState = LED_Status(INVALID_CHANNEL, &data);
   if (
      (LED_ErrorState == E_LED_INVALID_CH_NO) && (data == 0)
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
   u8_ID = 15;
   LED_ErrorState = LED_Status(LED_CH_1, &data);
   if (
      (LED_ErrorState == E_LED_SUCCESS) && (data == 1)
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
   TestNotInit();

   TestInit();

   TestLEDOff();

   TestLEDOn();

   TestLEDToggle();

   TestLEDStatus();

   printf("%u/%u TestCases passed.\n", u8_PassedCounter, NUMBER_OF_TESTCASES);

   printf("Press Enter key to close this window . . . \n");

   getchar();
}
