/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  WDT_Lcfg.h
 *       Module:  WDT
 *
 *  Description:  header file for WDT module linking configurations.
 *
 *********************************************************************************************************************/
#ifndef __WDT_LCFG_H__
#define __WDT_LCFG_H__

/*- INCLUDES -----------------------------------------------*/
#include "Std_Types.h"

/*- CONSTANTS ----------------------------------------------*/
/* Interrupt Type Macros */
#define WDT_INT_NMI_TYPE        STD_HIGH
#define WDT_INT_STD_TYPE        STD_LOW
#define WDT_DEFAULT_INT_TYPE    WDT_INT_STD

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct Wdg_ConfigType{
   Ptr_VoidFuncVoid_t NotificationEN;
   uint8_t  u8_InterruptType;
   uint16_t  u16_WdgInitialTimeout;
   uint16_t  u16_WdgMaxTimeout;
} Wdg_ConfigType;

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/

#endif  /* __WDT_LCFG_H__ */
