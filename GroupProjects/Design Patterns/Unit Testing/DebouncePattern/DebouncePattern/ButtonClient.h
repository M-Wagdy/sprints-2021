/*
 * ButtonClient.h
 *
 * Created: 8/19/2021 1:50:18 PM
 *  Author: Mohamed Wagdy
 */ 

#ifndef __BUTTON_CLIENT_H__
#define __BUTTON_CLIENT_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_types.h"
#include "STUB_TIMER.h"
#include "STUB_BUTTON.h"

/*- ENUMS --------------------------------------------------*/
/* Enum for Get Button State State Machine */
typedef enum
{
   ButtonClient_Ready = 0,
   ButtonClient_Delay = 1,
   ButtonClient_StateReady = 2,
} Enu_ButtonClientStateMachine;

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct STR_BTNClient_t{
   uint8_t u8_ButtonCh;
   uint8_t u8_ButtonState;
   uint8_t u8_OldButtonState;
   uint8_t u8_TimerCh;
   uint32_t u32_DebounceDelay;
   Enu_ButtonClientStateMachine ENU_ClientState;
   Ptr_VoidFuncVoid_t EventCallback;
} STR_BTNClient_t;

/*- FUNCTION DECLARATIONS ----------------------------------*/
ERROR_STATE_t BUTTONClient_Init(STR_BTNClient_t * const ClientData);
ERROR_STATE_t BUTTONClient_SetBtn(STR_BTNClient_t * const ClientData, uint8_t BTN_CH);
ERROR_STATE_t BUTTONClient_SetTimer(STR_BTNClient_t * const ClientData, uint8_t TIM_CH, uint32_t DelayMS);
ERROR_STATE_t BUTTONClient_SetEventCallback(STR_BTNClient_t * const ClientData, Ptr_VoidFuncVoid_t Callback);
ERROR_STATE_t BUTTONClient_EventReceive(STR_BTNClient_t * const ClientData);

#endif /* __BUTTON_CLIENT_H__ */