/*
 * Keypad_Config.c
 *
 * Created: 8/3/2021 12:34:34 PM
 *  Author: Mohamed Wagdy
 */
 /*- INCLUDES
 ----------------------------------------------*/
#include "Firmware/Keypad/Keypad_Config.h"

 /*- GLOBAL EXTERN VARIABLES
 -------------------------------*/
const uint8_t KP_CH_0_COL_PORT = PORTA;
const uint8_t KP_CH_0_COL_START_PIN = PIN_1;
const uint8_t KP_CH_0_ROW_PORT = PORTA;
const uint8_t KP_CH_0_ROW_START_PIN = PIN_4;

const uint8_t KP_CH_0_MAP[KP_CH_0_ROWS][KP_CH_0_COLS] = {
   {'1','2','3'},
   {'4','5','6'},
   {'7','8','9'},
   {'*','0','#'},
};