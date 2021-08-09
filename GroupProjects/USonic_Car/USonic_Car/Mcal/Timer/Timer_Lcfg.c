/*
 * Timer_Lcfg.c
 *
 * Created: 8/9/2021 12:43:25 PM
 *  Author: Mohamed Wagdy
 */ 


/*- INCLUDES
----------------------------------------------*/
#include "Timer_Cfg.h"


const STR_TIMER_config_t gastr_Timer_Config[TIMERS_NUMBER] = {
  {NORMAL_MODE, DEFAULT_INTERRUPT, CLK_64_PRESCALE},
  {DEFAULT_MODE, DEFAULT_INTERRUPT, CLK_DEFAULT},
  {NORMAL_MODE, NO_INTERRUPT, T2_CLK_64_PRESCALE}
};