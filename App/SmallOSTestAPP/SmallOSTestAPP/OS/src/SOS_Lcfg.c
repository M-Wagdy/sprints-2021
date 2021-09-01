/*
 * SOS_Lcfg.c
 *
 * Created: 8/28/2021 3:22:02 PM
 * Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "SOS_Lcfg.h"

const STR_SYSTICK_config_t gstr_SYSTICK_Config = {DEFAULT_MODE, DEFAULT_INTERRUPT, CLK_NO_PRESCALE};

/* Tick Time in Microseconds. */
const uint16_t gu16_TICK_Interval = 1000;