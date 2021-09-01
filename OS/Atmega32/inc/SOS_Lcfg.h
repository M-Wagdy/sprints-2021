/*
 * SOS_Lcfg.h
 *
 * Created: 8/28/2021 3:22:02 PM
 * Author: Mohamed Wagdy
 */

#ifndef __SOS_LCFG_H__
#define __SOS_LCFG_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_types.h"

/*- MACROS -------------------------------------------------*/
#define  MAX_TASKS_NUMBER           (uint8_t)(10)
#define  MAX_TASK_PRIORTITY         (uint8_t)(8)

/* Systick Prescalers */
#define  CLK_NO_SRC                 (uint8_t)( 0x00 )
#define  CLK_NO_PRESCALE            (uint8_t)( 0x01 )
#define  CLK_8_PRESCALE             (uint8_t)( 0x02 )
#define  CLK_32_PRESCALE            (uint8_t)( 0x03 )
#define  CLK_64_PRESCALE            (uint8_t)( 0x04 )
#define  CLK_128_PRESCALE           (uint8_t)( 0x05 )
#define  CLK_256_PRESCALE           (uint8_t)( 0x06 )
#define  CLK_1024_PRESCALE          (uint8_t)( 0x07 )
#define  CLK_DEFAULT                CLK_NO_PRESCALE

/* Systick Mode */
#define  NORMAL_MODE                (uint8_t)( 0x00 )
#define  COMPARE_MATCH_MODE         (uint8_t)( 0x08 )
#define  DEFAULT_MODE               NORMAL_MODE

/*  */
#define  NO_INTERRUPT               (uint8_t)( 0x00 )
#define  SYSTICK_OVERFLOW_INTERRUPT (uint8_t)( 0x40 )
#define  SYSTICK_COMPARE_INTERRUPT  (uint8_t)( 0x80 )
#define  DEFAULT_INTERRUPT          SYSTICK_OVERFLOW_INTERRUPT

#define  SYSTICK_OVERFLOW_FLAG      (uint8_t)( 0x40 )
#define  SYSTICK_COMPARE_FLAG       (uint8_t)( 0x80 )

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct STR_SYSTICK_config_t{
   uint8_t u8_mode;
   uint8_t u8_interrupt_mode;
   uint8_t u8_prescale;
} STR_SYSTICK_config_t;

#endif /* __SOS_LCFG_H__ */