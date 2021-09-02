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
#define GREEN_LED_PORT     PORTB
#define GREEN_LED_PIN      PIN_4

/* Button Macros */
#define PRESSED            (uint8_t)(0)

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/
void GreenLedMain(void);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t OldButtonState;
static STR_BTNClient_t GreenLed_BTNClient;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
void GreenLedMain(void)
{
   /* If Button is Pressed */
   if(PRESSED == GreenLed_BTNClient.u8_ButtonState && OldButtonState != GreenLed_BTNClient.u8_ButtonState)
   {
      /* Toggle Pin */
      DIO_TogglePin(GREEN_LED_PORT, GREEN_LED_PIN);
   }
   else{/* Do Nothing */}
   OldButtonState = GreenLed_BTNClient.u8_ButtonState;
}

/*- APIs IMPLEMENTATION
-----------------------------------*/
int main(void)
{
   /* Init Button Pins */
   Button_Init(BTN_0);
   
   /* Init Led Pin */
   DIO_SetPinDirection(GREEN_LED_PORT, GREEN_LED_PIN, OUTPUT);
   
   /* Init Button Client */
   BUTTONClient_Init(&GreenLed_BTNClient);
   BUTTONClient_SetBtn(&GreenLed_BTNClient, BTN_0);
   BUTTONClient_SetTimer(&GreenLed_BTNClient, TIMER_2, 20);
   BUTTONClient_SetEventCallback(&GreenLed_BTNClient, GreenLedMain);
   
   while (1) 
   {
      BUTTONClient_EventReceive(&GreenLed_BTNClient);
   }
}

