/*
 * TIMER_DRIVER_PRIV.h
 *
 *  Created on: Jul 9, 2021
 *      Author: zoldeyck
 */

#ifndef TIMER_DRIVER_PRIV_H_
#define TIMER_DRIVER_PRIV_H_

//control registers of timers
#define TIM0_Ctrl_REG 				*((volatile uint8_t*)0x53)//TCCR0
#define TIM1_Ctrl_REG_A 			*((volatile uint8_t*)0x4F)
#define TIM1_Ctrl_REG_B 			*((volatile uint8_t*)0x4E)
#define TIM2_Ctrl_REG				*((volatile uint8_t*)0x45)//TCCR2
#define WD_TIM_Ctrl_REG				*((volatile uint8_t*)0x41)//WatchDog timer control register


#define TIM0_CurrCount_REG 			*((volatile uint8_t*)0x52)//TCNT0
#define TIM1_CurrCount_REG_H 		*((volatile uint8_t*)0x4D)
#define TIM1_CurrCount_REG_L 		*((volatile uint8_t*)0x4C)
#define TIM2_CurrCount_REG 			*((volatile uint8_t*)0x44)//TCNT0

#define TIM0_OutputComp_REG 		*((volatile uint8_t*)0x5C)//OCR0
#define TIM1_OutputComp_REG_A_H     *((volatile uint8_t*)0x4B)
#define TIM1_OutputComp_REG_A_L     *((volatile uint8_t*)0x4A)
#define TIM1_OutputComp_REG_B_H     *((volatile uint8_t*)0x49)
#define TIM1_OutputComp_REG_B_L     *((volatile uint8_t*)0x48)
#define TIM2_OutputComp_REG 		*((volatile uint8_t*)0x43)//OCR2

#define TIMS_InterruptFlag_REG 		*((volatile uint8_t*)0x58)//TIFR
#define TIMS_InterruptMask_REG 		*((volatile uint8_t*)0x59)//TIMSK
#define STATUS_REG		 			*((volatile uint8_t*)0x5F)//SREG

#define TIM1_InputCap_REG_H     	*((volatile uint8_t*)0x47)//ICR1H
#define TIM1_InputCap_REG_L       	*((volatile uint8_t*)0x46)//ICR1L



//BITS OF TIMER0 CONTROL REGISTER
#define TIM0_MODE_SELECT_BIT1 				6
#define TIM0_MODE_SELECT_BIT2 				3
#define TIM0_MODE_SELECT_CLRMSK 			0b01001000
#define	TIM0_Normal_SETMSK					0b00000000
#define	TIM0_CLR_Timer_OnCompare_SETMSK		0b00001000
#define	TIM0_PWM_PhaseCorrect_SETMSK		0b01000000
#define	TIM0_Fast_PWM_SETMSK				0b01001000

#define TIM0_OC0_OUTPUT_CTRL_BIT1 			4
#define TIM0_OC0_OUTPUT_CTRL_BIT2 			5
#define TIM0_OC0_OUTPUT_CTRL_CLRMSK 		0b00110000
#define TIM0_CO_DISABLED_MODE_SETMSK		0b00000000
#define TIM0_CO_TOGGLE_MODE_SETMSK			0b00010000
#define TIM0_CO_CLEAR_MODE_SETMSK			0b00100000
#define TIM0_CO_SET_MODE_SETMSK				0b00110000

#define TIM0_CLK_PRSCLR_CTRL_BIT1 			0
#define TIM0_CLK_PRSCLR_CTRL_BIT2 			1
#define TIM0_CLK_PRSCLR_CTRL_BIT3 			2
#define TIM0_CLK_PRSCLR_CTRL_CLRMSK 		0b00000111
#define	TIM0_NoCLK_SETMSK					0b00000000
#define	TIM0_SYSCLK_SETMSK					0b00000001
#define	TIM0_SYSCLK_DivideBy8_SETMSK		0b00000010
#define	TIM0_SYSCLK_DivideBy64_SETMSK		0b00000011
#define	TIM0_SYSCLK_DivideBy256_SETMSK		0b00000100
#define	TIM0_SYSCLK_DivideBy1024_SETMSK		0b00000101
#define	TIM0_EXTCLK_FallingEdge_SETMSK		0b00000110
#define	TIM0_EXTCLK_RisingEdge_SETMSK		0b00000111

