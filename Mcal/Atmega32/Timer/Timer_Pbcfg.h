/*
 * Timer_Pbcfg.h
 *
 * Created: 7/8/2021 1:08:25 PM
 *  Author: Mohamed Wagdy
 */ 

#ifndef __TIMER_PBCFG_H__
#define __TIMER_PBCFG_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../../Infrastructure/STD_types.h"

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct STR_TIMER_config_t{
   uint8_t timer_no;
   uint8_t mode;
   uint8_t interrupt_mode;
} STR_TIMER_config_t;

/*- MACROS -------------------------------------------------*/
#define  TIMERS_NUMBER       (uint8_t)( 2 )

#define  TIMER_0              (uint8_t)( 0 )
#define  TIMER_2              (uint8_t)( 1 )

#define  CLK_NO_SRC           (uint8_t)( 0x00 )
#define  CLK_1_MHZ            (uint8_t)( 0x01 )
#define  CLK_125_KHZ          (uint8_t)( 0x02 )
#define  CLK_16_KHZ           (uint8_t)( 0x03 )
#define  CLK_4_KHZ            (uint8_t)( 0x04 )
#define  CLK_1_KHZ            (uint8_t)( 0x05 )
#define  CLK_EXT_FALLING_EDGE (uint8_t)( 0x06 )
#define  CLK_EXT_RISING_EDGE  (uint8_t)( 0x07 )
#define  CLK_DEFAULT          (uint8_t)( 0x00 )

#define  NORMAL_MODE          (uint8_t)( 0x00 )
#define  PHASE_PWM_MODE       (uint8_t)( 0x40 )
#define  COMPARE_MATCH_MODE   (uint8_t)( 0x08 )
#define  FAST_PWM_MODE        (uint8_t)( 0x48 )
#define  DEFAULT_MODE         (uint8_t)( 0x00 )

#define  NO_INTERRUPT         (uint8_t)( 0x00 )
#define  OVERFLOW_INTERRUPT   (uint8_t)( 0x01 )
#define  COMPARE_INTERRUPT    (uint8_t)( 0x02 )
#define  DEFAULT_INTERRUPT    (uint8_t)( 0 )

#endif /* __TIMER_PBCFG_H__ */