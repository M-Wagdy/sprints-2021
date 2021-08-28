 /* BCM_Interface.c
 *
 * Created: 8/24/2021
 *  Author: Ahmed Essam
 */
 /*-INCLUDES-------------------------------*/
 #include "BCM_Interface.h"
 /*- GLOBAL EXTERN VARIABLES-------------------------------*/
 extern uint8_t u8_BCM_ID;
/*- GLOBAL STATIC VARIABLES-------------------------------*/
static STR_BCMTask_t gastr_BCM_Task[COMM_NUMBERS]=
{
   {ZERO,BCM_MODE_IDEAL,ZERO, BCM_STATE_INVALID, ZERO, ZERO , ZERO , NULL_PTR , NULL_PTR},
   {ZERO,BCM_MODE_IDEAL,ZERO, BCM_STATE_INVALID, ZERO, ZERO , ZERO , NULL_PTR , NULL_PTR},
   {ZERO,BCM_MODE_IDEAL,ZERO, BCM_STATE_INVALID, ZERO, ZERO , ZERO , NULL_PTR , NULL_PTR},
};
/*- APIs IMPLEMENTATION-----------------------------------*/
/**
* @brief: This function sets the data to be sent.
*/
extern ERROR_STATE_t BCM_Send(uint8_t CH_ID, uint16_t Size,ptr_uint8_t DataArr,Ptr_VoidFuncVoid_t TX_CBF)
{
    ERROR_STATE_t u8_ErrorState =ERROR_OK;
    uint16_t u16_BCM_CSCounter=ZERO;
	if(CH_ID>=COMM_NUMBERS)
	{
		u8_ErrorState =ERROR_NOK;
	}
    else if(BCM_MODE_IDEAL!=gastr_BCM_Task[CH_ID].u8_BCMMode)
    {
        u8_ErrorState =ERROR_NOK;
    }
    else if((Size>BCM_MAX_DATA_SIZE)||(Size<BCM_MIN_DATA_SIZE))
	{
		u8_ErrorState =ERROR_NOK;
	}
    else if((NULL_PTR==DataArr)||(NULL_PTR==TX_CBF))
	{
		u8_ErrorState =ERROR_NOK;
	}
	else
	{
	    gastr_BCM_Task[CH_ID].u8_BCMID=u8_BCM_ID;
		gastr_BCM_Task[CH_ID].u8_BCMMode=BCM_MODE_TX;
		gastr_BCM_Task[CH_ID].u8_BCMCS=ZERO;
		gastr_BCM_Task[CH_ID].u8_BCMState=BCM_TXSTATE_SENDING;
		gastr_BCM_Task[CH_ID].u8_BCMPacketCounter=ZERO;
		gastr_BCM_Task[CH_ID].u16_BCMByteCoounter=ZERO;
		gastr_BCM_Task[CH_ID].u16_BCMSize=Size;
		gastr_BCM_Task[CH_ID].ptr_BCMBuffer=DataArr;
		gastr_BCM_Task[CH_ID].ptr_BCMCallBackFu=TX_CBF;
		for(u16_BCM_CSCounter=ZERO;u16_BCM_CSCounter<Size;u16_BCM_CSCounter++)
		{
			gastr_BCM_Task[CH_ID].u8_BCMCS+=DataArr[u16_BCM_CSCounter];
		}
	}
    return u8_ErrorState;
}
/**
* @brief: This function sets up the receiving buffer.
*/
extern ERROR_STATE_t BCM_Receive(uint8_t CH_ID,uint16_t Size,ptr_uint8_t DataArr,Ptr_VoidFuncVoid_t RX_CBF)
{
    ERROR_STATE_t u8_ErrorState =ERROR_OK;
	if(CH_ID>=COMM_NUMBERS)
	{
		u8_ErrorState =ERROR_NOK;
	}
	else if(BCM_MODE_IDEAL!=gastr_BCM_Task[CH_ID].u8_BCMMode)
    {
        u8_ErrorState =ERROR_NOK;
    }
	else if((Size>BCM_MAX_DATA_SIZE)||(Size<BCM_MIN_DATA_SIZE))
	{
		u8_ErrorState =ERROR_NOK;
	}
    else if((NULL_PTR==DataArr)||(NULL_PTR==RX_CBF))
    {
		 u8_ErrorState =ERROR_NOK;
	}
	else
	{
		gastr_BCM_Task[CH_ID].u8_BCMMode=BCM_MODE_RX;
		gastr_BCM_Task[CH_ID].u8_BCMCS=ZERO;
		gastr_BCM_Task[CH_ID].u8_BCMState=BCM_RXSTATE_RECEIVING;
		gastr_BCM_Task[CH_ID].u8_BCMPacketCounter=ZERO;
		gastr_BCM_Task[CH_ID].u16_BCMByteCoounter=ZERO;
		gastr_BCM_Task[CH_ID].u16_BCMSize=Size;
		gastr_BCM_Task[CH_ID].ptr_BCMBuffer=DataArr;
		gastr_BCM_Task[CH_ID].ptr_BCMCallBackFu=RX_CBF;

	}
    return u8_ErrorState;
}

/**
* @brief: This function gets the data.
*/
extern ERROR_STATE_t BCM_Get(uint8_t CH_ID,ptr_STR_BCMTask_t* Task)
{
    ERROR_STATE_t u8_ErrorState =ERROR_OK;
    if(NULL_PTR==Task)
    {
        u8_ErrorState =ERROR_NOK;
    }
    else if(CH_ID>=COMM_NUMBERS)
	{
		u8_ErrorState =ERROR_NOK;
	}
	else
	{
	   *Task=&gastr_BCM_Task[CH_ID];
	}
    return u8_ErrorState;
}
/**
* @brief: This function sets the state.
*/
extern ERROR_STATE_t BCM_SetState(uint8_t CH_ID,uint8_t CurrentState)
{
    ERROR_STATE_t u8_ErrorState =ERROR_OK;
    if(CH_ID>=COMM_NUMBERS)
    {
        u8_ErrorState =ERROR_NOK;
    }
    else if(CurrentState>=BCM_STATE_INVALID)
	{
		u8_ErrorState =ERROR_NOK;
	}
	else
	{
		gastr_BCM_Task[CH_ID].u8_BCMState=CurrentState;
	}
    return u8_ErrorState;
}
