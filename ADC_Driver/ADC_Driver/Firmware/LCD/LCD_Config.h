/*
 * LCD_Config.h
 *
 * Created: 7/25/2021 5:30:11 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __LCD_CONFIG_H__
#define __LCD_CONFIG_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../Infrastructure/STD_types.h"

/*- MACROS -------------------------------------------------*/

/* LCD COMMANDS */
#define LCD_4_BIT_MODE           (uint8_t)(0X02)
#define LCD_ENABLE_2_ROWS        (uint8_t)(0X28)
#define LCD_CLEAR                (uint8_t)(0X01)
#define LCD_CURSOR_OFF           (uint8_t)(0x0C)
#define LCD_CURSOR_ON            (uint8_t)(0x0E)
#define LDC_SET_CURSOR_LOCATION  (uint8_t)(0x80)


/* LCD CHANNEL 0 */
#define LCD_CH_0                 (uint8_t)(0)
#define LCD_CH_0_RS_PORT         PORTC
#define LCD_CH_0_RS_PIN          PIN_5
#define LCD_CH_0_RW_PORT         PORTC
#define LCD_CH_0_RW_PIN          PIN_6
#define LCD_CH_0_E_PORT          PORTC
#define LCD_CH_0_E_PIN           PIN_7
#define LCD_CH_0_DATA_PORT       PORTD
#define LCD_CH_0_DATA_START_PIN  PIN_4


#endif /* __LCD_CONFIG_H__ */