/*
 * Interrupt_Design_Pattern.h
 *
 * Created: 8/19/2021 12:22:29 PM
 * Author: Mohamed Wagdy
 */ 

#ifndef __INTERRUPT_DESIGN_PATTERN_H__
#define __INTERRUPT_DESIGN_PATTERN_H__

/*- INCLUDES -----------------------------------------------*/
#include "Interrupts.h"
#include "STD_TYPES.h"

/*- FUNCTION DECLARATIONS ----------------------------------*/
/* Install new Callback function to the ISR array. */
void Interrupt_Install(uint8_t Vector_No, Ptr_VoidFuncVoid_t Callback);

/* Returns the old Callback function to the ISR array. */
void Interrupt_Deinstall(uint8_t Vector_No);

#endif /* __INTERRUPT_DESIGN_PATTERN_H__ */