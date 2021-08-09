/*
 * Timer_Registers.h
 *
 * Created: 8/9/2021 12:04:23 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __TIMER_REGISTERS_H__
#define __TIMER_REGISTERS_H__

/*- INCLUDES -----------------------------------------------*/
#include "Infrastructure/STD_TYPES.h"

/*- TIMER0 REGISTERS-----------------------------------------*/
#define  TIMER_0_CONTROL      (*((volatile uint8_t *) (0x53)))
#define  TIMER_0_DATA         (*((volatile uint8_t *) (0x52)))
#define  TIMER_0_COMPARE      (*((volatile uint8_t *) (0x5C)))

/*- TIMER1 REGISTERS-----------------------------------------*/
#define  TIMER_1_DATA         (*((volatile uint16_t *) (0x4C)))
#define  TIMER_1A_COMPARE     (*((volatile uint16_t *) (0x4A)))
#define  TIMER_1B_COMPARE     (*((volatile uint16_t *) (0x48)))
#define  TIMER_1A_CONTROL     (*((volatile uint8_t *) (0x4F)))
#define  TIMER_1B_CONTROL     (*((volatile uint8_t *) (0x4E)))

/*- TIMER2 REGISTERS-----------------------------------------*/
#define  TIMER_2_CONTROL      (*((volatile uint8_t *) (0x45)))
#define  TIMER_2_DATA         (*((volatile uint8_t *) (0x44)))
#define  TIMER_2_COMPARE      (*((volatile uint8_t *) (0x43)))

/*- TIMER INTERRUPTS REGISTERS-------------------------------*/
#define  TIMER_INT_MASK       (*((volatile uint8_t *) (0x59)))
#define  TIMER_INT_FLAG       (*((volatile uint8_t *) (0x58)))

#endif /* __TIMER_REGISTERS_H__ */