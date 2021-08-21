/*
 * Button.c
 *
 * Created: 7/7/2021 1:50:41 PM
 *  Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "Button.h"

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern const STR_BUTTON_config_t gastr_Button_Config[BUTTONS_NUMBER];

/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function gets the button state
*
* @param [in]  BUTTON_CH -  Button channel number.
*
* @return button state.
*/
ERROR_STATE_t Button_Init(uint8_t BUTTON_CH)
{
   ERROR_STATE_t BUTTON_ErrorState;
   if(BUTTON_CH >= BTN_INVALID_CH)
   {
      BUTTON_ErrorState = BTN_E_INVALID_CH_NUM;
   }
   else
   {
      uint8_t BTN_Port;
      uint8_t BTN_Pin;
      uint8_t BTN_PullUp;
      
      switch(BUTTON_CH)
      {
         case BTN_0:
            BTN_Port = gastr_Button_Config[BTN_0].u8_Port;
            BTN_Pin = gastr_Button_Config[BTN_0].u8_Pin;
            BTN_PullUp = gastr_Button_Config[BTN_0].u8_PullUp;
            break;
         default:
            BUTTON_ErrorState = BTN_E_INVALID_CH_NUM;
            break;
      }
      
      /* Init Button Pins */
      DIO_SetPinDirection(BTN_Port, BTN_Pin, INPUT);
      if(PULL_UP == BTN_PullUp)
      {
         DIO_EnablePinPullup(BTN_Port, BTN_Pin);
      }
      BUTTON_ErrorState = ERROR_OK;
   }
   
   /* return function Error State. */   
   return BUTTON_ErrorState;
}


/**
* @brief: This function gets the button state
*
* @param [in]  BUTTON_CH   -  Button channel number.
* @param [out] State       -  State of Button.
*
* @return button state.
*/
ERROR_STATE_t BUTTON_getState(uint8_t BUTTON_CH, uint8_t * State)
{
   ERROR_STATE_t BUTTON_ErrorState;
   if(BUTTON_CH >= BTN_INVALID_CH)
   {
      BUTTON_ErrorState = BTN_E_INVALID_CH_NUM;
   }
   else if(NULL_PTR == State)
   {
      BUTTON_ErrorState = BTN_E_NULL_PTR;
   }
   else
   {
      uint8_t BTN_Port;
      uint8_t BTN_Pin;
      uint8_t BTN_PullUp;
      
      switch(BUTTON_CH)
      {
         case BTN_0:
            BTN_Port = gastr_Button_Config[BTN_0].u8_Port;
            BTN_Pin = gastr_Button_Config[BTN_0].u8_Pin;
            BTN_PullUp = gastr_Button_Config[BTN_0].u8_PullUp;
            break;
         default:
            BUTTON_ErrorState = BTN_E_INVALID_CH_NUM;
            break;
      }
      
      /* variable to get error status of the DIO API. */
      DIO_ERROR_state_t e_status;
      
      /* read DIO pin. */
      e_status = DIO_ReadPin(BTN_Port, BTN_Pin, State);
      
      /* return data if DIO API returns success. */
      if(E_DIO_SUCCESS == e_status)
      {
         BUTTON_ErrorState = ERROR_OK;
      }
      else
      {
         BUTTON_ErrorState = ERROR_NOK;
      }
   }   
   
   /* return function Error State. */
   return BUTTON_ErrorState;
}