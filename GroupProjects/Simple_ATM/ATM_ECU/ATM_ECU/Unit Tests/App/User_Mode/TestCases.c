/*
 * USER_TestCases.c
 * Created: 08/06/2021
 *  Author: Essam
 */

 /*- INCLUDES
 ----------------------------------------------*/
#include <stdio.h>
#include"App/User/User.h"


 /*- LOCAL MACROS
 ------------------------------------------*/
#define TRUE                                 (uint8_t)(1)
#define FALSE                                (uint8_t)(0)
#define ZERO_ASCII                           (uint8_t)(0x30)
#define PAN_SIZE                             (uint8_t)10
#define BALANCE_SIZE                         (uint8_t)4
/*LOCAL MACROS BY AHMED ADEL*/
#define FAIL                                 (uint8_t)1
#define PASS                                 (uint8_t)0

 /*- LOCAL FUNCTIONS PROTOTYPES
 ----------------------------*/
static void ClearMemory(void);
extern uint8_t StringCmpr(ptr_uint8_t STRING_1, ptr_uint8_t STRING_2);
void GetCardDataTest(void);
void GetServerDataTest(void);
void USER_InterfaceTest (void);
void User_AuthenticateTest(void);
void User_CheckAmountTest(void);
void User_UpdateBalanceTest(void);
/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t* ptr_null;
static uint8_t u8_ID;
static uint8_t u8_PassedCounter = 0;
/*GLOBAL NONSTATIC VARIABLES BY ADEL*/
uint8_t USER_InterfaceTestResult = FAIL;
static uint8_t USER_InterfaceTestData [6][11]={{'1','2','3','1','1','1','1','1','1','1','1'},//pressed key values
                                               {EXIST,EXIST,EXIST,NOTEXIST,2,EXIST,EXIST,EXIST,EXIST,EXIST,EXIST},//PAN Existance values
                                               {CORRECT_PIN,CORRECT_PIN,CORRECT_PIN,CORRECT_PIN,CORRECT_PIN,WRONG_PIN,2,CORRECT_PIN,CORRECT_PIN,CORRECT_PIN,WRONG_PIN},//Authenication result values
                                               {APPROVED,APPROVED,APPROVED,APPROVED,APPROVED,APPROVED,APPROVED,EXCEED_MAX_AMOUNT,INSUFFICIENT_FUND,APPROVED,APPROVED},//check amount results
                                               {1,1,1,1,1,1,1,1,1,0,1},//card entry pin status
                                               {0,0,0,0,0,0,0,0,0,0,3}};//counter of wrong entries

uint8_t USER_InterfaceTestCaseCounter=0;
uint8_t Mock_PressedKey = 0;
uint8_t Mock_AuthenticationResult = 0;
uint8_t Mock_ExistanceofPAN = 0;
uint8_t Mock_CheckAmountResult = 0;
uint8_t Mock_CounterOfWrongEntries = 0;
uint8_t Mock_Card_Entry = 0;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern uint8_t gau8_Memory[255];//MOCKING EEPROM
extern uint8_t testing_key;//MOCKING KEYPAD

extern uint8_t Entered_PIN_Flag;//MOCKING KEYPAD
extern uint8_t Entered_Amount_Flag;//MOCKING KEYPAD

extern uint8_t au8_Entered_PIN_Test[5];//MOCKING KEYPAD
extern uint8_t u8_Entered_PIN_Index;//MOCKING KEYPAD

extern uint8_t au8_Entered_Amount_Test[8];//MOCKING KEYPAD
extern uint8_t u8_Entered_Amount_Index;//MOCKING KEYPAD

extern uint8_t Push_Button_Status;
extern ST_cardData_t ST_CurrrentCardDATA;//CARD DATA STRUCTURE
extern uint8_t Mocking_data;
extern uint8_t CARD_PAN[10];
extern uint8_t CARD_PIN[5];
f32_t gf32_balance =1000.5;
extern f32_t f32_EnteredAmount;
/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/**
* @brief: This function Initialize EEPROM Memory with 0xFF (Not initialized bits).
*/
void ClearMemory(void)
{
    uint8_t u8_Counter;
    for (u8_Counter = 0; u8_Counter < 255; u8_Counter++)
        {
            gau8_Memory[u8_Counter] = 0xFF;
    }
}

/**
* @brief: This function clears card data.
*/
void ClearCardData(void)
{
}



/**
* @brief: This function Checks EEPROM is Filled With User Data.
*/






