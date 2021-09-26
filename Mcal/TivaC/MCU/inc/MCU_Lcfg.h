/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  MCU_Lcfg.h
 *       Module:  MCU
 *
 *  Description:  header file for MCU module linking configurations.
 *
 *********************************************************************************************************************/
#ifndef __MCU_LCFG_H__
#define __MCU_LCFG_H__

/*- INCLUDES -----------------------------------------------*/
#include "Std_Types.h"

/*- CONSTANTS ----------------------------------------------*/
#define CLOCK_SETTINGS_NUM      (uint8_t)(3)

/* Oscillator Source Values */
#define OSCSRC_MOSC             (uint8_t)(0x00)
#define OSCSRC_PIOSC            (uint8_t)(0x01)
#define OSCSRC_PIOSC_DIV_4      (uint8_t)(0x02)
#define OSCSRC_LFIOSC           (uint8_t)(0x03)
#define OSCSRC_INVALID_VAL      (uint8_t)(0x04)

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct STR_Mcu_ConfigType{
   uint8_t          u8_PLLUse;
   uint8_t          u8_OSCSRC;
   uint32_t         u32_Freq;
} STR_Mcu_ConfigType;

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/

#endif  /* __MCU_LCFG_H__ */
