/*
 * InterruptDesingPatternTestApp.c
 *
 * Created: 8/19/2021 12:15:21 PM
 * Author : Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "TIMER.h"
#include "DIO.h"
#include "Interrupt_Design_Pattern.h"

/*- LOCAL MACROS
------------------------------------------*/
/* Green Led Macros */
#define GREEN_LED_PORT  PORTA
#define GREEN_LED_PIN   PIN_0

/* Red Led Macros */
#define RED_LED_PORT    PORTA
#define RED_LED_PIN     PIN_1

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/
/* Callback Functions to be installed in the ISR Handler. */
void ToggleGreenLED(void);
void ToggleRedLED(void);

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
void ToggleGreenLED(void)
{
   /* Toggle Green Led */
   DIO_TogglePin(GREEN_LED_PORT, GREEN_LED_PIN);
   /* Deinstall this Callback from ISR Vector Table. */
   Interrupt_Deinstall(TIMER2_OVF_VECTOR_NUMBER);
   /* Install the other Callback to ISR Vector Table. */
   Interrupt_Install(TIMER2_OVF_VECTOR_NUMBER, ToggleRedLED);
   /* Start a new Timer */
   TIM_Start(TIMER_2, 0);
}

void ToggleRedLED(void)
{
   /* Toggle Red Led */
   DIO_TogglePin(RED_LED_PORT, RED_LED_PIN);
   /* Deinstall this Callback from ISR Vector Table. */
   Interrupt_Deinstall(TIMER2_OVF_VECTOR_NUMBER);
   /* Install the other Callback to ISR Vector Table. */
   Interrupt_Install(TIMER2_OVF_VECTOR_NUMBER, ToggleGreenLED);
   /* Start a new Timer */
   TIM_Start(TIMER_2, 255);
}

int main(void)
{
   /* Initialize Led Pins */
   DIO_SetPinDirection(GREEN_LED_PORT, GREEN_LED_PIN, OUTPUT);
   DIO_SetPinDirection(RED_LED_PORT, RED_LED_PIN, OUTPUT);
   
   /* Initialize Timer */
   TIM_Init(TIMER_2);

   /* Install Green Led Toggle API in ISR Vector Table */
   Interrupt_Install(TIMER2_OVF_VECTOR_NUMBER, ToggleGreenLED);
   /* Enable Globale Interrupt */
   INTERRUPTS_Enable();
   
   /* Start a Timer */
   TIM_Start(TIMER_2, 0);

   while (1) 
   {
      /* Do Nothing Wait For Interrupts. */
   }
}

