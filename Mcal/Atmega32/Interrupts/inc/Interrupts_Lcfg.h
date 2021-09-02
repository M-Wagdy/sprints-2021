/*
 * Interrupts_Lcfg.h
 *
 * Created: 8/19/2021 1:21:24 PM
 * Author: Mohamed Wagdy
 */ 

#ifndef __INTERRUPTS_LCFG_H__
#define __INTERRUPTS_LCFG_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_TYPES.h"

/*- MACROS -------------------------------------------------*/
#define TABLE_SIZE						(uint8_t)(20)

#define INT0_VECTOR_NUMBER				(uint8_t)(0)
#define INT1_VECTOR_NUMBER				(uint8_t)(1)
#define INT2_VECTOR_NUMBER				(uint8_t)(2)
#define TIMER2_COMP_VECTOR_NUMBER	(uint8_t)(3)
#define TIMER2_OVF_VECTOR_NUMBER		(uint8_t)(4)
#define TIMER1_CAPT_VECTOR_NUMBER	(uint8_t)(5)
#define TIMER1_COMPA_VECTOR_NUMBER	(uint8_t)(6)
#define TIMER1_COMPB_VECTOR_NUMBER	(uint8_t)(7)
#define TIMER1_OVF_VECTOR_NUMBER		(uint8_t)(8)
#define TIMER0_COMP_VECTOR_NUMBER	(uint8_t)(9)
#define TIMER0_OVF_VECTOR_NUMBER		(uint8_t)(10)
#define SPI_STC_VECTOR_NUMBER			(uint8_t)(11)
#define USART_RXC_VECTOR_NUMBER		(uint8_t)(12)
#define USART_UDRE_VECTOR_NUMBER		(uint8_t)(13)
#define USART_TXC_VECTOR_NUMBER		(uint8_t)(14)
#define ADC_VECTOR_NUMBER				(uint8_t)(15)
#define EE_RDY_VECTOR_NUMBER			(uint8_t)(16)
#define ANA_COMP_VECTOR_NUMBER		(uint8_t)(17)
#define TWI_VECTOR_NUMBER				(uint8_t)(18)
#define SPM_RDY_VECTOR_NUMBER			(uint8_t)(19)

#define IRQ_MIN_VECTOR_NUMBER			INT0_VECTOR_NUMBER
#define IRQ_MAX_VECTOR_NUMBER			SPM_RDY_VECTOR_NUMBER

#endif /* __INTERRUPTS_LCFG_H__ */