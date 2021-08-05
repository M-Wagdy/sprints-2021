/*
 * TestCases.c
 *
 * Created: 7/13/2021 5:25:47 PM
 *  Author: Mohamed Wagdy
 */

 /*- INCLUDES
 ----------------------------------------------*/
#include <stdio.h>
#include "Firmware/EEPROM/EEPROM.h"

 /*- LOCAL MACROS
 ------------------------------------------*/
#define NUMBER_OF_TESTCASES      (uint8_t)(13)
#define INVALID_CHANNEL          (uint8_t)(20)

 /*- LOCAL FUNCTIONS PROTOTYPES
 ----------------------------*/
void TestInit(void);
void TestRead(void);
void TestWrite(void);
void TestReadBytes(void);
void TestWriteBytes(void);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t* ptr_null;
static uint8_t u8_ID;
static uint8_t u8_PassedCounter = 0;
static EEPROM_ERROR_state_t EEPROM_ErrorState;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

/**
* @brief: This function tests init function.
*/
void TestInit(void)
{
   /* Invalid Channel */
   u8_ID = 1;
   EEPROM_ErrorState = EEPROM_Init(INVALID_CHANNEL);
   if (
      (EEPROM_ErrorState == E_EEPROM_INVALID_CH_NO)
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
   EEPROM_ErrorState = EEPROM_Init(EEPROM_CH_0);
   if (
      (EEPROM_ErrorState == E_EEPROM_SUCCESS)
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
* @brief: This function tests reading from EEPROM.
*/
void TestRead(void)
{
   /* Null Pointer */
   u8_ID = 3;
   EEPROM_ErrorState = EEPROM_Read(EEPROM_CH_0, MEMORY_BLOCK_1, 0x00, ptr_null);
   if (
      (EEPROM_ErrorState == E_EEPROM_NULL_PTR)
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
   u8_ID = 4;
   EEPROM_ErrorState = EEPROM_Read(INVALID_CHANNEL, MEMORY_BLOCK_1, 0x00, &data);
   if (
      (EEPROM_ErrorState == E_EEPROM_INVALID_CH_NO)
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
   EEPROM_ErrorState = EEPROM_Read(EEPROM_CH_0, MEMORY_BLOCK_1, 0x00, &data);
   if (
      (EEPROM_ErrorState == E_EEPROM_SUCCESS) && (data == 'A')
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
* @brief: This function tests Writing to EEPORM.
*/
void TestWrite(void)
{
   /* Invalid Channel */
   u8_ID = 6;
   EEPROM_ErrorState = EEPROM_Write(INVALID_CHANNEL, MEMORY_BLOCK_1, 0x00, 'a');
   if (
      (EEPROM_ErrorState == E_EEPROM_INVALID_CH_NO)
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
   u8_ID = 7;
   EEPROM_ErrorState = EEPROM_Write(EEPROM_CH_0, MEMORY_BLOCK_1, 0x00, 'a');
   if (
      (EEPROM_ErrorState == E_EEPROM_SUCCESS)
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
* @brief: This function tests reading bytes from EEPROM.
*/
void TestReadBytes(void)
{
   /* Null Pointer */
   u8_ID = 8;
   EEPROM_ErrorState = EEPROM_ReadBytes(EEPROM_CH_0, MEMORY_BLOCK_1, 0x00, ptr_null, 3);
   if (
      (EEPROM_ErrorState == E_EEPROM_NULL_PTR)
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   uint8_t data[3] = { 0, 0, 0 };

   /* Invalid Channel */
   u8_ID = 9;
   EEPROM_ErrorState = EEPROM_ReadBytes(INVALID_CHANNEL, MEMORY_BLOCK_1, 0x00, &data, 3);
   if (
      (EEPROM_ErrorState == E_EEPROM_INVALID_CH_NO) && (data[0] == 0) && (data[1] == 0) && (data[2] == 0)
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
   EEPROM_ErrorState = EEPROM_ReadBytes(EEPROM_CH_0, MEMORY_BLOCK_1, 0x00, &data, 3);
   if (
      (EEPROM_ErrorState == E_EEPROM_SUCCESS) && (data[0] == 'A') && (data[1] == 'A') && (data[2] == 'A')
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
* @brief: This function tests Writing bytes to EEPORM.
*/
void TestWriteBytes(void)
{
   /* Null Pointer */
   u8_ID = 11;
   EEPROM_ErrorState = EEPROM_WriteBytes(EEPROM_CH_0, MEMORY_BLOCK_1, 0x00, ptr_null, 3);
   if (
      (EEPROM_ErrorState == E_EEPROM_NULL_PTR)
      )
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   uint8_t data[3] = { 0, 0, 0 };

   /* Invalid Channel */
   u8_ID = 12;
   EEPROM_ErrorState = EEPROM_WriteBytes(INVALID_CHANNEL, MEMORY_BLOCK_1, 0x00, &data, 3);
   if (
      (EEPROM_ErrorState == E_EEPROM_INVALID_CH_NO)
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
   u8_ID = 13;
   EEPROM_ErrorState = EEPROM_WriteBytes(EEPROM_CH_0, MEMORY_BLOCK_1, 0x00, &data, 3);
   if (
      (EEPROM_ErrorState == E_EEPROM_SUCCESS)
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

   TestRead();

   TestWrite();

   TestReadBytes();

   TestWriteBytes();

   printf("%u/%u TestCases passed.\n", u8_PassedCounter, NUMBER_OF_TESTCASES);

   printf("Press Enter key to close this window . . . \n");

   getchar();
}