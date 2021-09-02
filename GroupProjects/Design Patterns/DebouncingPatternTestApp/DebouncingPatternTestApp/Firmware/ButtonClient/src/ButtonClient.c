/*
 * ButtonClient.c
 *
 * Created: 8/19/2021 1:50:18 PM
 *  Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "ButtonClient.h"

/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function Initialize Client Struct.
*
* @param [in]  ClientData  -  Struct containing Client Data.
*
* @return function error state.
*/
ERROR_STATE_t BUTTONClient_Init(STR_BTNClient_t * const ClientData)
{
   ERROR_STATE_t Client_ErrorState;

   if (NULL_PTR != ClientData)
   {
      ClientData->u8_ButtonCh = BTN_INVALID_CH;
      ClientData->u8_ButtonState = 0;
      ClientData->u8_OldButtonState = 0;
      ClientData->u8_TimerCh = INVALID_TIMER_CH;
      ClientData->u32_DebounceDelay = 0;
      ClientData->ENU_ClientState = ButtonClient_Ready;
      ClientData->EventCallback = NULL_PTR;

      Client_ErrorState = ERROR_OK;
   }
   else
   {
      Client_ErrorState = ERROR_NOK;
   }

   return Client_ErrorState;
}

/**
* @brief: This function Sets Button Device.
*
* @param [in]  ClientData  -  Struct containing Client Data.
* @param [in]  BTN_CH      -  Button Channel Number.
*
* @return function error state.
*/
ERROR_STATE_t BUTTONClient_SetBtn(STR_BTNClient_t * const ClientData, uint8_t BTN_CH)
{
   ERROR_STATE_t Client_ErrorState;
   
   if (NULL_PTR != ClientData)
   {
      if (BTN_CH >= BTN_INVALID_CH)
      {
         Client_ErrorState = ERROR_NOK;
      }
      else
      {
         ClientData->u8_ButtonCh = BTN_CH;
         Client_ErrorState = ERROR_OK;
      }
   }
   else
   {
      Client_ErrorState = ERROR_NOK;
   }
   
   return Client_ErrorState;
}

/**
* @brief: This function Sets Debounce Delay for device.
*
* @param [in]  ClientData  -  Struct containing Client Data.
* @param [in]  TIM_CH      -  Timer Channel Number.
* @param [in]  DelayMS     -  Debounce Delay in milliseconds.
*
* @return function error state.
*/
ERROR_STATE_t BUTTONClient_SetTimer(STR_BTNClient_t * const ClientData, uint8_t TIM_CH, uint32_t DelayMS)
{
   ERROR_STATE_t Client_ErrorState;
   
   if (NULL_PTR != ClientData)
   {
      if (TIM_CH >= INVALID_TIMER_CH)
      {
         Client_ErrorState = ERROR_NOK;
      }
      else
      {
         ClientData->u8_TimerCh = TIM_CH;
         ClientData->u32_DebounceDelay = DelayMS;
         Client_ErrorState = ERROR_OK;
      }
   }
   else
   {
      Client_ErrorState = ERROR_NOK;
   }

   return Client_ErrorState;
}

/**
* @brief: This function Sets Callback Function.
*
* @param [in]  ClientData  -  Struct containing Client Data.
* @param [in]  Callback    -  Pointer to the Callback Function.
*
* @return function error state.
*/
ERROR_STATE_t BUTTONClient_SetEventCallback(STR_BTNClient_t * const ClientData, Ptr_VoidFuncVoid_t Callback)
{
   ERROR_STATE_t Client_ErrorState;
   
   if (NULL_PTR != ClientData)
   {
      if (NULL_PTR == Callback)
      {
         Client_ErrorState = ERROR_NOK;
      }
      else
      {
         ClientData->EventCallback = Callback;
         Client_ErrorState = ERROR_OK;
      }
   }
   else
   {
      Client_ErrorState = ERROR_NOK;
   }
   
   return Client_ErrorState;
}

/**
* @brief: This function gets Button State.
*
* @param [in]  ClientData -  Struct containing Client Data.
*
* @return function error state.
*/
ERROR_STATE_t BUTTONClient_EventReceive(STR_BTNClient_t * const ClientData)
{  
   /* Used Function Return Error State */
   ERROR_STATE_t RetErrorState;
   
   /* Button Client Error State */
   ERROR_STATE_t ErrorState = ERROR_NOK;
   
   if (NULL_PTR != ClientData)
   {
      /* State Machine */
      switch (ClientData->ENU_ClientState)
      {
         /* Get First Button Reading State */
         case ButtonClient_Ready:
            RetErrorState = BUTTON_getState(ClientData->u8_ButtonCh, &ClientData->u8_OldButtonState);
            if (ERROR_OK == RetErrorState)
            {
               /* Go to debounce Delay State. */
               ClientData->ENU_ClientState = ButtonClient_Delay;
            }
            else
            {
               /* Do Nothing */
            }
            break;
            /* Debounce Delay State */
         case ButtonClient_Delay:
            /* Call Delay Status. */
            RetErrorState = TIM_DelayStatus(ClientData->u8_TimerCh, BUTTONClient_EventReceive);
            /* If Delay is not used by another API. */
            if (TIMER_E_DELAY_EMPTY == RetErrorState)
            {
               /* Start Delay with 20 Milliseconds. */
               TIM_DelayMs(ClientData->u8_TimerCh, ClientData->u32_DebounceDelay, BUTTONClient_EventReceive);
            }
            /* If Delay Finished */
            else if (ERROR_OK == RetErrorState)
            {
               /* Go To Get Second Button Reading State. */
               ClientData->ENU_ClientState = ButtonClient_StateReady;
            }
            else
            {
               /* Do Nothing */
            }
            break;
            /* Get Second Button Reading State. */
         case ButtonClient_StateReady:
            RetErrorState = BUTTON_getState(ClientData->u8_ButtonCh, &ClientData->u8_ButtonState);
            if (ERROR_OK == RetErrorState)
            {
               /* Compare the button old state with the new state. */
               if (ClientData->u8_OldButtonState == ClientData->u8_ButtonState)
               {
                  /* Make Sure Callback is not pointing to null. */
                  if (NULL_PTR != ClientData->EventCallback)
                  {
                     /* Call The callback function. */
                     ClientData->EventCallback();
                  }
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
            ClientData->ENU_ClientState = ButtonClient_Ready;
            break;
         default:
            break;
      }
   }
   else
   {
      ErrorState = ERROR_NOK;
   }

   /* Return Function Error State. */
   return ErrorState;
}