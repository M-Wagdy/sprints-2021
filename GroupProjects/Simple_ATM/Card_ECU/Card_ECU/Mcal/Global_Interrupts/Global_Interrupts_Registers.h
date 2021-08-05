/*
 * Global_Interrupts_Registers.h
 *
 * Created: 7/24/2021 8:03:06 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __GLOBAL_INTERRUPTS_REGISTERS_H__
#define __GLOBAL_INTERRUPTS_REGISTERS_H__

#define TEST 0

#if !TEST
/*- Global Interrupts REGISTERS-----------------------------*/
#define  GLOBAL_INTERRUPTS_CONTROL_R      (*((volatile uint8_t *) (0x5F)))

#else
/*- Global Interrupts REGISTERS-----------------------------*/
extern volatile uint8_t GLOBAL_INTERRUPTS_CONTROL_R;
#endif

#endif /* __GLOBAL_INTERRUPTS_REGISTERS_H__ */