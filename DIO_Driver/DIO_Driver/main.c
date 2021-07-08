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

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
/* variable containing all DIO pins configurations */
extern const STR_DIO_config_t gastr_DIO_configurations;

int main(void)
{
   /* Initialization */
   
   /* variable to get error status of the DIO API. */
   DIO_ERROR_state_t DIO_init_state;
   /* initialize DIO pin. */
   DIO_init_state = DIO_init(&gastr_DIO_configurations);
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

