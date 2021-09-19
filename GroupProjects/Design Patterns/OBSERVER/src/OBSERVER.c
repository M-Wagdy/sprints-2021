/*
 * Observer.c
 *
 * Created: 8/21/2021 02:43:40 PM
 *  Author: Ahmed Essam
 */
 /*INCLUDES-------------------------------*/
#include "OBSERVER.h"
#include "USONIC.h"
/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/
static ERROR_STATE_t OBSERVER_Init(void);
static void OBSERVER_Notify(void);
/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern Ptr_VoidFuncVoid_t gptrA_Client[NUMBER_OF_CLIENTS];
/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/*THIS FNCTION INIT THE MODULE*/
static ERROR_STATE_t OBSERVER_Init(void)
{
	uint8_t u8_ErrorState=ERROR_NOK;
	u8_ErrorState = USONIC_Init();
	return u8_ErrorState;
}
/*THIS FUNCTION NOTIFY ALL SUBSCRIBERS*/
static void OBSERVER_Notify(void)
{
	uint8_t u8_NotifyIterator =ZERO;
	/*KEEP CALL THE FUNCTIONS UNTIL YOU FIND NULL*/
	while(NULL_PTR!=gptrA_Client[u8_NotifyIterator]){
		gptrA_Client[u8_NotifyIterator]();
		u8_NotifyIterator++;
		if(u8_NumberOfClientIterator>=NUMBER_OF_CLIENTS)
		{
			break;
		}
		else
		{
			/*DO NOTHING*/
		}
	}
}
/*- APIs IMPLEMENTATION
-----------------------------------*/
void OBSERVER_MainFunction(void)
{
	double64_t d64_Distance;
	uint8_t u8_UsonicState;
	static ERROR_STATE_t u8_InitFlag=NOT_INIT;
	if(NOT_INIT==u8_InitFlag)
	{
		if(ERROR_OK==OBSERVER_Init())
		{
			u8_InitFlag=INIT;
		}
		else
		{
			/*DO NOTHING*/
		}
	}
	if(INIT==u8_InitFlag)
	{
		u8_UsonicState = USONIC_GetDistance(&d64_Distance);
		if(ERROR_OK==u8_UsonicState)
		{
			OBSERVER_Set(d64_Distance);
			OBSERVER_Notify();
		}	
		else
		{
			/*DO NOTHING*/
		}
	}
	else
	{
		/*DO NOTHING*/
	}	
}