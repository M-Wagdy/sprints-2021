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
/* System Clock Divisor Values */
#define SYSDIV_1                (uint8_t)(0x00)
#define SYSDIV_2                (uint8_t)(0x01)
#define SYSDIV_3                (uint8_t)(0x02)
#define SYSDIV_4                (uint8_t)(0x03)
#define SYSDIV_5                (uint8_t)(0x04)
#define SYSDIV_6                (uint8_t)(0x05)
#define SYSDIV_7                (uint8_t)(0x06)
#define SYSDIV_8                (uint8_t)(0x07)
#define SYSDIV_9                (uint8_t)(0x08)
#define SYSDIV_10               (uint8_t)(0x09)
#define SYSDIV_11               (uint8_t)(0x0A)
#define SYSDIV_12               (uint8_t)(0x0B)
#define SYSDIV_13               (uint8_t)(0x0C)
#define SYSDIV_14               (uint8_t)(0x0D)
#define SYSDIV_15               (uint8_t)(0x0E)
#define SYSDIV_16               (uint8_t)(0x0F)
#define SYSDIV_INVALID          (uint8_t)(0x10)

/* System Clock Divisor Enable Values */
#define USESYSDIV_DIS           (uint8_t)(0x00)
#define USESYSDIV_EN            (uint8_t)(0x01)
#define USESYSDIV_INVALID       (uint8_t)(0x02)

/* XTAL Values */
#define XTAL_4_MHZ              (uint8_t)(0x06)
#define XTAL_4096_KHZ           (uint8_t)(0x07)
#define XTAL_4915_KHZ           (uint8_t)(0x08)
#define XTAL_5_MHZ              (uint8_t)(0x09)
#define XTAL_5120_KHZ           (uint8_t)(0x0A)
#define XTAL_6_MHZ              (uint8_t)(0x0B)
#define XTAL_6144_KHZ           (uint8_t)(0x0C)
#define XTAL_7373_KHZ           (uint8_t)(0x0D)
#define XTAL_8_MHZ              (uint8_t)(0x0E)
#define XTAL_8192_KHZ           (uint8_t)(0x0F)
#define XTAL_10_MHZ             (uint8_t)(0x10)
#define XTAL_12_MHZ             (uint8_t)(0x11)
#define XTAL_12288_KHZ          (uint8_t)(0x12)
#define XTAL_13560_KHZ          (uint8_t)(0x13)
#define XTAL_14318_KHZ          (uint8_t)(0x14)
#define XTAL_16_MHZ             (uint8_t)(0x15)
#define XTAL_16384_KHZ          (uint8_t)(0x16)
#define XTAL_18_MHZ             (uint8_t)(0x17)
#define XTAL_20_MHZ             (uint8_t)(0x18)
#define XTAL_24_MHZ             (uint8_t)(0x19)
#define XTAL_25_MHZ             (uint8_t)(0x1A)
#define XTAL_MIN_VAL            XTAL_4_MHZ
#define XTAL_MAX_VAL            XTAL_25_MHZ

/* Oscillator Source Values */
#define OSCSRC_MOSC             (uint8_t)(0x00)
#define OSCSRC_PIOSC            (uint8_t)(0x01)
#define OSCSRC_PIOSC_DIV_4      (uint8_t)(0x02)
#define OSCSRC_LFIOSC           (uint8_t)(0x03)
#define OSCSRC_INVALID_VAL      (uint8_t)(0x04)

/* Main Oscillator Enable Values */
#define MOSC_EN                 (uint8_t)(0x00)
#define MOSC_DIS                (uint8_t)(0x01)
#define MOSC_INVALID            (uint8_t)(0x02)

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct STR_MCU_config_t{
   uint8_t          u8_SYSDIV;
   uint8_t          u8_USESYSDIV;
   uint8_t          u8_XTAL;
   uint8_t          u8_OSCSRC;
   uint8_t          u8_MOSCDIS;
} STR_MCU_config_t;

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/

#endif  /* __MCU_LCFG_H__ */
