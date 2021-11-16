/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  GPT_Cfg.h
 *       Module:  GPT
 *
 *  Description:  header file for GPT module preprocessor configurations.
 *
 *********************************************************************************************************************/
#ifndef __GPT_CFG_H__
#define __GPT_CFG_H__

/*- INCLUDES -----------------------------------------------*/
#include "Std_Types.h"

/*- CONSTANTS ----------------------------------------------*/
#define GPT_CFG_NOT_CONCAT_BIT                  (uint8_t)(2)

#define GPT_ONESHOT_BIT                         (uint8_t)(0)
#define GPT_CONTINUOUS_BIT                      (uint8_t)(1)
#define GPT_DIR_BIT                             (uint8_t)(4)

#define GPT_CTL_EN_BIT                          (uint8_t)(0)
#define GPT_CTL_STALL_BIT                       (uint8_t)(1)

#define GPT_INT_EN_BIT                          (uint8_t)(0)

#define GPT_PREDEF_TIMER_100US_32BIT_EN         1
#define GPT_PREDEF_TIMER_1US_16BIT_EN           0
#define GPT_PREDEF_TIMER_1US_24BIT_EN           0
#define GPT_PREDEF_TIMER_1US_32BIT_EN           0

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef uint8_t Gpt_ChannelType;
typedef uint32_t Gpt_ValueType;
typedef uint8_t Gpt_ModeType;
typedef uint8_t Gpt_PredefTimerType;
#define GPT_PREDEF_TIMER_100US_32BIT            (Gpt_PredefTimerType)(0)
#define GPT_PREDEF_TIMER_1US_16BIT              (Gpt_PredefTimerType)(1)
#define GPT_PREDEF_TIMER_1US_24BIT              (Gpt_PredefTimerType)(2)
#define GPT_PREDEF_TIMER_1US_32BIT              (Gpt_PredefTimerType)(3)

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/

#endif  /* __GPT_CFG_H__ */
