/*
 * TestCases.c
 *
 * Created: 7/22/2021 9:35:06 AM
 *  Author: Mohamed Wagdy
 */

 /*- INCLUDES
 ----------------------------------------------*/
#include <stdio.h>
#include "DIO_HardwareProxy.h"

 /*- LOCAL MACROS
 ------------------------------------------*/
#define NUMBER_OF_TESTCASES			(uint8_t)(22)

 /*- LOCAL FUNCTIONS PROTOTYPES
 ----------------------------*/
static void TestAssert(uint8_t ID, uint8_t State);
static void TestBeforeInit(void);
static void TestInit(void);
static void TestConfigure(void);
static void TestAccess(void);
static void TestMutate(void);
static void TestDisable(void);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t u8_ID;
static uint8_t u8_PassedCounter = 0;
static ERROR_STATE_t DIO_ErrorState;
static STR_DIOProxy_t PORTA_Proxy;
static STR_DIOProxy_t PORTB_Proxy;
static STR_DIOProxy_t PORTC_Proxy;
static STR_DIOProxy_t PORTD_Proxy;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/

/* Uint32_t to make sure addresses are sequential in memory. */
extern uint32_t PORTA_Registers;
extern uint32_t PORTB_Registers;
extern uint32_t PORTC_Registers;
extern uint32_t PORTD_Registers;

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
 * @brief: This function tests calling functions before initialization.
 */
void TestBeforeInit(void)
{
	/* Configure Pin before initialization. */
	u8_ID = 1;
	DIO_ErrorState = DIOProxy_Configure(&PORTA_Proxy, PIN_1, PIN_OUTPUT, PIN_NO_RES);
	TestAssert(
		u8_ID, (ERROR_NOK == DIO_ErrorState)
	);

	/* Access Pin before initialization. */
	uint8_t PinData;

	u8_ID = 2;
	DIO_ErrorState = DIOProxy_AccessPin(&PORTB_Proxy, PIN_1, &PinData);
	TestAssert(
		u8_ID, (ERROR_NOK == DIO_ErrorState)
	);

	/* Mutate Pin Before Initialization */
	u8_ID = 3;
	DIO_ErrorState = DIOProxy_MutatePin(&PORTC_Proxy, PIN_1, PIN_HIGH);
	TestAssert(
		u8_ID, (ERROR_NOK == DIO_ErrorState)
	);
}

/**
* @brief: This function tests init function.
*/
void TestInit(void)
{
	/* Initialize With Address Pointinig to Null Pointer. */
	u8_ID = 4;
	DIO_ErrorState = DIOProxy_Init(&PORTA_Proxy, NULL_PTR);
	TestAssert(
		u8_ID, (ERROR_NOK == DIO_ErrorState)
	);

	/* Initialize With Struct Pointinig to Null Pointer. */
	u8_ID = 5;
	DIO_ErrorState = DIOProxy_Init(NULL_PTR, ((uint8_t)&PORTA_Registers + 3));
	TestAssert(
		u8_ID, (ERROR_NOK == DIO_ErrorState)
	);

	/* Initialize All Ports. */
	u8_ID = 6;
	DIO_ErrorState = DIOProxy_Init(&PORTA_Proxy, (&(uint8_t)PORTA_Registers + 2));
	DIO_ErrorState |= DIOProxy_Init(&PORTB_Proxy, (&(uint8_t)PORTB_Registers + 2));
	DIO_ErrorState |= DIOProxy_Init(&PORTC_Proxy, (&(uint8_t)PORTC_Registers + 2));
	DIO_ErrorState |= DIOProxy_Init(&PORTD_Proxy, (&(uint8_t)PORTD_Registers + 2));
	TestAssert(
		u8_ID, (ERROR_OK == DIO_ErrorState) && 
		(PORTA_Proxy.u8_Addr == (&(uint8_t)PORTA_Registers + 2)) &&
		(PORTB_Proxy.u8_Addr == (&(uint8_t)PORTB_Registers + 2)) && 
		(PORTC_Proxy.u8_Addr == (&(uint8_t)PORTC_Registers + 2)) &&
		(PORTD_Proxy.u8_Addr == (&(uint8_t)PORTD_Registers + 2))
	);
}

