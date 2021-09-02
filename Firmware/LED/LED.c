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

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t gu8_IsLEDInit = NOT_INIT;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
#ifdef LED_CH_1
extern const uint8_t LED_CH_1_PORT;
extern const uint8_t LED_CH_1_PIN;
#endif
#ifdef LED_CH_2
extern const uint8_t LED_CH_2_PORT;
extern const uint8_t LED_CH_2_PIN;
#endif
#ifdef LED_CH_3
extern const uint8_t LED_CH_3_PORT;
extern const uint8_t LED_CH_3_PIN;
#endif

/*- APIs IMPLEMENTATION
-----------------------------------*/

/**
* @brief: This function initialize LEDs.
*
* @return function error state.
*/
LED_ERROR_state_t LED_Init(void)
{
   /* check if init function was called before */
   if(INIT == gu8_IsLEDInit)
   {
      return E_LED_INIT_BEFORE;
   }
   
   DIO_ERROR_state_t e_state;
   
   #ifdef LED_CH_1
      /* configure LED pin */
      e_state = DIO_SetPinDirection(LED_CH_1_PORT, LED_CH_1_PIN, OUTPUT);
      /* make sure pin configuration is successful */
      if(E_DIO_SUCCESS != e_state)
      {
         return E_LED_DIO_ERROR;
      }
   #endif
   #ifdef LED_CH_2
      /* configure LED pin */
      e_state = DIO_SetPinDirection(LED_CH_2_PORT, LED_CH_2_PIN, OUTPUT);
      /* make sure pin configuration is successful */
      if(E_DIO_SUCCESS != e_state)
      {
         return E_LED_DIO_ERROR;
      }
   #endif
   #ifdef LED_CH_3
      /* configure LED pin */
      e_state = DIO_SetPinDirection(LED_CH_3_PORT, LED_CH_3_PIN, OUTPUT);
      /* make sure pin configuration is successful */
      if(E_DIO_SUCCESS != e_state)
      {
         return E_LED_DIO_ERROR;
      }
   #endif
   
   /* set global variable to initialized */
   gu8_IsLEDInit = INIT;
   
   /* return success message */
   return E_LED_SUCCESS;
}

/**
* @brief: This function turns off a LED.
*
* @param [in]  LED_ch   -  LED channel number.
*
* @return function error state.
*/
LED_ERROR_state_t LED_Off(uint8_t LED_ch)
{
   /* check if init function wasn't called before */
   if(NOT_INIT == gu8_IsLEDInit)
   {
      return E_LED_NOT_INIT;
   }
   
   uint8_t u8_ChPort;
   uint8_t u8_ChPin;
   
   /* set the required port and pin to the LED */
   switch(LED_ch)
   {
      #ifdef LED_CH_1
      case LED_CH_1:
         u8_ChPort = LED_CH_1_PORT;
         u8_ChPin = LED_CH_1_PIN;
         break;   
      #endif
      #ifdef LED_CH_2
      case LED_CH_2:
         u8_ChPort = LED_CH_2_PORT;
         u8_ChPin = LED_CH_2_PIN;
         break;
      #endif
      #ifdef LED_CH_3
      case LED_CH_3:
         u8_ChPort = LED_CH_3_PORT;
         u8_ChPin = LED_CH_3_PIN;
         break;
      #endif
      default:
         return E_LED_INVALID_CH_NO;
   }
   
   DIO_ERROR_state_t DIOErrorState;
   
   /* set LED pin to low */
   DIOErrorState = DIO_WritePin(u8_ChPort, u8_ChPin, LOW);
   
   /* make sure DIO function was successful */
   if(E_DIO_SUCCESS != DIOErrorState)
   {
      return E_LED_DIO_ERROR;
   }
   
   /* return success message */
   return E_LED_SUCCESS;
}

