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
#define GREEN_LED_PORT  PORTA
#define GREEN_LED_PIN   PIN_0
#define RED_LED_PORT    PORTA
#define RED_LED_PIN     PIN_1

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/
void ToggleGreenLED(void);
void ToggleRedLED(void);

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
void ToggleGreenLED(void)
{
   DIO_TogglePin(GREEN_LED_PORT, GREEN_LED_PIN);
   Interrupt_Deinstall(TIMER2_OVF_VECTOR_NUMBER);
   Interrupt_Install(TIMER2_OVF_VECTOR_NUMBER, ToggleRedLED);
   TIM_Start(TIMER_2, 255);
}

void ToggleRedLED(void)
{
   DIO_TogglePin(RED_LED_PORT, RED_LED_PIN);
   Interrupt_Deinstall(TIMER2_OVF_VECTOR_NUMBER);
   Interrupt_Install(TIMER2_OVF_VECTOR_NUMBER, ToggleGreenLED);
   TIM_Start(TIMER_2, 255);
}

int main(void)
{
   DIO_SetPinDirection(GREEN_LED_PORT, GREEN_LED_PIN, OUTPUT);
   DIO_SetPinDirection(RED_LED_PORT, RED_LED_PIN, OUTPUT);
   
   TIM_Init(TIMER_2);

   Interrupt_Install(TIMER2_OVF_VECTOR_NUMBER, ToggleGreenLED);
   INTERRUPTS_Enable();
   
   TIM_Start(TIMER_2, 255);

   /* Replace with your application code */
   while (1) 
   {
   }
}

