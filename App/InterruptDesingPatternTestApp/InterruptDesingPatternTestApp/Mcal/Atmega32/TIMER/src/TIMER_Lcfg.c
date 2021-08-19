/*
 * TIMER_Lcfg.c
 *
 * Created: 8/9/2021 12:43:25 PM
 *  Author: Mohamed Wagdy
 */ 


/*- INCLUDES
----------------------------------------------*/
#include "TIMER_Lcfg.h"

const STR_TIMER_config_t gastr_Timer_Config[TIMERS_NUMBER] = {
  {DEFAULT_MODE, DEFAULT_INTERRUPT, CLK_DEFAULT},
  {DEFAULT_MODE, DEFAULT_INTERRUPT, CLK_DEFAULT},
  {NORMAL_MODE, TIMER_2_OVERFLOW_INTERRUPT, T2_CLK_1024_PRESCALE}
};