/*
 * Interrupts.h
 *
 * Created: 8/19/2021 12:21:30 PM
 * Author: Mohamed Wagdy
 */ 

#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__

/*- INCLUDES -----------------------------------------------*/
#include "Interrupts_Lcfg.h"

/*- Interrupt Vectors-----------------------------------------*/
#define INT0_IRQ						   __vector_1
#define INT1_IRQ						   __vector_2
#define INT2_IRQ						   __vector_3
#define TIMER2_COMP_IRQ					__vector_4
#define TIMER2_OVF_IRQ					__vector_5
#define TIMER1_CAPT_IRQ					__vector_6
#define TIMER1_COMPA_IRQ				__vector_7
#define TIMER1_COMPB_IRQ				__vector_8
#define TIMER1_OVF_IRQ					__vector_9
#define TIMER0_COMP_IRQ					__vector_10
#define TIMER0_OVF_IRQ					__vector_11
#define SPI_STC_IRQ						__vector_12
#define USART_RXC_IRQ					__vector_13
#define USART_UDRE_IRQ					__vector_14
#define USART_TXC_IRQ					__vector_15
#define ADC_IRQ							__vector_16
#define EE_RDY_IRQ						__vector_17
#define ANA_COMP_IRQ					   __vector_18
#define TWI_IRQ							__vector_19
#define SPM_RDY_IRQ						__vector_20

/*- FUNCTION-LIKE MACROS -----------------------------------*/
#  define ISR(vector, ...)            \
void vector (void) __attribute__ ((signal)); \
void vector (void)

/*- FUNCTION DECLARATIONS ----------------------------------*/
/* Function that enables global interrupts. */
void INTERRUPTS_Enable(void);

/* Function that disables global interrupts. */
void INTERRUPTS_Disable(void);

#endif /* __INTERRUPTS_H__ */