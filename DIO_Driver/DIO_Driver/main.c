/*
 * DIO_Driver.c
 *
 * Created: 7/7/2021 1:48:33 PM
 * Author : ASUS
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "Firmware/Button/Button.h"
#include "Firmware/LED/LED.h"

/*- LOCAL MACROS
------------------------------------------*/
#define PRESSED (uint8_t)(1)
#define NOT_PRESSED (uint8_t)(0)

int main(void)
{
   /* Initialization */
   
   /* variable to get error status of the DIO API. */
   DIO_ERROR_state_t DIO_init_state;
   /* initialize DIO pin. */
   DIO_init_state = DIO_SetPinDirection(PORTA, PIN_0, OUTPUT);
   DIO_init_state |= DIO_SetPinDirection(PORTC, PIN_0, INPUT);
   
   /* if DIO init returned error make the program stuck in super loop for debugging. */
   if(E_DIO_SUCCESS != DIO_init_state)
   {
      while(1)
      {
         /* do nothing */
      }
   }
   
   /* main loop. */
   while(1)
   {
      /* check if button is pressed */
      if(PRESSED == BUTTON_get_state())
      {
         /* toggle LED. */
         LED_toggle();
         /* loop in empty loop until button is unpressed */
         while(PRESSED == BUTTON_get_state()){}
      }
   }
}

