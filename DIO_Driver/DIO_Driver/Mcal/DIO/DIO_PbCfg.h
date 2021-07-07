/*
 * DIO_PbCfg.h
 *
 * Created: 7/7/2021 5:40:29 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __DIO_PBCFG_H__
#define __DIO_PBCFG_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../Infrastructure/STD_types.h"

/*- ENUMS --------------------------------------------------*/
typedef enum  {
   PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7
}ENU_pins;

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct STR_DIO_config_t{
   uint8_t port_no;
   ENU_pins pin_no;
   uint8_t direction;
   uint8_t resistor;
   uint8_t initial_value;
}STR_DIO_config_t;

/*- MACROS -------------------------------------------------*/
#define  PINS_NUMBERS      (uint8_t)32

#define  OUTPUT            (uint8_t)1
#define  INPUT             (uint8_t)0
#define  DEFAULT_DIR       (uint8_t)0

#define  OPEN_DRAIN        (uint8_t)0
#define  PULL_UP           (uint8_t)1
#define  DEFAULT_RESISTOR  (uint8_t)0

#define  INITIAL_HIGH       (uint8_t)1
#define  INITIAL_LOW        (uint8_t)0
#define  DEFAULT_INITIAL    (uint8_t)0

#define  PORTA             (uint8_t)0
#define  PORTB             (uint8_t)1
#define  PORTC             (uint8_t)2
#define  PORTD             (uint8_t)3

#endif /* __DIO_PBCFG_H__ */