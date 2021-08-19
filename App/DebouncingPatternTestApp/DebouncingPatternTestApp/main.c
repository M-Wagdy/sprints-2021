/*
 * DebouncingPatternTestApp.c
 *
 * Created: 8/19/2021 3:53:12 PM
 * Author : asus
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "ButtonClient.h"

/*- LOCAL MACROS
------------------------------------------*/
/* Led Macros */
#define GREEN_LED_PORT     PORTA
#define GREEN_LED_PIN      PIN_0

/* Button Macros */
#define BTN_PORT           PORTC
#define BTN_PIN            PIN_0
#define PRESSED            (uint8_t)(0)

/*- APIs IMPLEMENTATION
-----------------------------------*/
int main(void)
{
   /* Init Button Pins */
   DIO_SetPinDirection(BTN_PORT, BTN_PIN, INPUT);
   DIO_EnablePinPullup(BTN_PORT, BTN_PIN);
   
   /* Init Led Pin */
   DIO_SetPinDirection(GREEN_LED_PORT, GREEN_LED_PIN, OUTPUT);
   
   /* Variables to be used in super loop. */
   uint8_t ButtonState;
   ERROR_STATE_t ErrorState;
   
   while (1) 
   {
      ErrorState = BUTTONClient_EventReceive(&ButtonState);
      {
         /* If Button Client Finished */
         if(ERROR_OK == ErrorState)
         {
            /* If Button is Pressed */
            if(PRESSED == ButtonState)
            {
               /* Toggle Pin */
               DIO_TogglePin(GREEN_LED_PORT, GREEN_LED_PIN);
            }
            else{/* Do Nothing */}
         }
         else{/* Do Nothing */}
      }
   }
}

