/*
 * TestCases.c
 *
 * Created: 7/13/2021 5:25:47 PM
 *  Author: Mohamed Wagdy
 */

 /*- INCLUDES
 ----------------------------------------------*/
#include <stdio.h>
#include "Firmware/Motor/Motor.h"

 /*- LOCAL MACROS
 ------------------------------------------*/
#define NUMBER_OF_TESTCASES      (uint8_t)(6)
#define INVALID_CHANNEL          (uint8_t)(20)

 /*- LOCAL FUNCTIONS PROTOTYPES
 ----------------------------*/
void TestInit(void);
void TestStart(void);
void TestStop(void);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t* ptr_null;
static uint8_t u8_ID;
static uint8_t u8_PassedCounter = 0;
static MOTOR_ERROR_state_t MOTOR_ErrorState;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
#ifdef MOTOR_CH_0
extern const uint8_t MOTOR_CH_0_PORT;
extern const uint8_t MOTOR_CH_0_PIN;
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
   MOTOR_ErrorState = MOTOR_Init(INVALID_CHANNEL);
   if (
      (MOTOR_ErrorState == E_MOTOR_INVALID_CH)
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
   MOTOR_ErrorState = MOTOR_Init(MOTOR_CH_0);
   if (
      (MOTOR_ErrorState == E_MOTOR_SUCCESS)
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
* @brief: This function tests Starting a motor.
*/
void TestStart(void)
{
   /* Invalid Channel */
   u8_ID = 3;
   MOTOR_ErrorState = MOTOR_Start(INVALID_CHANNEL);
   if (
      (MOTOR_ErrorState == E_MOTOR_INVALID_CH)
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
   MOTOR_ErrorState = MOTOR_Start(MOTOR_CH_0);
   if (
      (MOTOR_ErrorState == E_MOTOR_SUCCESS)
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
* @brief: This function tests Stopping a motor.
*/
void TestStop(void)
{
   /* Invalid Channel */
   u8_ID = 5;
   MOTOR_ErrorState = MOTOR_Stop(INVALID_CHANNEL);
   if (
      (MOTOR_ErrorState == E_MOTOR_INVALID_CH)
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
   MOTOR_ErrorState = MOTOR_Stop(MOTOR_CH_0);
   if (
      (MOTOR_ErrorState == E_MOTOR_SUCCESS)
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

   TestStart();

   TestStop();

   printf("%u/%u TestCases passed.\n", u8_PassedCounter, NUMBER_OF_TESTCASES);

   printf("Press Enter key to close this window . . . \n");

   getchar();
}