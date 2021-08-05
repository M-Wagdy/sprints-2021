/*
 * TestCases.c
 *
 * Created: 7/13/2021 5:25:47 PM
 *  Author: Mohamed Wagdy
 */

 /*- INCLUDES
 ----------------------------------------------*/
#include <stdio.h>
#include "App/Card/Card.h"

 /*- LOCAL MACROS
 ------------------------------------------*/
#define NUMBER_OF_TESTCASES                  (uint8_t)(5)
#define GLOBAL_BUFFER_SIZE                   (uint8_t)(255)
#define STRING_COUNTER_START                 (uint8_t)(0)

#define CARD_HOLDER_NAME_START_ADDRESS       (uint8_t)(0X00)
#define PAN_START_ADDRESS                    (uint8_t)(0X0A)
#define PIN_START_ADDRESS                    (uint8_t)(0X14)
#define CARD_HOLDER_NAME_STRING_SIZE         (uint8_t)(9)
#define PAN_STRING_SIZE                      (uint8_t)(9)
#define PIN_STRING_SIZE                      (uint8_t)(4)

#define TRUE                                 (uint8_t)(1)
#define FALSE                                (uint8_t)(0)

#define ZERO_ASCII                           (uint8_t)(0x30)

 /*- LOCAL FUNCTIONS PROTOTYPES
 ----------------------------*/
static void ClearMemory(void);
static void ClearCardData(void);
static void FillMemoryOnes(void);
static void FillBufferAdmin(void);
static uint8_t CheckMemoryFromUser(void);
static uint8_t CheckMemoryFilledOnes(void);

void TestInit(void);
void TestGetData(void);
void TestSetData(void);
void TestReceive(void);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t* ptr_null;
static uint8_t u8_ID;
static uint8_t u8_PassedCounter = 0;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern uint8_t gu8_RxBuffer[GLOBAL_BUFFER_SIZE];
extern uint8_t gu8_Counter;
extern uint8_t gu8_TerminalData[10];
extern STR_cardData_t gSTR_CardData;
extern uint8_t gau8_Memory[25];

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/**
* @brief: This function Initialize EEPROM Memory with 0xFF (Not initialized bits).
*/
void ClearMemory(void)
{
   for (uint8_t u8_Counter = STRING_COUNTER_START; u8_Counter < 25; u8_Counter++)
   {
      gau8_Memory[u8_Counter] = 0xFF;
   }
}

/**
* @brief: This function clears card data.
*/
void ClearCardData(void)
{
   /* Clear Card Holder Name */
   for (uint8_t u8_Counter = STRING_COUNTER_START; u8_Counter < CARD_HOLDER_NAME_STRING_SIZE; u8_Counter++)
   {
      gSTR_CardData.au8_CardHolderName[u8_Counter] = '\0';
   }

   /* Clear PAN */
   for (uint8_t u8_Counter = STRING_COUNTER_START; u8_Counter < PAN_STRING_SIZE; u8_Counter++)
   {
      gSTR_CardData.au8_PAN[u8_Counter] = '\0';
   }

   /* Clear PIN */
   for (uint8_t u8_Counter = STRING_COUNTER_START; u8_Counter < PIN_STRING_SIZE; u8_Counter++)
   {
      gSTR_CardData.au8_PIN[u8_Counter] = '\0';
   }
}

/**
* @brief: This function Initializes EEPROM Memory with One Ascii.
*/
void FillMemoryOnes(void)
{
   for (uint8_t u8_Counter = STRING_COUNTER_START; u8_Counter < 25; u8_Counter++)
   {
      gau8_Memory[u8_Counter] = '1';
   }

   /* Add end of string after card holder name in memory  */
   gau8_Memory[9] = '\0';
   /* Add end of string after PAN in memory  */
   gau8_Memory[19] = '\0';
   /* Add end of string after PIN in memory  */
   gau8_Memory[24] = '\0';
}

/**
* @brief: This function Fills Uart Buffer with ADMIN string.
*/
void FillBufferAdmin(void)
{
   /* Addd data in the buffer */
   gu8_RxBuffer[0] = 'A';
   gu8_RxBuffer[1] = 'D';
   gu8_RxBuffer[2] = 'M';
   gu8_RxBuffer[3] = 'I';
   gu8_RxBuffer[4] = 'N';
   gu8_RxBuffer[5] = NEW_LINE;

   /* Set Buffer counter on the new line */
   gu8_Counter = 5;
}

