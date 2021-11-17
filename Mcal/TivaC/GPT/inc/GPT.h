/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  GPT.h
 *       Module:  GPT
 *
 *  Description:  header file for GPT module.
 *  
 *********************************************************************************************************************/
#ifndef __GPT_H__
#define __GPT_H__

/*- INCLUDES -----------------------------------------------*/
#include "GPT_Cfg.h"
#include "GPT_Lcfg.h"
#include "Std_Types.h"

/*- CONSTANTS ----------------------------------------------*/
/*- ERRORS DEFINITIONS--------------------------------------*/

/**
* @brief: Module ID.
*/
#define           E_GPT_ID                      (Std_ReturnType)( 0x00 )


/**
* @brief: This return value indicate that a function got an
* invalid value.
*/
#define           E_GPT_INVALID_VALUE           (Std_ReturnType)( 1 )

/**
* @brief: This return value indicate that the module was
* initialized before.
*/
#define           E_GPT_INIT_BEFORE             (Std_ReturnType)( 2 )

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/
/* Initializes the GPT module and Start Preconfig timers. */
extern void Gpt_Init(const Gpt_ConfigType* ConfigPtr);

/* Disable GPT Notification. */
extern void Gpt_DisableNotification(Gpt_ChannelType Channel);

/* Enable GPT Notification. */
extern void Gpt_EnableNotification (Gpt_ChannelType Channel);

/* Start Timer Channel. */
extern void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value);

/* Stop Timer Channel. */
extern void Gpt_StopTimer(Gpt_ChannelType Channel);

/* Get Timer Channel Elapsed Time. */
extern Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel);

/* Get Timer Channel Remaining Time. */
extern Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel);

/* Get Predefined Timer Ticks Value. */
extern Std_ReturnType Gpt_GetPredefTimerValue(Gpt_PredefTimerType PredefTimer, uint32_t* TimeValuePtr);

#endif  /* __GPT_H__ */
