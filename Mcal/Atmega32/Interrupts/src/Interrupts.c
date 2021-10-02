/*
 * Interrupts.c
 *
 * Created: 8/19/2021 1:21:24 PM
 * Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "BIT_MATH.h"
#include "MC_REGISTERS.h"
#include "Interrupts.h"

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern Ptr_VoidFuncVoid_t aptr_ISRAddress[TABLE_SIZE];

/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function enables global interrupts.
*/
void INTERRUPTS_Enable(void)
{
   SET_BIT(SREG, BIT7);
}

/**
* @brief: This function disables global interrupts.
*/
void INTERRUPTS_Disable(void)
{
   CLEAR_BIT(SREG, BIT7);
}

/**
* @brief: INT0 ISR.
*/
ISR(INT0_IRQ)
{
   if(aptr_ISRAddress[INT0_VECTOR_NUMBER] != NULL_PTR)
   {
      aptr_ISRAddress[INT0_VECTOR_NUMBER]();
   }
}

/**
* @brief: INT1 ISR.
*/
ISR(INT1_IRQ)
{
   if(aptr_ISRAddress[INT1_VECTOR_NUMBER] != NULL_PTR)
   {
      aptr_ISRAddress[INT1_VECTOR_NUMBER]();
   }
}

/**
* @brief: INT2 ISR.
*/
ISR(INT2_IRQ)
{
   if(aptr_ISRAddress[INT2_VECTOR_NUMBER] != NULL_PTR)
   {
      aptr_ISRAddress[INT2_VECTOR_NUMBER]();
   }
}

/**
* @brief: TIMER2_COMP ISR.
*/
ISR(TIMER2_COMP_IRQ)
{
   if(aptr_ISRAddress[TIMER2_COMP_VECTOR_NUMBER] != NULL_PTR)
   {
      aptr_ISRAddress[TIMER2_COMP_VECTOR_NUMBER]();
   }
}

/**
* @brief: TIMER2_OVF ISR.
*/
ISR(TIMER2_OVF_IRQ)
{
   if(aptr_ISRAddress[TIMER2_OVF_VECTOR_NUMBER] != NULL_PTR)
   {
      aptr_ISRAddress[TIMER2_OVF_VECTOR_NUMBER]();
   }
}

/**
* @brief: TIMER1_CAPT ISR.
*/
ISR(TIMER1_CAPT_IRQ)
{
   if(aptr_ISRAddress[TIMER1_CAPT_VECTOR_NUMBER] != NULL_PTR)
   {
      aptr_ISRAddress[TIMER1_CAPT_VECTOR_NUMBER]();
   }
}

/**
* @brief: TIMER1_COMPA ISR.
*/
ISR(TIMER1_COMPA_IRQ)
{
   if(aptr_ISRAddress[TIMER1_COMPA_VECTOR_NUMBER] != NULL_PTR)
   {
      aptr_ISRAddress[TIMER1_COMPA_VECTOR_NUMBER]();
   }
}

/**
* @brief: TIMER1_COMPB ISR.
*/
ISR(TIMER1_COMPB_IRQ)
{
   if(aptr_ISRAddress[TIMER1_COMPB_VECTOR_NUMBER] != NULL_PTR)
   {
      aptr_ISRAddress[TIMER1_COMPB_VECTOR_NUMBER]();
   }
}

/**
* @brief: TIMER1_OVF ISR.
*/
ISR(TIMER1_OVF_IRQ)
{
   if(aptr_ISRAddress[TIMER1_OVF_VECTOR_NUMBER] != NULL_PTR)
   {
      aptr_ISRAddress[TIMER1_OVF_VECTOR_NUMBER]();
   }
}

/**
* @brief: TIMER0_COMP ISR.
*/
ISR(TIMER0_COMP_IRQ)
{
   if(aptr_ISRAddress[TIMER0_COMP_VECTOR_NUMBER] != NULL_PTR)
   {
      aptr_ISRAddress[TIMER0_COMP_VECTOR_NUMBER]();
   }
}

/**
* @brief: TIMER0_OVF ISR.
*/
ISR(TIMER0_OVF_IRQ)
{
   if(aptr_ISRAddress[TIMER0_OVF_VECTOR_NUMBER] != NULL_PTR)
   {
      aptr_ISRAddress[TIMER0_OVF_VECTOR_NUMBER]();
   }
}

/**
* @brief: SPI_STC ISR.
*/
ISR(SPI_STC_IRQ)
{
   if(aptr_ISRAddress[SPI_STC_VECTOR_NUMBER] != NULL_PTR)
   {
      aptr_ISRAddress[SPI_STC_VECTOR_NUMBER]();
   }
}

/**
* @brief: USART_RXC ISR.
*/
ISR(USART_RXC_IRQ)
{
   if(aptr_ISRAddress[USART_RXC_VECTOR_NUMBER] != NULL_PTR)
   {
      aptr_ISRAddress[USART_RXC_VECTOR_NUMBER]();
   }
}

/**
* @brief: USART_UDRE ISR.
*/
ISR(USART_UDRE_IRQ)
{
   if(aptr_ISRAddress[USART_UDRE_VECTOR_NUMBER] != NULL_PTR)
   {
      aptr_ISRAddress[USART_UDRE_VECTOR_NUMBER]();
   }
}

/**
* @brief: USART_TXC ISR.
*/
ISR(USART_TXC_IRQ)
{
   if(aptr_ISRAddress[USART_TXC_VECTOR_NUMBER] != NULL_PTR)
   {
      aptr_ISRAddress[USART_TXC_VECTOR_NUMBER]();
   }
}

/**
* @brief: ADC ISR.
*/
ISR(ADC_IRQ)
{
   if(aptr_ISRAddress[ADC_VECTOR_NUMBER] != NULL_PTR)
   {
      aptr_ISRAddress[ADC_VECTOR_NUMBER]();
   }
}

/**
* @brief: EE_RDY ISR.
*/
ISR(EE_RDY_IRQ)
{
   if(aptr_ISRAddress[EE_RDY_VECTOR_NUMBER] != NULL_PTR)
   {
      aptr_ISRAddress[EE_RDY_VECTOR_NUMBER]();
   }
}

/**
* @brief: ANA_COMP ISR.
*/
ISR(ANA_COMP_IRQ)
{
   if(aptr_ISRAddress[ANA_COMP_VECTOR_NUMBER] != NULL_PTR)
   {
      aptr_ISRAddress[ANA_COMP_VECTOR_NUMBER]();
   }
}

/**
* @brief: TWI ISR.
*/
ISR(TWI_IRQ)
{
   if(aptr_ISRAddress[TWI_VECTOR_NUMBER] != NULL_PTR)
   {
      aptr_ISRAddress[TWI_VECTOR_NUMBER]();
   }
}

/**
* @brief: SPM_RDY ISR.
*/
ISR(SPM_RDY_IRQ)
{
   if(aptr_ISRAddress[SPM_RDY_VECTOR_NUMBER] != NULL_PTR)
   {
      aptr_ISRAddress[SPM_RDY_VECTOR_NUMBER]();
   }
}