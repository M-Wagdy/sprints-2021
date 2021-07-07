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
#define PRESSED (uint8_t)1
#define NOT_PRESSED (uint8_t)0

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern const STR_DIO_config_t gastr_DIO_configurations;

int main(void)
{
   DIO_ERROR_state_t DIO_init_state;
   DIO_init_state = DIO_init(&gastr_DIO_configurations);
   if(E_DIO_SUCCESS != DIO_init_state)
   {
      LED_toggle();
   }
   while(1)
   {
      if(PRESSED == BUTTON_get_state())
      {
         LED_toggle();
         while(PRESSED == BUTTON_get_state()){}
      }
   }
}

