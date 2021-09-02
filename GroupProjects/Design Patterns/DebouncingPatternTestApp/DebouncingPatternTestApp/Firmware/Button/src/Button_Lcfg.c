/*
 * Button_Lcfg.c
 *
 * Created: 8/21/2021 2:04:51 PM
 *  Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "Button_Lcfg.h"

const STR_BUTTON_config_t gastr_Button_Config[BUTTONS_NUMBER] = {
   {PORTB, PIN_2, PULL_UP},
};