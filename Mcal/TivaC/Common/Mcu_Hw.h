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
#define STCTRL                         (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x010)))
#define STRELOAD                       (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x014)))
#define STCURRENT                      (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x018)))

/* NVIC Registers */
#define EN0                            (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x100)))
#define EN1                            (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x104)))
#define EN2                            (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x108)))
#define EN3                            (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x10C)))
#define EN4                            (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x110)))
#define DIS0                           (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x180)))
#define DIS1                           (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x184)))
#define DIS2                           (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x188)))
#define DIS3                           (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x18C)))
#define DIS4                           (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x190)))
#define PRI0                           (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x400)))
#define PRI1                           (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x404)))
#define PRI2                           (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x408)))
#define PRI3                           (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x40C)))
#define PRI4                           (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x410)))
#define PRI5                           (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x414)))
#define PRI6                           (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x418)))
#define PRI7                           (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x41C)))
#define PRI8                           (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x420)))
#define PRI9                           (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x424)))
#define PRI10                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x428)))
#define PRI11                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x42C)))
#define PRI12                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x430)))
#define PRI13                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x434)))
#define PRI14                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x438)))
#define PRI15                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x43C)))
#define PRI16                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x440)))
#define PRI17                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x444)))
#define PRI18                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x448)))
#define PRI19                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x44C)))
#define PRI20                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x450)))
#define PRI21                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x454)))
#define PRI22                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x458)))
#define PRI23                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x45C)))
#define PRI24                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x460)))
#define PRI25                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x464)))
#define PRI26                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x468)))
#define PRI27                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x46C)))
#define PRI28                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x470)))
#define PRI29                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x474)))
#define PRI30                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x478)))
#define PRI31                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x47C)))
#define PRI32                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x480)))
#define PRI33                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x484)))
#define PRI34                          (*((volatile uint32_t *)(CORTEXM4_PERI_BASE_ADDRESS+0x488)))

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
