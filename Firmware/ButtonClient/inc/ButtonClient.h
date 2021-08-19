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
#include "TIMER.h"
#include "Button.h"

/*- ENUMS --------------------------------------------------*/
/* Enum for Get Button State State Machine */
typedef enum
{
   ButtonClient_Ready = 0,
   ButtonClient_Delay = 1,
   ButtonClient_StateReady = 2,
} Enu_ButtonClientStateMachine;


/*- FUNCTION DECLARATIONS ----------------------------------*/
ERROR_STATE_t BUTTONClient_EventReceive(uint8_t * State);

#endif /* __BUTTON_CLIENT_H__ */