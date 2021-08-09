/*
 * Timer_Registers.h
 *
 * Created: 8/9/2021 12:04:23 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __TIMER_REGISTERS_H__
#define __TIMER_REGISTERS_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_TYPES.h"

/*- TIMER0 REGISTERS-----------------------------------------*/
volatile uint8_t  TIMER_0_CONTROL;
volatile uint8_t  TIMER_0_DATA;
volatile uint8_t  TIMER_0_COMPARE;
/*- TIMER1 REGISTERS-----------------------------------------*/
volatile uint16_t  TIMER_1_DATA;
volatile uint16_t  TIMER_1A_COMPARE;
volatile uint16_t  TIMER_1B_COMPARE;
volatile uint8_t  TIMER_1A_CONTROL;
volatile uint8_t  TIMER_1B_CONTROL;

/*- TIMER2 REGISTERS-----------------------------------------*/
volatile uint8_t  TIMER_2_CONTROL;
volatile uint8_t  TIMER_2_DATA;
volatile uint8_t  TIMER_2_COMPARE;

/*- TIMER INTERRUPTS REGISTERS-------------------------------*/
volatile uint8_t  TIMER_INT_MASK;
volatile uint8_t  TIMER_INT_FLAG;




#endif /* __TIMER_REGISTERS_H__ */