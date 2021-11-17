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
  {GPT_CH0, GPT_CH_MODE_CONTINUOUS, GPT_CH_FREQ_125KHZ, 1000000, T0_Callback},
  {GPT_CH1, GPT_CH_MODE_ONESHOT, GPT_CH_FREQ_16MHZ, 0, NULL_PTR},
  {GPT_CH2, GPT_CH_MODE_ONESHOT, GPT_CH_FREQ_16MHZ, 0, NULL_PTR},
  {GPT_CH3, GPT_CH_MODE_ONESHOT, GPT_CH_FREQ_16MHZ, 0, NULL_PTR},
  {GPT_CH4, GPT_CH_MODE_ONESHOT, GPT_CH_FREQ_16MHZ, 0, NULL_PTR},
  {GPT_CH5, GPT_CH_MODE_ONESHOT, GPT_CH_FREQ_16MHZ, 0, NULL_PTR},
  {GPT_CH6, GPT_CH_MODE_ONESHOT, GPT_CH_FREQ_16MHZ, 0, NULL_PTR},
  {GPT_CH7, GPT_CH_MODE_ONESHOT, GPT_CH_FREQ_16MHZ, 0, NULL_PTR},
  {GPT_CH8, GPT_CH_MODE_ONESHOT, GPT_CH_FREQ_16MHZ, 0, NULL_PTR},
  {GPT_CH9, GPT_CH_MODE_ONESHOT, GPT_CH_FREQ_16MHZ, 0, NULL_PTR},
  {GPT_CH10, GPT_CH_MODE_ONESHOT, GPT_CH_FREQ_16MHZ, 0, NULL_PTR},
  {GPT_CH11, GPT_CH_MODE_ONESHOT, GPT_CH_FREQ_16MHZ, 0, NULL_PTR},
};
