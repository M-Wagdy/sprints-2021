/*
 * TestCases.c
 *
 * Created: 7/13/2021 5:25:47 PM
 *  Author: Mohamed Wagdy
 */

 /*- INCLUDES
 ----------------------------------------------*/
#include <stdio.h>
#include "../../../../ATM_ECU/App/Admin/admin.h"

 /*- LOCAL MACROS
 ------------------------------------------*/
#define NUMBER_OF_TESTCASES                  (uint8_t)(6)
#define GLOBAL_BUFFER_SIZE                   (uint8_t)(255)
#define STRING_COUNTER_START                 (uint8_t)(0)

#define CARD_HOLDER_NAME_START_ADDRESS       (uint8_t)(0X00)
#define PAN_START_ADDRESS                    (uint8_t)(0X0A)
#define PIN_START_ADDRESS                    (uint8_t)(0X14)
#define CARD_HOLDER_NAME_STRING_SIZE         (uint8_t)(9)
#define PAN_BYTES_NO                      (uint8_t)(9)
#define PIN_STRING_SIZE                      (uint8_t)(4)

#define TRUE                                 (uint8_t)(1)
#define FALSE                                (uint8_t)(0)

#define ZERO_ASCII                           (uint8_t)(0x30)

 /*- LOCAL FUNCTIONS PROTOTYPES
 ----------------------------*/
static void ClearMemory(void);
static void ClearCardData(void);
static void FillMemoryOnes(void);
static uint8_t CheckMemoryFilledOnes(void);

void TestInit(void);
void TestSetAccount(void);
void TestGetAccount(void);
void TestSetMaximumAccount(void);
void TestGetMaximumAccount(void);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t* ptr_null;
static uint8_t u8_ID;
static uint8_t u8_PassedCounter = 0;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern uint8_t gau8_Memory[25];
extern uint8_t au8_PANNumbers[MAX_ACCOUNT_NO][PAN_BYTES_GUARD_NO];
extern uint8_t au8_PANNumber[PAN_BYTES_GUARD_NO];
extern uint8_t au8_AccountBalance[MAX_ACCOUNT_BYTES_NO];
extern uint8_t au8_PANAddress, au8_SPACEAddress, au8_AccountBalanceAddress;
extern uint8_t pin[PASS_BYTES_GUARD_NO];
extern uint8_t user_pin[USER_PASS_BYTES_NO];
extern f32_t ufloat_AccountBalance;
extern uint8_t u8_choice;

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
	for (uint8_t u8_Counter = STRING_COUNTER_START; u8_Counter < PIN_STRING_SIZE; u8_Counter++)
	{
		pin[u8_Counter] = '\0';
	}

	/* Clear PAN */
	for (uint8_t u8_Counter = STRING_COUNTER_START; u8_Counter < PAN_BYTES_NO; u8_Counter++)
	{
		au8_PANNumber[u8_Counter] = '\0';
	}

	/* Clear PIN */
	for (uint8_t u8_Counter = STRING_COUNTER_START; u8_Counter < PIN_STRING_SIZE; u8_Counter++)
	{
		au8_AccountBalance[u8_Counter] = '\0';
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
	gau8_Memory[4] = '\0';
	/* Add end of string after PAN in memory  */
	gau8_Memory[19] = '\0';
	/* Add end of string after PIN in memory  */
	gau8_Memory[24] = '\0';
}

uint8_t CheckPinFromUser(void)
{
	uint8_t u8_MemoryCorrect = TRUE;
	uint8_t u8_CharactersCounter = 1;
	/* Compare Pin */
	for (uint8_t u8_NameCounter = STRING_COUNTER_START; u8_NameCounter < PIN_STRING_SIZE; u8_NameCounter++)
	{
		if (pin[u8_NameCounter] != (ZERO_ASCII + u8_CharactersCounter))
		{
			u8_MemoryCorrect = FALSE;
			break;
		}
		u8_CharactersCounter++;
	}
	return u8_MemoryCorrect;
}