/**
* @brief: This function tests Configuring Pins.
*/
static void TestConfigure(void)
{
	/* Configure With Struct Pointinig to Null Pointer. */
	u8_ID = 7;
	DIO_ErrorState = DIOProxy_Configure(NULL_PTR, PIN_0, PIN_OUTPUT, PIN_NO_RES);
	TestAssert(
		u8_ID, (ERROR_NOK == DIO_ErrorState)
	);

	/* Configure invalid pin. */
	u8_ID = 8;
	DIO_ErrorState = DIOProxy_Configure(&PORTA_Proxy, PIN_INVALID, PIN_OUTPUT, PIN_NO_RES);
	TestAssert(
		u8_ID, (ERROR_NOK == DIO_ErrorState)
	);

	/* Configure Output Pin. */
	u8_ID = 9;
	DIO_ErrorState = DIOProxy_Configure(&PORTA_Proxy, PIN_0, PIN_OUTPUT, PIN_NO_RES);
	TestAssert(
		u8_ID, (ERROR_OK == DIO_ErrorState) && (PORTA_Registers == 0x000100)
	);

	/* Configure Input Pin. */
	u8_ID = 10;
	DIO_ErrorState = DIOProxy_Configure(&PORTA_Proxy, PIN_1, PIN_INPUT, PIN_NO_RES);
	TestAssert(
		u8_ID, (ERROR_OK == DIO_ErrorState) && (PORTA_Registers == 0x000100)
	);

	/* Configure Input Pull Up Pin. */
	u8_ID = 11;
	DIO_ErrorState = DIOProxy_Configure(&PORTA_Proxy, PIN_2, PIN_INPUT, PIN_PULLUP);
	TestAssert(
		u8_ID, (ERROR_OK == DIO_ErrorState) && (PORTA_Registers == 0x040100)
	);
}

/**
* @brief: This function tests Accessing Pins.
*/
void TestAccess(void)
{
	uint8_t PinData;
	/* Access With Struct Pointinig to Null Pointer. */
	u8_ID = 12;
	DIO_ErrorState = DIOProxy_AccessPin(NULL_PTR, PIN_0, &PinData);
	TestAssert(
		u8_ID, (ERROR_NOK == DIO_ErrorState)
	);

	/* Access invalid pin. */
	u8_ID = 13;
	DIO_ErrorState = DIOProxy_AccessPin(&PORTA_Proxy, PIN_INVALID, &PinData);
	TestAssert(
		u8_ID, (ERROR_NOK == DIO_ErrorState)
	);

	/* Access with null pointer in PinData. */
	u8_ID = 14;
	DIO_ErrorState = DIOProxy_AccessPin(&PORTA_Proxy, PIN_INVALID, NULL_PTR);
	TestAssert(
		u8_ID, (ERROR_NOK == DIO_ErrorState)
	);

	/* Access Output Pin. */
	u8_ID = 15;
	DIO_ErrorState = DIOProxy_AccessPin(&PORTA_Proxy, PIN_0, &PinData);
	TestAssert(
		u8_ID, (ERROR_OK == DIO_ErrorState) && (PinData == 0)
	);

	/* Set High in Input Pin 1 */
	PORTA_Registers |= 0x02;

	/* Access Input Pin */
	u8_ID = 16;
	DIO_ErrorState = DIOProxy_AccessPin(&PORTA_Proxy, PIN_1, &PinData);
	TestAssert(
		u8_ID, (ERROR_OK == DIO_ErrorState) && (PinData == 1)
	);
}

/**
* @brief: This function tests Mutating Pins.
*/
void TestMutate(void)
{
	/* Mutate With Struct Pointinig to Null Pointer. */
	u8_ID = 17;
	DIO_ErrorState = DIOProxy_MutatePin(NULL_PTR, PIN_0, PIN_HIGH);
	TestAssert(
		u8_ID, (ERROR_NOK == DIO_ErrorState)
	);

	/* Mutate invalid pin. */
	u8_ID = 18;
	DIO_ErrorState = DIOProxy_MutatePin(&PORTA_Proxy, PIN_INVALID, PIN_HIGH);
	TestAssert(
		u8_ID, (ERROR_NOK == DIO_ErrorState)
	);

	/* Mutate input pin. */
	u8_ID = 19;
	DIO_ErrorState = DIOProxy_MutatePin(&PORTA_Proxy, PIN_1, PIN_HIGH);
	TestAssert(
		u8_ID, (ERROR_NOK == DIO_ErrorState) && (PORTA_Registers == 0x040102)
	);

	/* Mutate Output pin. */
	u8_ID = 20;
	DIO_ErrorState = DIOProxy_MutatePin(&PORTA_Proxy, PIN_0, PIN_HIGH);
	TestAssert(
		u8_ID, (ERROR_OK == DIO_ErrorState) && (PORTA_Registers == 0x050102)
	);
}

/**
* @brief: This function tests Disabling Proxy.
*/
static void TestDisable(void)
{
	/* Diable Null Pointer */
	u8_ID = 21;
	DIO_ErrorState = DIOProxy_Disable(NULL_PTR);
	TestAssert(
		u8_ID, (ERROR_NOK == DIO_ErrorState)
	);

	/* Disable Proxy. */
	u8_ID = 22;
	DIO_ErrorState = DIOProxy_Disable(&PORTA_Proxy);
	TestAssert(
		u8_ID, (ERROR_OK == DIO_ErrorState) && (PORTA_Proxy.u8_Addr == NULL_PTR)
	);
}

/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function runs all test cases.
*/
void main(void)
{
	TestBeforeInit();

	TestInit();

	TestConfigure();

	TestAccess();

	TestMutate();

	TestDisable();

	printf("%u/%u TestCases passed.\n", u8_PassedCounter, NUMBER_OF_TESTCASES);

	printf("Press Enter key to close this window . . . \n");

	getchar();
}