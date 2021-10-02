/*
 * TestCases.c
 *
 * Created: 9/2/2021 9:35:06 AM
 *  Author: Mohamed Wagdy
 */

 /*- INCLUDES
 ----------------------------------------------*/
#include <stdio.h>
#include "ButtonClient.h"

 /*- LOCAL MACROS
 ------------------------------------------*/
#define NUMBER_OF_TESTCASES			(uint8_t)(16)

 /*- LOCAL FUNCTIONS PROTOTYPES
 ----------------------------*/
static void TestAssert(uint8_t ID, uint8_t State);
static void CBF(void);
static void TestInit(void);
static void TestSetBTN(void);
static void TestSetTimer(void);
static void TestSetCBF(void);
static void TestEventReceive(void);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t u8_ID;
static uint8_t u8_PassedCounter = 0;
static ERROR_STATE_t BTNClient_ErrorState;
static STR_BTNClient_t BTN_Client;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern uint8_t ButtonState;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

/**
* @brief: This function Prints the Test State and increament Passed Tests if passed.
*
* @param [in]  ID		-  ID of the test.
* @param [in]  State	-  State of the test.
*/
void TestAssert(uint8_t ID, uint8_t State)
{
	if (State)
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
* @brief: This function is event callback function.
*/
void CBF(void)
{

}

/**
* @brief: This function tests init function.
*/
void TestInit(void)
{
	/* Initialize With Address Pointinig to Null Pointer. */
	u8_ID = 1;
	BTNClient_ErrorState = BUTTONClient_Init(NULL_PTR);
	TestAssert(
		u8_ID, (ERROR_NOK == BTNClient_ErrorState)
	);

	/* Initialize With valid data */
	u8_ID = 2;
	BTNClient_ErrorState = BUTTONClient_Init(&BTN_Client);
	TestAssert(
		u8_ID, (ERROR_OK == BTNClient_ErrorState) &&
		(BTN_Client.u8_ButtonCh == BTN_INVALID_CH) && (BTN_Client.u8_ButtonState == 0) &&
		(BTN_Client.u8_OldButtonState == 0) && (BTN_Client.u8_TimerCh == INVALID_TIMER_CH) &&
		(BTN_Client.u32_DebounceDelay == 0) && (BTN_Client.ENU_ClientState == ButtonClient_Ready) &&
		(BTN_Client.EventCallback == NULL_PTR)
	);
}

/**
* @brief: This function setting button channel.
*/
static void TestSetBTN(void)
{
	/* Set BTN in null pointer. */
	u8_ID = 3;
	BTNClient_ErrorState = BUTTONClient_SetBtn(NULL_PTR, BTN_0);
	TestAssert(
		u8_ID, (ERROR_NOK == BTNClient_ErrorState)
	);

	/* Set invalid BTN ch. */
	u8_ID = 4;
	BTNClient_ErrorState = BUTTONClient_SetBtn(&BTN_Client, BTN_INVALID_CH);
	TestAssert(
		u8_ID, (ERROR_NOK == BTNClient_ErrorState)
	);

	/* Set Valid BTN ch. */
	u8_ID = 5;
	BTNClient_ErrorState = BUTTONClient_SetBtn(&BTN_Client, BTN_0);
	TestAssert(
		u8_ID, (ERROR_OK == BTNClient_ErrorState) && (BTN_Client.u8_ButtonCh == BTN_0)
	);
}

/**
* @brief: This function setting timer channel and delay value.
*/
void TestSetTimer(void)
{
	/* Set Timer in null pointer. */
	u8_ID = 6;
	BTNClient_ErrorState = BUTTONClient_SetTimer(NULL_PTR, TIMER_2, 20);
	TestAssert(
		u8_ID, (ERROR_NOK == BTNClient_ErrorState)
	);

	/* Set invalid timer ch. */
	u8_ID = 7;
	BTNClient_ErrorState = BUTTONClient_SetTimer(&BTN_Client, INVALID_TIMER_CH, 20);
	TestAssert(
		u8_ID, (ERROR_NOK == BTNClient_ErrorState)
	);

	/* Set Valid Timer ch. */
	u8_ID = 8;
	BTNClient_ErrorState = BUTTONClient_SetTimer(&BTN_Client, TIMER_2, 20);
	TestAssert(
		u8_ID, (ERROR_OK == BTNClient_ErrorState) && (BTN_Client.u8_TimerCh == TIMER_2) &&
		(BTN_Client.u32_DebounceDelay == 20)
	);
}

/**
* @brief: This function tests setting Callback function.
*/
void TestSetCBF(void)
{
	/* Set Callback in null pointer. */
	u8_ID = 9;
	BTNClient_ErrorState = BUTTONClient_SetEventCallback(NULL_PTR, CBF);
	TestAssert(
		u8_ID, (ERROR_NOK == BTNClient_ErrorState)
	);

	/* Set Null Callback. */
	u8_ID = 10;
	BTNClient_ErrorState = BUTTONClient_SetEventCallback(&BTN_Client, NULL_PTR);
	TestAssert(
		u8_ID, (ERROR_NOK == BTNClient_ErrorState)
	);

	/* Set Valid Callback Function. */
	u8_ID = 11;
	BTNClient_ErrorState = BUTTONClient_SetEventCallback(&BTN_Client, CBF);
	TestAssert(
		u8_ID, (ERROR_OK == BTNClient_ErrorState) && (BTN_Client.EventCallback == CBF)
	);
}

/**
* @brief: This function tests receiving event.
*/
static void TestEventReceive(void)
{
	/* Event Receive of null pointer. */
	u8_ID = 12;
	BTNClient_ErrorState = BUTTONClient_EventReceive(NULL_PTR);
	TestAssert(
		u8_ID, (ERROR_NOK == BTNClient_ErrorState)
	);

	/* Set BTN State. */
	ButtonState = 1;
	
	/* Change State from Ready To Delay */
	u8_ID = 13;
	BTNClient_ErrorState = BUTTONClient_EventReceive(&BTN_Client);
	TestAssert(
		u8_ID, (ERROR_NOK == BTNClient_ErrorState) && (BTN_Client.ENU_ClientState == ButtonClient_Delay) &&
		(BTN_Client.u8_OldButtonState == ButtonState)
	);

	/* Change State from Delay To Second Reading ready */
	u8_ID = 14;
	BTNClient_ErrorState = BUTTONClient_EventReceive(&BTN_Client);
	TestAssert(
		u8_ID, (ERROR_NOK == BTNClient_ErrorState) && (BTN_Client.ENU_ClientState == ButtonClient_StateReady)
	);

	/* Btn Reading Changed Before Second Reading */
	ButtonState = 0;
	u8_ID = 15;
	BTNClient_ErrorState = BUTTONClient_EventReceive(&BTN_Client);
	TestAssert(
		u8_ID, (ERROR_NOK == BTNClient_ErrorState) && (BTN_Client.ENU_ClientState == ButtonClient_Ready)
	);

	/* Btn Reading The Same Before and After Delay. */
	ButtonState = 1;
	u8_ID = 16;
	BTNClient_ErrorState = BUTTONClient_EventReceive(&BTN_Client);
	BTNClient_ErrorState = BUTTONClient_EventReceive(&BTN_Client);
	BTNClient_ErrorState = BUTTONClient_EventReceive(&BTN_Client);
	TestAssert(
		u8_ID, (ERROR_OK == BTNClient_ErrorState) && (BTN_Client.ENU_ClientState == ButtonClient_Ready) &&
		(BTN_Client.u8_OldButtonState == ButtonState) && (BTN_Client.u8_ButtonState == ButtonState)
	);
}

/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function runs all test cases.
*/
void main(void)
{
	TestInit();

	TestSetBTN();

	TestSetTimer();

	TestSetCBF();

	TestEventReceive();

	printf("%u/%u TestCases passed.\n", u8_PassedCounter, NUMBER_OF_TESTCASES);

	printf("Press Enter key to close this window . . . \n");

	getchar();
}