/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function runs all test cases.
*/
int main(void)
{
    printf("Start of Execution of Test Cases of USER_InterfaceTest()\n");
    USER_InterfaceTest();
    printf("End of Execution of Test Cases of USER_InterfaceTest() press any key\n");
    getchar();
    printf("Start of Execution of Test Cases of GetCardDataTest()\n");
    GetCardDataTest();
    printf("End of Execution of Test Cases of GetCardDataTest() press any key\n");
    getchar();
    printf("Start of Execution of Test Cases of GetServerDataTest()\n");
    GetServerDataTest();
    printf("End of Execution of Test Cases of GetServerDataTest() press any key\n");
    getchar();
    printf("Start of Execution of Test Cases of User_AuthenticateTest()\n");
    User_AuthenticateTest();
    printf("End of Execution of Test Cases of User_AuthenticateTest() press any key\n");
    getchar();
    printf("Start of Execution of Test Cases of User_CheckAmountTest()\n");
    User_CheckAmountTest();
    printf("End of Execution of Test Cases of User_CheckAmountTest() press any key\n");
    getchar();
    printf("Start of Execution of Test Cases of User_UpdateBalanceTest()\n");
    User_UpdateBalanceTest();
    printf("End of Execution of Test Cases of User_UpdateBalanceTest() press any key\n");
    getchar();
    return 0;
}
/*
* @brief This function test USER_GetCardData functionality which is store data in structure
*/
void GetCardDataTest(void){
    USER_GetCardData();
    uint8_t i=0;
    uint8_t PANIsEqual=TRUE;
    uint8_t PINIsEqual=TRUE;
    PANIsEqual=StringCmpr(CARD_PAN,(ST_CurrrentCardDATA.primaryAccountNumber));
    PINIsEqual=StringCmpr(CARD_PIN,(ST_CurrrentCardDATA.pin));
    if((PANIsEqual==TRUE)&&(PINIsEqual==TRUE))
    {
        printf("TEST 1 PASSED\n");
    }
    else{

        printf("TEST 1 FAILED\n");
    }
}
/*
* @brief This function test GetServerData functionality which search in the server if PAN exist and if yes update balance
*/
void GetServerDataTest (void){
    Mocking_data='N';//THIS MEANS MEMORY EMPTY
    if(NOTEXIST==USER_GetServerData()){
        printf("TEST 2 PASSED\n");
    }
    else{
        printf("TEST 2 FAILED\n");
    }

    Mocking_data=5;//THIS MEANS  ACCOUNTS BUT NO MATCH
    ClearMemory();
    if(NOTEXIST==USER_GetServerData()){
        printf("TEST 3 PASSED\n");
    }
    else{
        printf("TEST 3 FAILED\n");
    }
    EEPROM_WriteBytes(EEPROM_CH_0, MEMORY_BLOCK_4,14,CARD_PAN,PAN_SIZE);
    EEPROM_WriteBytes(EEPROM_CH_0, MEMORY_BLOCK_4,24,(uint8_t*)&(gf32_balance),BALANCE_SIZE);
    if(EXIST==USER_GetServerData()){
        printf("TEST 4 PASSED\n");
    }
    else{
        printf("TEST 4 FAILED\n");
    }
    if(gf32_balance==ST_CurrrentCardDATA.balance){
        printf("TEST 5 PASSED\n");
    }
    else{
        printf("TEST 5 FAILED\n");
    }
    if(14==ST_CurrrentCardDATA.index){
        printf("TEST 6 PASSED\n");
    }
    else{
        printf("TEST 6 FAILED\n");

    }
}
void USER_InterfaceTest (void){
    uint8_t iterator=0;
    for(;iterator<11;iterator++)
    {
        USER_InterfaceTestCaseCounter++;

        Mock_PressedKey = USER_InterfaceTestData[0][iterator];
        Mock_ExistanceofPAN = USER_InterfaceTestData[1][iterator];
        Mock_AuthenticationResult = USER_InterfaceTestData[2][iterator];
        Mock_CheckAmountResult = USER_InterfaceTestData[3][iterator];
        Mock_Card_Entry = USER_InterfaceTestData[4][iterator];
        Mock_CounterOfWrongEntries = USER_InterfaceTestData[5][iterator];

        USER_Interface();
        printf("\n\nTEST Case:%d\n",USER_InterfaceTestCaseCounter);
        printf("Key-Pad Pressed Key: %c\n",Mock_PressedKey);

        if(Mock_ExistanceofPAN==EXIST)
            printf("State Of PAN on Server is: exist\n");
        else
            printf("State Of PAN on Server is: exist\n");

        if(Mock_AuthenticationResult==CORRECT_PIN)
            printf("State Of Entered PIN is: Entered Correctly\n");
        else
            if(Mock_CounterOfWrongEntries<3)
                printf("State Of Entered PIN is: Entered InCorrectly\n");
            else
                printf("State Of Entered PIN is: Entered 3 times InCorrectly\n");

        if(Mock_CheckAmountResult==APPROVED)
            printf("Transaction Amount is: APPROVED\n");
        else if(Mock_CheckAmountResult==EXCEED_MAX_AMOUNT)
            printf("Transaction Amount is: Exceeds the max. amount\n");
        else if (Mock_CheckAmountResult==INSUFFICIENT_FUND)
            printf("Transaction Amount is: Exceeds your funds\n");
        else
            printf("Transaction Amount is: incorrect State\n");

        if(Mock_Card_Entry==1)
            printf("State of the Pulled-Down Pin is: card Entered\n");
        else
            printf("State of the Pulled-Down Pin is: card isn't Entered\n");
        if(USER_InterfaceTestResult==PASS)
        {
            printf("The LCD Displays: ");
            switch(USER_InterfaceTestCaseCounter)
            {
            case 1:
                printf("APPROVED\n");
                break;
            case 2:
                printf("The Current Temperature\n");
                break;
            case 3:
                printf("Nothing\n");
                break;
            case 4:
                printf("Card Declined Press Any Key To Continue\n");
                break;
            case 5:
                printf("Nothing and the function return Operation Fails\n");
                break;
            case 6:
                printf("Wrong PIN\n");
                break;
            case 7:
                printf("Nothing and the function return Operation Fails\n");
                break;
            case 8:
                printf("MAX Val Exceeded\n");
                break;
            case 9:
                printf("Not enough Fund\n");
                break;
            case 10:
                printf("Card Removed\n");
                break;
            case 11:
                printf("3 Wrong PINs Press Any Key to continue\n");
                break;
            default:
                break;
            }
            printf("TEST CASE %d STATE : PASSED\n",USER_InterfaceTestCaseCounter);
            USER_InterfaceTestResult=FAIL;
        }
        else
        {
            printf("TEST CASE %d STATE : FAILED\n",USER_InterfaceTestCaseCounter);
        }
    }
}
void User_AuthenticateTest(void)
{
	uint8_t PINState;

    USER_GetCardData();
	Entered_PIN_Flag=1;

	for(uint8_t i=0;i<PIN_LENGTH;i++)
	{
		if(i==4)
		{
			au8_Entered_PIN_Test[i]='\0';
			break;
		}
		au8_Entered_PIN_Test[i]=i+48;
	}

	User_Authenticate(&PINState);
	u8_Entered_PIN_Index=0;

    if(CORRECT_PIN==PINState)
	{
        printf("TEST 7 PASSED\n");
    }
    else
	{
        printf("TEST 7 FAILED\n");
    }

	for(uint8_t i=0;i<PIN_LENGTH;i++)
	{
		if(i==4)
		{
			au8_Entered_PIN_Test[i]='\0';
			break;
		}
		au8_Entered_PIN_Test[i]=i+49;
	}

	User_Authenticate(&PINState);
	u8_Entered_PIN_Index=0;

    if(WRONG_PIN==PINState)
	{
        printf("TEST 8 PASSED\n");
    }
    else
	{
        printf("TEST 8 FAILED\n");
    }
	Entered_PIN_Flag=0;
}

