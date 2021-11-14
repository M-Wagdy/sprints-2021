/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  WDT_Cfg.h
 *       Module:  WDT
 *
 *  Description:  header file for WDT module preprocessor configurations.
 *
 *********************************************************************************************************************/
#ifndef __WDT_CFG_H__
#define __WDT_CFG_H__

/*- INCLUDES -----------------------------------------------*/
#include "Std_Types.h"

/*- CONSTANTS ----------------------------------------------*/
#define WDT_ENABLE_BIT          (uint8_t)(0)
#define WDT_RESET_EN_BIT        (uint8_t)(1)
#define WDT_INT_NMI_BIT         (uint8_t)(2)
#define WDT_STALL_BIT           (uint8_t)(8)
#define WDT_WRITE_COMPLETE_BIT  (uint8_t)(31)

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/

#endif  /* __WDT_CFG_H__ */
