/*
 * OBSERVER_Interface.c
 *
 * Created: 8/21/2021 02:43:40 PM
 *  Author: Ahmed Essam
 */
 /*INCLUDES-------------------------------*/
#include "OBSERVER_Interface.h"
/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static double64_t gd64_Distance = ZERO;
static u8_NumberOfClientIterator =ZERO;
/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
Ptr_VoidFuncVoid_t gptra_Client[NUMBER_OF_CLIENTS];
uint8_t gu8_NumberOfSubscriber=ZERO;

/*- APIs IMPLEMENTATION
 -----------------------------------*/
extern ERROR_STATE_t OBSERVER_Subscribe(Ptr_VoidFuncVoid_t ClientFunction)
{
	uint8_t u8_ErrorState = ERROR_OK;
	/*CHECK IF THE FUNCTION ADD NOT EQUAL NULL*/
	if(NULL_PTR==ClientFunction)
	{
		u8_ErrorState = ERROR_NOK;
	}
	else
	{
		/*CHECK IF THE NUMBER OF CLIENTS IS NOT FULL*/
		if(u8_NumberOfClientIterator>=NUMBER_OF_CLIENTS)
		{
			u8_ErrorState = ERROR_NOK;
		}
		else
		{
			/*STORE THE POINTER TO FUNCTION IN THE ARRAY*/
			gptrA_Client[u8_NumberOfClientIterator]=ClientFunction;
			u8_NumberOfClientIterator++;
			gu8_NumberOfSubscriber++;
			u8_ErrorState = ERROR_OK;
		}
	}
	/*RETURN THE STATE OF THE FUNCTION*/
	return u8_ErrorState;
}

extern ERROR_STATE_t OBSERVER_Unsubscribe(Ptr_VoidFuncVoid_t ClientFunction)
{
	uint8_t u8_ErrorState = ERROR_OK;
	uint8_t u8_SearchinGIterator = 0;
	/*CHECK IF THE POINTER = NULL*/
	if(NULL_PTR==ClientFunction)
	{
		u8_ErrorState = ERROR_NOK;
	}
	else
	{
		/*CHECK IF THE ARRAY IS EMPTY*/
		if(EMPTY==gu8_NumberOfSubscriber)
		{
			/*STORE NOT OK*/
			u8_ErrorState = ERROR_NOK;
		}
		else
		{
			/*GO THROUGH ALL THE ELEMENT IN THE ARRAY */
			for(u8_SearchinGIterator=0;u8_SearchinGIterator<gu8_NumberOfSubscriber;u8_SearchinGIterator++)
			{	/*CHECK IF THE */
				if(ClientFunction==gptrA_Client[u8_SearchinGIterator])
				{
					/*ٍSTORE LAST ELEMENT IN THE PLACE NEEDED TO REMOVE*/
					gptrA_Client[u8_SearchinGIterator]=gptrA_Client[gu8_NumberOfSubscriber-1];
					/*STORE NULL_PTR IN THE LAST PLACE*/
					gptrA_Client[gu8_NumberOfSubscriber-1]=NULL_PTR;
					/*DECREASE NUMBER OF SUBSCRIBER*/
					gu8_NumberOfSubscriber=gu8_NumberOfSubscriber-1;
					/*STORE OK*/
					u8_ErrorState = ERROR_OK;
					/*BREAK OF THE LOOP */
					break;
				}
				else
				{
					/*STORE NOT OK*/
					u8_ErrorState = ERROR_NOK;
				}
			}
		}
	}
	/*RETURN THE STATE OF THE FUNCTION*/
	return u8_ErrorState;
}

extern ERROR_STATE_t OBSERVER_Get(ptr_double64_t Distance)
{
	uint8_t u8_ErrorState = ERROR_OK;
	/*CHECK IF THE POINTER = NULL*/
	if(NULL_PTR==Distance)
	{
		/*STORE NOT OK*/
		u8_ErrorState = ERROR_NOK;
	}
	else
	{
		/*STORE THE DISTANCE*/
		*Distance = gd64_Distance;
		/*STORE OK*/
		u8_ErrorState = ERROR_OK;
	}
	/*RETURN THE STATE OF THE FUNCTION*/
	return u8_ErrorState;
}
extern ERROR_STATE_t OBSERVER_Set(double64_t Distance)
{
	uint8_t u8_ErrorState=ERROR_OK;
	/*STORE THE DISTANCE*/
	gd64_Distance = Distance;
	/*RETURN THE STATE OF THE FUNCTION*/
	return u8_ErrorState;
}