void User_CheckAmountTest(void)
{
	uint8_t AmountState;
	f32_t f32_t_MaxAmount;
	Entered_Amount_Flag=1;

	for(uint8_t i=0;i<AMOUNT_LENGTH;i++)
	{
		if(i==4)
		{
			au8_Entered_Amount_Test[i]='5';
			continue;
		}
		if(i==7)
		{
			au8_Entered_Amount_Test[i]='\0';
			break;
		}

		au8_Entered_Amount_Test[i]=i+48;
	}
	u8_Entered_Amount_Index=0;
	User_CheckAmount(&AmountState);


    if(ERROR_FORMAT==AmountState)
	{
        printf("TEST 9 PASSED\n");
    }
    else
	{
        printf("TEST 9 FAILED\n");
    }

	for(uint8_t i=0;i<AMOUNT_LENGTH;i++)
	{
		if(i==3)
		{
			au8_Entered_Amount_Test[i]='*';
			continue;
		}
		if(i==7)
		{
			au8_Entered_Amount_Test[i]='\0';
			break;
		}

		au8_Entered_Amount_Test[i]=i+48;
	}
	u8_Entered_Amount_Index=0;
	User_CheckAmount(&AmountState);


    if(ERROR_FORMAT==AmountState)
	{
        printf("TEST 10 PASSED\n");
    }
    else
	{
        printf("TEST 10 FAILED\n");
    }

	for(uint8_t i=0;i<AMOUNT_LENGTH;i++)
	{
		if(i==6)
		{
			au8_Entered_Amount_Test[i]='#';
			continue;
		}
		if(i==7)
		{
			au8_Entered_Amount_Test[i]='\0';
			break;
		}

		au8_Entered_Amount_Test[i]=i+48;
	}
	u8_Entered_Amount_Index=0;
	User_CheckAmount(&AmountState);


    if(ERROR_FORMAT==AmountState)
	{
        printf("TEST 11 PASSED\n");
    }
    else
	{
        printf("TEST 11 FAILED\n");
    }

	for(uint8_t i=0;i<AMOUNT_LENGTH;i++)
	{
		if(i==4)
		{
			au8_Entered_Amount_Test[i]='*';
			continue;
		}
		if(i==7)
		{
			au8_Entered_Amount_Test[i]='\0';
			break;
		}

		au8_Entered_Amount_Test[i]=i+49;
	}
	u8_Entered_Amount_Index=0;
	f32_t_MaxAmount=1100.55;
	EEPROM_WriteBytes(EEPROM_CH_0, MEMORY_BLOCK_2,0x0,(ptr_uint8_t)&f32_t_MaxAmount,sizeof(f32_t));
	ST_CurrrentCardDATA.balance=1000.66;
	User_CheckAmount(&AmountState);

    if(EXCEED_MAX_AMOUNT==AmountState)
	{
        printf("TEST 12 PASSED\n");
    }
    else
	{
        printf("TEST 12 FAILED\n");
    }

	for(uint8_t i=0;i<AMOUNT_LENGTH;i++)
	{
		if(i==4)
		{
			au8_Entered_Amount_Test[i]='*';
			continue;
		}
		if(i==7)
		{
			au8_Entered_Amount_Test[i]='\0';
			break;
		}

		au8_Entered_Amount_Test[i]=i+49;
	}
	u8_Entered_Amount_Index=0;
	f32_t_MaxAmount=1500.55;
	EEPROM_WriteBytes(EEPROM_CH_0, MEMORY_BLOCK_2,0x0,(ptr_uint8_t)&f32_t_MaxAmount,sizeof(f32_t));
	ST_CurrrentCardDATA.balance=1000.66;
	User_CheckAmount(&AmountState);

    if(INSUFFICIENT_FUND==AmountState)
	{
        printf("TEST 13 PASSED\n");
    }
    else
	{
        printf("TEST 13 FAILED\n");
    }

	for(uint8_t i=0;i<AMOUNT_LENGTH;i++)
	{
		if(i==4)
		{
			au8_Entered_Amount_Test[i]='*';
			continue;
		}
		if(i==7)
		{
			au8_Entered_Amount_Test[i]='\0';
			break;
		}

		au8_Entered_Amount_Test[i]=i+49;
	}
	u8_Entered_Amount_Index=0;
	f32_t_MaxAmount=1500.55;
	EEPROM_WriteBytes(EEPROM_CH_0, MEMORY_BLOCK_2,0x0,(ptr_uint8_t)&f32_t_MaxAmount,sizeof(f32_t));
	ST_CurrrentCardDATA.balance=1400.66;
	User_CheckAmount(&AmountState);

    if(APPROVED==AmountState)
	{
        printf("TEST 14 PASSED\n");
    }
    else
	{
        printf("TEST 14 FAILED\n");
    }
	Entered_Amount_Flag=0;
}

void User_UpdateBalanceTest(void)
{
	ST_CurrrentCardDATA.balance=1000.66;
	f32_EnteredAmount=100;
	f32_t Expected_Output=ST_CurrrentCardDATA.balance-f32_EnteredAmount;
	User_UpdateBalance();

    if(ST_CurrrentCardDATA.balance==Expected_Output)
	{
        printf("TEST 15 PASSED\n");
    }
    else
	{
        printf("TEST 15 FAILED\n");
    }
}
