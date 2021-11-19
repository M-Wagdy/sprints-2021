/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  ADC_Lcfg.h
 *       Module:  ADC
 *
 *  Description:  header file for ADC module linking configurations.
 *
 *********************************************************************************************************************/
#ifndef __ADC_LCFG_H__
#define __ADC_LCFG_H__

/*- INCLUDES -----------------------------------------------*/
#include "ADC_Cfg.h"
#include "Std_Types.h"

/*- CONSTANTS ----------------------------------------------*/
#define ADC_CONFIGURED_CHS  (uint8_t)(12)

/* ADC Channels */
#define ADC_CH0                 (Adc_ChannelType)(0)
#define ADC_CH1                 (Adc_ChannelType)(1)
#define ADC_CH2                 (Adc_ChannelType)(2)
#define ADC_CH3                 (Adc_ChannelType)(3)
#define ADC_CH4                 (Adc_ChannelType)(4)
#define ADC_CH5                 (Adc_ChannelType)(5)
#define ADC_CH6                 (Adc_ChannelType)(6)
#define ADC_CH7                 (Adc_ChannelType)(7)
#define ADC_CH8                 (Adc_ChannelType)(8)
#define ADC_CH9                 (Adc_ChannelType)(9)
#define ADC_CH10                (Adc_ChannelType)(10)
#define ADC_CH11                (Adc_ChannelType)(11)
#define ADC_INVALID_CH          (Adc_ChannelType)(12)

/* ADC Groups */
#define ADC_GROUP0              (Adc_GroupType)(0)
#define ADC_GROUP1              (Adc_GroupType)(1)
#define ADC_GROUP2              (Adc_GroupType)(2)
#define ADC_GROUP3              (Adc_GroupType)(3)
#define ADC_INVALID_GROUP       (Adc_GroupType)(4)

/* ADC Groups Priorities */
#define ADC_GROUP_PRI0          (Adc_GroupPriorityType)(0)
#define ADC_GROUP_PRI1          (Adc_GroupPriorityType)(1)
#define ADC_GROUP_PRI2          (Adc_GroupPriorityType)(2)
#define ADC_GROUP_PRI3          (Adc_GroupPriorityType)(3)
#define ADC_INVALID_PRIORITY    (Adc_GroupPriorityType)(4)

/* ADC Trigger Modes */
#define ADC_TRIGG_SRC_HW        (Adc_TriggerSourceType)(0)
#define ADC_TRIGG_SRC_SW        (Adc_TriggerSourceType)(1)

/* ADC Conversion Modes */
#define ADC_CONV_MODE_CONTINUOUS    (Adc_GroupConvModeType)(0)
#define ADC_CONV_MODE_ONESHOT       (Adc_GroupConvModeType)(1)

/* ADC Stream Buffer Modes */
#define ADC_STREAM_BUFFER_CIRCULAR  (Adc_StreamBufferModeType)(0)
#define ADC_STREAM_BUFFER_LINEAR    (Adc_StreamBufferModeType)(1)

/* ADC Status */
#define ADC_STATUS_NOT_INIT         (Adc_StatusType)(0)
#define ADC_STATUS_BUSY             (Adc_StatusType)(1)
#define ADC_STATUS_NOT_RUNNING      (Adc_StatusType)(2)
#define ADC_STATUS_READY            (Adc_StatusType)(3)
#define ADC_STATUS_INVALID_GROUP    (Adc_StatusType)(4)

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct Adc_ConfigType{
   Adc_ChannelType AdcChannelId;
   Adc_GroupType AdcGroupId;
   Adc_GroupPriorityType AdcGroupPriority;
   Adc_TriggerSourceType AdcGroupTriggSrc;
   Adc_GroupConvModeType AdcGroupConversionMode;
   Ptr_VoidFuncVoid_t AdcNotification;
   Adc_StreamBufferModeType AdcStreamingBufferMode;
   Adc_StreamNumSampleType AdcStreamingNumSamples;
} Adc_ConfigType;

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/

#endif  /* __ADC_LCFG_H__ */
