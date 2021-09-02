/*
 * DIO_PbCfg.h
 *
 * Created: 7/7/2021 5:40:29 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __DIO_PBCFG_H__
#define __DIO_PBCFG_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_types.h"

/*- MACROS -------------------------------------------------*/
#define  PINS_NUMBERS      (uint8_t)( 32 )

#define  OUTPUT            (uint8_t)( 1 )
#define  INPUT             (uint8_t)( 0 )
#define  DEFAULT_DIR       (uint8_t)( 0 )

#define  OPEN_DRAIN        (uint8_t)( 0 )
#define  PULL_UP           (uint8_t)( 1 )
#define  DEFAULT_RESISTOR  (uint8_t)( 0 )

#define  INITIAL_HIGH      (uint8_t)( 1 )
#define  INITIAL_LOW       (uint8_t)( 0 )
#define  DEFAULT_INITIAL   (uint8_t)( 0 )

#define  PORTA             (uint8_t)( 0 )
#define  PORTB             (uint8_t)( 1 )
#define  PORTC             (uint8_t)( 2 )
#define  PORTD             (uint8_t)( 3 )

#define  PIN_0             (uint8_t)( 0 )
#define  PIN_1             (uint8_t)( 1 )
#define  PIN_2             (uint8_t)( 2 )
#define  PIN_3             (uint8_t)( 3 )
#define  PIN_4             (uint8_t)( 4 )
#define  PIN_5             (uint8_t)( 5 )
#define  PIN_6             (uint8_t)( 6 )
#define  PIN_7             (uint8_t)( 7 )

#endif /* __DIO_PBCFG_H__ */