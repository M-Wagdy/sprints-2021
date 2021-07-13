/*
 * LED.c
 *
 * Created: 7/7/2021 1:50:26 PM
 *  Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "LED.h"

/*- LOCAL MACROS
------------------------------------------*/
#define HIGH               (uint8_t)(1)
#define LOW                (uint8_t)(0)

/*- APIs IMPLEMENTATION
-----------------------------------*/

/**
* @brief: This function toggles the led
*/
LED_ERROR_state_t LED_Off(uint8_t LED_ch)
{
   uint8_t u8_ChPort;
   uint8_t u8_ChPin;
   
   switch(LED_ch)
   {
      case LED_CH_1:
         u8_ChPort = LED_CH_1_PORT;
         u8_ChPin = LED_CH_1_PIN;
         break;   
      case LED_CH_2:
         u8_ChPort = LED_CH_2_PORT;
         u8_ChPin = LED_CH_2_PIN;
         break;
      case LED_CH_3:
         u8_ChPort = LED_CH_3_PORT;
         u8_ChPin = LED_CH_3_PIN;
         break;
      default:
         return E_LED_INVALID_CH_NO;
   }
   
   DIO_ERROR_state_t DIOErrorState;
   
   DIOErrorState = DIO_write(u8_ChPort, u8_ChPin, LOW);
   
   if(E_DIO_SUCCESS != DIOErrorState)
   {
      return E_LED_DIO_ERROR;
   }
   
   return E_LED_SUCCESS;
}

LED_ERROR_state_t LED_On(uint8_t LED_ch)
{
   uint8_t u8_ChPort;
   uint8_t u8_ChPin;
   
   switch(LED_ch)
   {
      case LED_CH_1:
      u8_ChPort = LED_CH_1_PORT;
      u8_ChPin = LED_CH_1_PIN;
      break;
      case LED_CH_2:
      u8_ChPort = LED_CH_2_PORT;
      u8_ChPin = LED_CH_2_PIN;
      break;
      case LED_CH_3:
      u8_ChPort = LED_CH_3_PORT;
      u8_ChPin = LED_CH_3_PIN;
      break;
      default:
      return E_LED_INVALID_CH_NO;
   }
   
   DIO_ERROR_state_t DIOErrorState;
   
   DIOErrorState = DIO_write(u8_ChPort, u8_ChPin, HIGH);
   
   if(E_DIO_SUCCESS != DIOErrorState)
   {
      return E_LED_DIO_ERROR;
   }
   
   return E_LED_SUCCESS;
}

LED_ERROR_state_t LED_toggle(uint8_t LED_ch)
{
   uint8_t u8_ChPort;
   uint8_t u8_ChPin;
   
   switch(LED_ch)
   {
      case LED_CH_1:
      u8_ChPort = LED_CH_1_PORT;
      u8_ChPin = LED_CH_1_PIN;
      break;
      case LED_CH_2:
      u8_ChPort = LED_CH_2_PORT;
      u8_ChPin = LED_CH_2_PIN;
      break;
      case LED_CH_3:
      u8_ChPort = LED_CH_3_PORT;
      u8_ChPin = LED_CH_3_PIN;
      break;
      default:
      return E_LED_INVALID_CH_NO;
   }
   
   DIO_ERROR_state_t DIOErrorState;
   
   DIOErrorState = DIO_toggle(u8_ChPort, u8_ChPin);
   
   if(E_DIO_SUCCESS != DIOErrorState)
   {
      return E_LED_DIO_ERROR;
   }
   
   return E_LED_SUCCESS;
}