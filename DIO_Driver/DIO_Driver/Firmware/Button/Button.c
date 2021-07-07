/*
 * Button.c
 *
 * Created: 7/7/2021 1:50:41 PM
 *  Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "Button.h"

/*- LOCAL MACROS
------------------------------------------*/
#define BTN_PORT PORTC
#define BTN_PIN (uint8_t)0

/*- APIs IMPLEMENTATION
-----------------------------------*/

/**
* @brief: This function gets the button state
*
* @return button state.
*/
uint8_t BUTTON_get_state(void)
{
   uint8_t data;
   DIO_ERROR_state_t e_status;
   e_status = DIO_read(BTN_PORT, BTN_PIN, &data);
         
   if(E_DIO_SUCCESS == e_status)
   {
      return data;
   }
   else
   {
      while(1)
      {
         /* stuck in case of error */
      }
   }
}