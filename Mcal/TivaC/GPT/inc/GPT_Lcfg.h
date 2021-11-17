/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  GPT_Lcfg.h
 *       Module:  GPT
 *
 *  Description:  header file for GPT module linking configurations.
 *
 *********************************************************************************************************************/
#ifndef __GPT_LCFG_H__
#define __GPT_LCFG_H__

/*- INCLUDES -----------------------------------------------*/
#include "GPT_Cfg.h"
#include "Std_Types.h"

/*- CONSTANTS ----------------------------------------------*/
/* GPT Channels */
#define GPT_CH0                 (Gpt_ChannelType)(0)
#define GPT_CH1                 (Gpt_ChannelType)(1)
#define GPT_CH2                 (Gpt_ChannelType)(2)
#define GPT_CH3                 (Gpt_ChannelType)(3)
#define GPT_CH4                 (Gpt_ChannelType)(4)
#define GPT_CH5                 (Gpt_ChannelType)(5)
#define GPT_CH6                 (Gpt_ChannelType)(6)
#define GPT_CH7                 (Gpt_ChannelType)(7)
#define GPT_CH8                 (Gpt_ChannelType)(8)
#define GPT_CH9                 (Gpt_ChannelType)(9)
#define GPT_CH10                (Gpt_ChannelType)(10)
#define GPT_CH11                (Gpt_ChannelType)(11)
#define GPT_INVALID_CH          (Gpt_ChannelType)(12)

#define GPT_CONFIGURED_GPT_CHS  (uint8_t)(12)

/* Gpt Channel Modes */
#define GPT_CH_MODE_CONTINUOUS  (Gpt_ModeType)(0)
#define GPT_CH_MODE_ONESHOT     (Gpt_ModeType)(1)

/* Gpt Channel Tick Frequency */
#define GPT_CH_FREQ_16MHZ       (Gpt_ValueType)(0)
#define GPT_CH_FREQ_8MHZ        (Gpt_ValueType)(1)
#define GPT_CH_FREQ_4MHZ        (Gpt_ValueType)(2)
#define GPT_CH_FREQ_1MHZ        (Gpt_ValueType)(3)
#define GPT_CH_FREQ_500KHZ      (Gpt_ValueType)(4)
#define GPT_CH_FREQ_250KHZ      (Gpt_ValueType)(5)
#define GPT_CH_FREQ_125KHZ      (Gpt_ValueType)(6)

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct Gpt_ConfigType{
   Gpt_ChannelType GptChannelId;
   Gpt_ModeType ChannelMode;
   Gpt_ValueType GptGptChannelTickFrequency;
   Gpt_ValueType GptChannelTickValueMax;
   Ptr_VoidFuncVoid_t GptNotification;
} Gpt_ConfigType;

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/

#endif  /* __GPT_LCFG_H__ */