//BITS OF TIMER2 CONTROL REGISTER
#define TIM2_MODE_SELECT_BIT1 				6
#define TIM2_MODE_SELECT_BIT2 				3
#define TIM2_MODE_SELECT_CLRMSK 			0b01001000
#define	TIM2_Normal_SETMSK					0b00000000
#define	TIM2_CLR_Timer_OnCompare_SETMSK		0b00001000
#define	TIM2_PWM_PhaseCorrect_SETMSK		0b01000000
#define	TIM2_Fast_PWM_SETMSK				0b01001000

#define TIM2_OC0_OUTPUT_CTRL_BIT1 			4
#define TIM2_OC0_OUTPUT_CTRL_BIT2 			5
#define TIM2_OC2_OUTPUT_CTRL_CLRMSK 		0b00110000
#define TIM2_CO_DISABLED_MODE_SETMSK		0b00000000
#define TIM2_CO_TOGGLE_MODE_SETMSK			0b00010000
#define TIM2_CO_CLEAR_MODE_SETMSK			0b00100000
#define TIM2_CO_SET_MODE_SETMSK				0b00110000

#define TIM2_CLK_PRSCLR_CTRL_BIT1 			0
#define TIM2_CLK_PRSCLR_CTRL_BIT2 			1
#define TIM2_CLK_PRSCLR_CTRL_BIT3 			2
#define TIM2_CLK_PRSCLR_CTRL_CLRMSK 		0b00000111
#define	TIM2_NoCLK_SETMSK					0b00000000
#define	TIM2_SYSCLK_SETMSK					0b00000001
#define	TIM2_SYSCLK_DivideBy8_SETMSK		0b00000010
#define	TIM2_SYSCLK_DivideBy64_SETMSK		0b00000011
#define	TIM2_SYSCLK_DivideBy256_SETMSK		0b00000100
#define	TIM2_SYSCLK_DivideBy1024_SETMSK		0b00000101
#define	TIM2_EXTCLK_FallingEdge_SETMSK		0b00000110
#define	TIM2_EXTCLK_RisingEdge_SETMSK		0b00000111

//BITS OF TIMER0 for INTERRUPT MASK
#define TIM0_OverFlow_Interrupt_Enable_BIT 		0
#define TIM0_OutputComp_Interrupt_Enable_BIT 	1
//BITS OF TIMER0 for INTERRUPT FLAG
#define TIM0_OVF_Interrupt_Flg_BIT 				0
#define TIM0_OC_Interrupt_Flg_BIT 				1
//BITS OF TIMER2 for INTERRUPT MASK
#define TIM2_OverFlow_Interrupt_Enable_BIT 		6
#define TIM2_OutputComp_Interrupt_Enable_BIT 	7
//BITS OF TIMER2 for INTERRUPT FLAG
#define TIM2_OVF_Interrupt_Flg_BIT 				6
#define TIM2_OC_Interrupt_Flg_BIT 				7
//BIT OF GLOBAL INTERRUPT MASK
#define GLOBAL_Interrupt_Enable_BIT 			7

void static (*TIM0_OVFAction_callback)(void)=NULL_PTR;
void static (*TIM0_OCAction_callback)(void)=NULL_PTR;
void static (*TIM2_OVFAction_callback)(void)=NULL_PTR;
void static (*TIM2_OCAction_callback)(void)=NULL_PTR;

#endif /* TIMER_DRIVER_PRIV_H_ */