/**
* @brief: This function turns on a LED.
*
* @param [in]  LED_ch   -  LED channel number.
*
* @return function error state.
*/
LED_ERROR_state_t LED_On(uint8_t LED_ch)
{
   /* check if init function wasn't called before */
   if(NOT_INIT == gu8_IsLEDInit)
   {
      return E_LED_NOT_INIT;
   }
   
   uint8_t u8_ChPort;
   uint8_t u8_ChPin;
   
   /* set the required port and pin to the LED */
   switch(LED_ch)
   {
      #ifdef LED_CH_1
      case LED_CH_1:
         u8_ChPort = LED_CH_1_PORT;
         u8_ChPin = LED_CH_1_PIN;
         break;
      #endif
      #ifdef LED_CH_2
      case LED_CH_2:
         u8_ChPort = LED_CH_2_PORT;
         u8_ChPin = LED_CH_2_PIN;
         break;
      #endif
      #ifdef LED_CH_3
      case LED_CH_3:
         u8_ChPort = LED_CH_3_PORT;
         u8_ChPin = LED_CH_3_PIN;
         break;
      #endif
      default:
         return E_LED_INVALID_CH_NO;
   }
   
   DIO_ERROR_state_t DIOErrorState;
   
   /* set LED pin to high */
   DIOErrorState = DIO_WritePin(u8_ChPort, u8_ChPin, HIGH);
   
   /* make sure DIO function was successful */
   if(E_DIO_SUCCESS != DIOErrorState)
   {
      return E_LED_DIO_ERROR;
   }
   
   /* return success message */
   return E_LED_SUCCESS;
}

/**
* @brief: This function toggles a LED.
*
* @param [in]  LED_ch   -  LED channel number.
*
* @return function error state.
*/
LED_ERROR_state_t LED_Toggle(uint8_t LED_ch)
{
   /* check if init function wasn't called before */
   if(NOT_INIT == gu8_IsLEDInit)
   {
      return E_LED_NOT_INIT;
   }
   
   uint8_t u8_ChPort;
   uint8_t u8_ChPin;
   
   /* set the required port and pin to the LED */
   switch(LED_ch)
   {
      #ifdef LED_CH_1
      case LED_CH_1:
         u8_ChPort = LED_CH_1_PORT;
         u8_ChPin = LED_CH_1_PIN;
         break;
      #endif
      #ifdef LED_CH_2
      case LED_CH_2:
         u8_ChPort = LED_CH_2_PORT;
         u8_ChPin = LED_CH_2_PIN;
         break;
      #endif
      #ifdef LED_CH_3
      case LED_CH_3:
         u8_ChPort = LED_CH_3_PORT;
         u8_ChPin = LED_CH_3_PIN;
         break;
      #endif
      default:
         return E_LED_INVALID_CH_NO;
   }
   
   DIO_ERROR_state_t DIOErrorState;
   
   /* toggle LED pin */
   DIOErrorState = DIO_TogglePin(u8_ChPort, u8_ChPin);
   
   /* make sure DIO function was successful */
   if(E_DIO_SUCCESS != DIOErrorState)
   {
      return E_LED_DIO_ERROR;
   }
   
   /* return success message */
   return E_LED_SUCCESS;
}

/**
* @brief: This function returns a led state.
*
* @param [in]  LED_ch   -  LED channel number.
* @param [out] state    -  pointer to where to save the LED state.
*
* @return function error state.
*/
LED_ERROR_state_t LED_Status(uint8_t LED_ch, uint8_t * state)
{
   /* check if init function wasn't called before */
   if(NOT_INIT == gu8_IsLEDInit)
   {
      return E_LED_NOT_INIT;
   }
   else if(NULL_PTR == state)
   {
      return E_LED_NULL_PTR;
   }
   
   uint8_t u8_ChPort;
   uint8_t u8_ChPin;
   
   /* set the required port and pin to the LED */
   switch(LED_ch)
   {
      #ifdef LED_CH_1
      case LED_CH_1:
         u8_ChPort = LED_CH_1_PORT;
         u8_ChPin = LED_CH_1_PIN;
         break;
      #endif
      #ifdef LED_CH_2
      case LED_CH_2:
         u8_ChPort = LED_CH_2_PORT;
         u8_ChPin = LED_CH_2_PIN;
         break;
      #endif
      #ifdef LED_CH_3
      case LED_CH_3:
         u8_ChPort = LED_CH_3_PORT;
         u8_ChPin = LED_CH_3_PIN;
         break;
      #endif
      default:
         return E_LED_INVALID_CH_NO;
   }
   
   DIO_ERROR_state_t DIOErrorState;
   
   /* get LED pin state */
   DIOErrorState = DIO_ReadPin(u8_ChPort, u8_ChPin, state);
   
   /* make sure DIO function was successful */
   if(E_DIO_SUCCESS != DIOErrorState)
   {
      return E_LED_DIO_ERROR;
   }
   
   /* return success message */
   return E_LED_SUCCESS;
   
}
