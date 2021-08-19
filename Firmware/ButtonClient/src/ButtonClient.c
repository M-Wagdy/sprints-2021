/*
 * ButtonClient.c
 *
 * Created: 8/19/2021 1:50:18 PM
 *  Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "ButtonClient.h"

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t gu8_OldState;

/*- APIs IMPLEMENTATION
-----------------------------------*/

/**
* @brief: This function gets Button State.
*
* @param [in]  State -  Button State.
*
* @return function error state.
*/
ERROR_STATE_t BUTTONClient_EventReceive(uint8_t * State)
{
   /* State Machine Variable */
   static Enu_ButtonClientStateMachine ENU_ClientState = ButtonClient_Ready;
   
   /* Used Function Return Error State */
   ERROR_STATE_t RetErrorState;
   
   /* Button Client Error State */
   ERROR_STATE_t ErrorState = ERROR_NOK;
   
   /* Variable to store button state in it. */
   uint8_t u8_state;
   
   /* State Machine */
   switch(ENU_ClientState)
   {
      /* Get First Button Reading State */
      case ButtonClient_Ready:
         RetErrorState = BUTTON_getState(&u8_state);
         if(ERROR_OK == RetErrorState)
         {
            /* Store State in Old State */
            gu8_OldState = u8_state;
            
            /* Go to debounce Delay State. */
            ENU_ClientState = ButtonClient_Delay;
         }
         else
         {
            /* Do Nothing */
         }
         break;
      /* Debounce Delay State */
      case ButtonClient_Delay:
         /* Call Delay Status. */
         RetErrorState = TIM_DelayStatus(TIMER_2, BUTTONClient_EventReceive);
         /* If Delay is not used by another API. */
         if(TIMER_E_DELAY_EMPTY == RetErrorState)
         {
            /* Start Delay with 20 Milliseconds. */
            TIM_DelayMs(TIMER_2, 20, BUTTONClient_EventReceive);
         }
         /* If Delay Finished */
         else if(ERROR_OK == RetErrorState)
         {
            /* Go To Get Second Button Reading State. */
            ENU_ClientState = ButtonClient_StateReady;
         }
         else
         {
            /* Do Nothing */
         }
         break;
      /* Get Second Button Reading State. */
      case ButtonClient_StateReady:
         ErrorState = BUTTON_getState(&u8_state);
         if(ERROR_OK == RetErrorState)
         {
            /* Compare the button old state with the new state. */
            if(gu8_OldState == u8_state)
            {
               /* Return the button value. */
               *State = u8_state;
               ErrorState = ERROR_OK;
            }
            else
            {
               ErrorState = ERROR_NOK;
            }
            
         }
         else
         {
            /* Do Nothing */
         }
         /* Go To New Button Reading State. */
         ENU_ClientState = ButtonClient_Ready;
         break;
      default:
         break;
   }
   
   /* Return Function Error State. */
   return ErrorState;
}