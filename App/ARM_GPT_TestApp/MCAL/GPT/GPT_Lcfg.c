/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  GPT_Lcfg.c
 *       Module:  GPT
 *
 *  Description:  source file for GPT module linking configurations.
 *
 *********************************************************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "GPT_Lcfg.h"

extern void T0_Callback(void);

const Gpt_ConfigType STR_GptConfig[GPT_CONFIGURED_GPT_CHS] = {
  {GPT_CH0, GPT_CH_MODE_CONTINUOUS, GPT_CH_FREQ_4MHZ, 1000000, T0_Callback},
};
