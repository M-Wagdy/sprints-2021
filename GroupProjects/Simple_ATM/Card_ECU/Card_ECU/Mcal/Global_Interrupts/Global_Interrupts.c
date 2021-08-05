/*
 * Global_Interrupts.c
 *
 * Created: 7/24/2021 8:00:15 PM
 *  Author: Mohamed Wagdy
 */ 
/*- INCLUDES
----------------------------------------------*/
#include "Global_Interrupts.h"

/*- APIs IMPLEMENTATION
-----------------------------------*/

/**
* @brief: This function enables global interrupts.
*/
void GLOBALINTTERUPTS_Enable(void)
{
   GLOBAL_INTERRUPTS_CONTROL_R |= GLOBAL_INTERRUPT_BIT;
}

/**
* @brief: This function disables global interrupts.
*/
void GLOBALINTTERUPTS_Disable(void)
{
   GLOBAL_INTERRUPTS_CONTROL_R &= ~(GLOBAL_INTERRUPT_BIT);
}