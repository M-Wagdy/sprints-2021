/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Mcu_Hw.h
 *       Module:  Mcu_Hw
 *
 *  Description:  header file for Registers definition    
 *  
 *********************************************************************************************************************/
#ifndef __MCU_HW_H__
#define __MCU_HW_H__

/*- INCLUDES -----------------------------------------------*/
#include "Std_Types.h"
#include "Mcu_HwTags.h"

/*- CONSTANTS ----------------------------------------------*/
#define CORTEXM4_PERI_BASE_ADDRESS     (uint32_t)(0xE000E000)

/*- Systick Timer Registers---------------------------------*/
#define STCTRL                         (*((volatile STCTRL_Tag *)(CORTEXM4_PERI_BASE_ADDRESS+0x010)))
#define STRELOAD                       (*((volatile STRELOAD_Tag *)(CORTEXM4_PERI_BASE_ADDRESS+0x014)))
#define STCURRENT                      (*((volatile STCURRENT_Tag *)(CORTEXM4_PERI_BASE_ADDRESS+0x018)))
   
#define APINT                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0xD0C)))
#define INTCTRL                        (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0xD04)))

/*- System Control Registers--------------------------------*/
#define SYSCTL_BASE_ADDRESS            (uint32_t)(0x400FE000)
#define SYSCTL_RCC                     (*((volatile uint32_t *)(SYSCTL_BASE_ADDRESS+0x060)))
#define SYSCTL_RCGCGPIO                (*((volatile uint32_t *)(SYSCTL_BASE_ADDRESS+0x608)))
#define SYSCTL_PRGPIO                  (*((volatile uint32_t *)(SYSCTL_BASE_ADDRESS+0xA08)))
   
/*- PortF APB Registers--------------------------------*/ 
#define PORTF_APB_BASE_ADDRESS         (uint32_t)(0x40025000)
#define PORTF_LOCK                     (*((volatile uint32_t *)(PORTF_APB_BASE_ADDRESS+0x520)))
#define PORTF_CR                       (*((volatile uint32_t *)(PORTF_APB_BASE_ADDRESS+0x524)))
#define PORTF_DIR                      (*((volatile uint32_t *)(PORTF_APB_BASE_ADDRESS+0x400)))
#define PORTF_DEN                      (*((volatile uint32_t *)(PORTF_APB_BASE_ADDRESS+0x51C)))
#define PORTF_DATA                     (*((volatile uint32_t *)(PORTF_APB_BASE_ADDRESS+0x038)))
   
/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/
 
#endif  /* __MCU_HW_H__ */
