/*
 * Timer_Registers.h
 *
 * Created: 7/8/2021 12:56:09 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __TIMER_REGISTERS_H__
#define __TIMER_REGISTERS_H__

/*- TIMER0 REGISTERS-----------------------------------------*/
#define  TIMER_0_CONTROL      (*((volatile uint8_t *) (0x53)))
#define  TIMER_0_DATA         (*((volatile uint8_t *) (0x52)))
#define  TIMER_0_COMPARE      (*((volatile uint8_t *) (0x5C)))

/*- TIMER2 REGISTERS-----------------------------------------*/
#define  TIMER_2_CONTROL      (*((volatile uint8_t *) (0x45)))
#define  TIMER_2_DATA         (*((volatile uint8_t *) (0x44)))
#define  TIMER_2_COMPARE      (*((volatile uint8_t *) (0x43)))

/*- TIMER INTERRUPTS REGISTERS-------------------------------*/
#define  TIMER_INT_MASK       (*((volatile uint8_t *) (0x59)))
#define  TIMER_INT_FLAG       (*((volatile uint8_t *) (0x58)))

#endif /* __TIMER_REGISTERS_H__ */