/**
* @brief: This function Checks EEPROM is Filled With User Data.
*/
uint8_t CheckPanFromUser(void)
{
	uint8_t u8_MemoryCorrect = TRUE;
	uint8_t u8_CharactersCounter = 1;
	if (u8_MemoryCorrect == TRUE)
	{
		/* Compare PAN */
		for (uint8_t u8_PANCounter = STRING_COUNTER_START; u8_PANCounter < PAN_BYTES_NO; u8_PANCounter++)
		{
			if (au8_PANNumber[u8_PANCounter] != (ZERO_ASCII + u8_CharactersCounter))
			{
				u8_MemoryCorrect = FALSE;
				break;
			}
			u8_CharactersCounter++;
		}
	}
	return u8_MemoryCorrect;
}
/**
* @brief: This function Checks EEPROM is Filled With User Data.
*/


uint8_t CheckPanFilledOnes(void)
{
	uint8_t u8_MemoryCorrect = TRUE;
	if (u8_MemoryCorrect == TRUE)
	{
		/* Compare PAN */
		for (uint8_t u8_PANCounter = STRING_COUNTER_START; u8_PANCounter < PAN_BYTES_NO; u8_PANCounter++)
		{
			if (au8_PANNumber[u8_PANCounter] != '1')
			{
				u8_MemoryCorrect = FALSE;
				break;
			}
		}
	}
	return u8_MemoryCorrect;
}

uint8_t CheckMemoryFilledOnes(void)
{
	uint8_t u8_MemoryCorrect = TRUE;

	/* Compare Card Holder Name */
	for (uint8_t u8_NameCounter = STRING_COUNTER_START; u8_NameCounter < PIN_STRING_SIZE; u8_NameCounter++)
	{
		if (pin[u8_NameCounter] != '1')
		{
			u8_MemoryCorrect = FALSE;
			break;
		}
	}

	if (u8_MemoryCorrect == TRUE)
	{
		/* Compare PAN */
		for (uint8_t u8_PANCounter = STRING_COUNTER_START; u8_PANCounter < PAN_BYTES_NO; u8_PANCounter++)
		{
			if (au8_PANNumber[u8_PANCounter] != '1')
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
			if (au8_AccountBalance[u8_PINCounter] != '1')
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
	ADMIN_Authenticate();

	/* Check Data Stored In Memory */
	if (CheckPinFromUser() == TRUE)
	{
		printf("Test Case ID: %u - PASSED \n", u8_ID);
		u8_PassedCounter++;
	}
	else
	{
		printf("Test Case ID: %u - FAILED \n", u8_ID);
	}

	u8_ID = 2;
	ADMIN_Interface(&u8_choice);
	/* Check Data Stored In Memory */
	if ((u8_choice >= '1') && (u8_choice <= '5'))
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
void TestGetAccount(void)
{
	/* Clear Card Data */
	ClearCardData();

	/* Pre add data in memory */
	FillMemoryOnes();

	/* Get Data From Memory */
	u8_ID = 3;
	ADMIN_GetAccount();

	/* Check Data Stored In Memory */
	if (CheckPanFilledOnes() == TRUE)
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
void TestSetAccount(void)
{
	/* Clear Card Data */
	ClearCardData();

	/* Pre add data in memory */
	FillMemoryOnes();

	/* Set Data In Memory */
	u8_ID = 4;
	ADMIN_SetAccount();

	/* Check Data Stored In Memory */
	if (CheckPanFromUser() == TRUE)
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
void TestGetMaximumAccount(void)
{
	/* Clear Card Data */
	ClearCardData();

	/* Pre add data in memory */
	FillMemoryOnes();

	/* Get Data From Memory */
	u8_ID = 5;
	ADMIN_GetMaxBalance();

	/* Check Data Stored In Memory */
	if (ufloat_AccountBalance < 9999.99)
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
void TestSetMaximumAccount(void)
{
	/* Clear Card Data */
	ClearCardData();

	/* Pre add data in memory */
	FillMemoryOnes();

	/* Get Data From Memory */
	u8_ID = 6;
	ADMIN_SetMaxBalance();

	/* Check Data Stored In Memory */
	if (ufloat_AccountBalance < 9999.99)
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

	TestGetAccount();

	TestSetAccount();

	TestGetMaximumAccount();

	TestSetMaximumAccount();

	printf("%u/%u TestCases passed.\n", u8_PassedCounter, NUMBER_OF_TESTCASES);

	printf("Press Enter key to close this window . . . \n");
}