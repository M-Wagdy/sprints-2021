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
#define BTN_PIN (uint8_t)(0)

/*- APIs IMPLEMENTATION
-----------------------------------*/

/**
* @brief: This function gets the button state
*
* @return button state.
*/
uint8_t BUTTON_get_state(void)
{
   /* data variable to get pin reading in it. */
   uint8_t data;
   
   /* variable to get error status of the DIO API. */
   DIO_ERROR_state_t e_status;
   
   /* read DIO pin. */
   e_status = DIO_ReadPin(BTN_PORT, BTN_PIN, &data);
   
   /* return data if DIO API returns success. */
   if(E_DIO_SUCCESS == e_status)
   {
      return data;
   }
   /* if DIO returned error make the program stuck in super loop for debugging. */
   else
   {
      while(1)
      {
         /* do nothing */
      }
   }
}