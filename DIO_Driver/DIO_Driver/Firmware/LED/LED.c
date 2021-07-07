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
#define LED_PORT PORTA
#define LED_PIN (uint8_t)0

/*- APIs IMPLEMENTATION
-----------------------------------*/

/**
* @brief: This function toggles the led
*/
void LED_toggle(void)
{
   DIO_ERROR_state_t e_status;
   e_status = DIO_toggle(LED_PORT,LED_PIN);
   if(E_DIO_SUCCESS != e_status)
   {
      while(1)
      {
         /* stuck in case of error */
      }
   }
}