/**
* @brief: This function Checks EEPROM is Filled With User Data.
*/
uint8_t CheckMemoryFromUser(void)
{
   uint8_t u8_MemoryCorrect = TRUE;
   uint8_t u8_CharactersCounter = 1;

   /* Compare Card Holder Name */
   for (uint8_t u8_NameCounter = STRING_COUNTER_START; u8_NameCounter < CARD_HOLDER_NAME_STRING_SIZE; u8_NameCounter++)
   {
      if (gSTR_CardData.au8_CardHolderName[u8_NameCounter] != (ZERO_ASCII + u8_CharactersCounter))
      {
         u8_MemoryCorrect = FALSE;
         break;
      }
      u8_CharactersCounter++;
   }

   u8_CharactersCounter = 1;

   if (u8_MemoryCorrect == TRUE)
   {
      /* Compare PAN */
      for (uint8_t u8_PANCounter = STRING_COUNTER_START; u8_PANCounter < PAN_STRING_SIZE; u8_PANCounter++)
      {
         if (gSTR_CardData.au8_PAN[u8_PANCounter] != (ZERO_ASCII + u8_CharactersCounter))
         {
            u8_MemoryCorrect = FALSE;
            break;
         }
         u8_CharactersCounter++;
      }
   }

   u8_CharactersCounter = 1;

   if (u8_MemoryCorrect == TRUE)
   {
      /* Compare PIN */
      for (uint8_t u8_PINCounter = STRING_COUNTER_START; u8_PINCounter < PIN_STRING_SIZE; u8_PINCounter++)
      {
         if (gSTR_CardData.au8_PIN[u8_PINCounter] != (ZERO_ASCII + u8_CharactersCounter))
         {
            u8_MemoryCorrect = FALSE;
            break;
         }
         u8_CharactersCounter++;
      }
   }

   return u8_MemoryCorrect;
}

uint8_t CheckMemoryFilledOnes(void)
{
   uint8_t u8_MemoryCorrect = TRUE;

   /* Compare Card Holder Name */
   for (uint8_t u8_NameCounter = STRING_COUNTER_START; u8_NameCounter < CARD_HOLDER_NAME_STRING_SIZE; u8_NameCounter++)
   {
      if (gSTR_CardData.au8_CardHolderName[u8_NameCounter] != '1')
      {
         u8_MemoryCorrect = FALSE;
         break;
      }
   }

   if (u8_MemoryCorrect == TRUE)
   {
      /* Compare PAN */
      for (uint8_t u8_PANCounter = STRING_COUNTER_START; u8_PANCounter < PAN_STRING_SIZE; u8_PANCounter++)
      {
         if (gSTR_CardData.au8_PAN[u8_PANCounter] != '1')
         {
            u8_MemoryCorrect = FALSE;
            break;
         }
      }
   }

   if (u8_MemoryCorrect == TRUE)
   {
      /* Compare PIN */
      for (uint8_t u8_PINCounter = STRING_COUNTER_START; u8_PINCounter < PIN_STRING_SIZE; u8_PINCounter++)
      {
         if (gSTR_CardData.au8_PIN[u8_PINCounter] != '1')
         {
            u8_MemoryCorrect = FALSE;
            break;
         }
      }
   }

   return u8_MemoryCorrect;
}


/**
* @brief: This function tests init function.
*/
void TestInit(void)
{
   /* Clear Card Data */
   ClearCardData();

   /* Clear Memory */
   ClearMemory();

   /* No Data In Memory */
   u8_ID = 1;
   CARD_Init();
   
   /* Check Data Stored In Memory */
   if (CheckMemoryFromUser() == TRUE)
   {
      printf("Test Case ID: %u - PASSED \n", u8_ID);
      u8_PassedCounter++;
   }
   else
   {
      printf("Test Case ID: %u - FAILED \n", u8_ID);
   }

   /* Clear Card Data */
   ClearCardData();

   /* Pre add data in memory */
   FillMemoryOnes();

   /* Data In Memory */
   u8_ID = 2;
   CARD_Init();

   /* Check Data Stored In Memory */
   if (CheckMemoryFilledOnes() == TRUE)
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
void TestGetData(void)
{
   /* Clear Card Data */
   ClearCardData();

   /* Pre add data in memory */
   FillMemoryOnes();

   /* Get Data From Memory */
   u8_ID = 3;
   CARD_GetData();

   /* Check Data Stored In Memory */
   if (CheckMemoryFilledOnes() == TRUE)
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
void TestSetData(void)
{
   /* Clear Card Data */
   ClearCardData();

   /* Pre add data in memory */
   FillMemoryOnes();

   /* Set Data In Memory */
   u8_ID = 4;
   CARD_SetData();

   /* Check Data Stored In Memory */
   if (CheckMemoryFromUser() == TRUE)
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
void TestReceive(void)
{
   /* Clear Card Data */
   ClearCardData();

   /* Pre add data in memory */
   FillBufferAdmin();

   /* Set Data In Memory */
   u8_ID = 5;
   CARD_Receive();

   /* Check Data Stored In Memory */
   if (CheckMemoryFromUser() == TRUE)
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

   TestGetData();

   TestSetData();

   TestReceive();

   printf("%u/%u TestCases passed.\n", u8_PassedCounter, NUMBER_OF_TESTCASES);

   printf("Press Enter key to close this window . . . \n");

   getchar();
}