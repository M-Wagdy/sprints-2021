/*
 * TIMER_DRIVER.h
 *
 *  Created on: Jul 9, 2021
 *      Author: zoldeyck
 */

#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_
#include "TIMER_DRIVER_typedefs.h"
//Timers
#define TIMER0 					0
#define TIMER1 					1
#define TIMER2 					2
// the pre-scaler factor (1, 8, 64, 256, or 1024).
#define	_NoCLK					0
#define	_SYSCLK					1
#define	_SYSCLK_DivideBy8		2
#define	_SYSCLK_DivideBy64		3
#define	_SYSCLK_DivideBy256		4
#define	_SYSCLK_DivideBy1024	5
#define	_EXTCLK_FallingEdge		6
#define	_EXTCLK_RisingEdge		7
// timer modes
#define	Normal					0
#define	CLR_Timer_OnCompare		1
#define	PWM_PhaseCorrect		2
#define	Fast_PWM				3
// compare-match output modes
#define CO_DISABLED_MODE		0
#define CO_TOGGLE_MODE			1 //available only in non-pwm modes
#define CO_CLEAR_MODE			2
#define CO_SET_MODE				3
//available Timer interrupts
#define TIM0OVF 				0
#define TIM0COMP 				1
#define TIM2COMP 				0
#define TIM2OVF 				1
#define TIM1CAPT 				0
#define TIM1COMPA 				1
#define TIM1COMPB 				2
#define TIM1OVF 				3

#define EXIT_SUCCESFUL			0
#define EXIT_FAILURE   			1

#define TIM_FLAG_UP				0
#define TIM_FLAG_DOWN   		1

TIM_ERROR_t TIM_Init(TIM_SELECT_t Timer, TIM_CLK_SELECT_t clock,
		TIMER_MODE_t timer_mode, TIM_CMPMATCH_OUTPUT_t compareMatch_output_mode,
		uint16_t counterValue, uint16_t compareValue);

TIM_ERROR_t TIM_SetTimerPreLoadVal(TIM_SELECT_t Timer, uint16_t counterValue);

TIM_ERROR_t TIM_SetTimerOCVal(TIM_SELECT_t Timer, uint16_t compareValue);

TIM_ERROR_t TIM_SetTimerOVFAction(TIM_SELECT_t Timer, void (*callback)(void));

TIM_ERROR_t TIM_SetTimerOCAction(TIM_SELECT_t Timer, void (*callback)(void));

TIM_ERROR_t TIM_MODE_SLCT(TIM_SELECT_t Timer, TIMER_MODE_t mode);

TIM_ERROR_t TIM_CLK_SLCT(TIM_SELECT_t Timer, TIM_CLK_SELECT_t clock);

TIM_ERROR_t TIM_OC_MODE_SLCT(TIM_SELECT_t Timer,
		TIM_CMPMATCH_OUTPUT_t compareMatch_output_mode, TIMER_MODE_t mode);

TIM_ERROR_t TIM_Interrupt_Enable(TIM_SELECT_t Timer, TIM_Interrupt_t interrupt);

TIM_ERROR_t TIM_Interrupt_Disable(TIM_SELECT_t Timer, TIM_Interrupt_t interrupt);

TIM_FLAG_STAT_t TIM_Flag_Get(TIM_SELECT_t Timer, TIM_Interrupt_t interrupt);

TIM_ERROR_t TIM_Flag_Reset(TIM_SELECT_t Timer, TIM_Interrupt_t interrupt);

TIM_ERROR_t TIM_Init_OC_PIN(TIM_SELECT_t Timer,
		TIM_CMPMATCH_OUTPUT_t compareMatch_output_mode);

TIM_FLAG_STAT_t TIM_Flag_Get(TIM_SELECT_t Timer, TIM_Interrupt_t interrupt);

TIM_ERROR_t TIM_Delay_US(TIM_SELECT_t Timer, Delay_value_t delayVal);

TIM_ERROR_t TIM_Delay_MS(TIM_SELECT_t Timer, Delay_value_t delayVal);

#endif /* TIMER_DRIVER_H_ */
