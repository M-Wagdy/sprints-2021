/*
 * Keypad_Config.h
 *
 * Created: 7/25/2021 4:46:46 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __KEYPAD_CONFIG_H__
#define __KEYPAD_CONFIG_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../Infrastructure/STD_types.h"

/*- MACROS -------------------------------------------------*/
#define KP_CH_0                  (uint8_t)(0)
#define KP_CH_0_ROWS             (uint8_t)(4)
#define KP_CH_0_COLS             (uint8_t)(3)
#define KP_CH_0_COL_PORT         PORTA
#define KP_CH_0_COL_START_PIN    PIN_1
#define KP_CH_0_ROW_PORT         PORTA
#define KP_CH_0_ROW_START_PIN    PIN_4

#endif /* __KEYPAD_CONFIG_H__ */