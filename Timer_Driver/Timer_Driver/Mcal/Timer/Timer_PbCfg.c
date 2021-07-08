/*
 * Timer_PbCfg.c
 *
 * Created: 7/8/2021 1:33:54 PM
 *  Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "Timer_Pbcfg.h"

/* struct containing all DIO pins configurations. */
const STR_TIMER_config_t gastr_TIMER_configurations[TIMERS_NUMBER] = {
   {TIMER_0, CLK_125_KHZ, NORMAL_MODE, NO_INTERRUPT},
   {TIMER_2, CLK_DEFAULT, DEFAULT_MODE, DEFAULT_INTERRUPT}
};