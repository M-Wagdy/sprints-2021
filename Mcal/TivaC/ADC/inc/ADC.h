/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  ADC.h
 *       Module:  ADC
 *
 *  Description:  header file for ADC module.
 *  
 *********************************************************************************************************************/
#ifndef __ADC_H__
#define __ADC_H__

/*- INCLUDES -----------------------------------------------*/
#include "ADC_Cfg.h"
#include "ADC_Lcfg.h"
#include "Std_Types.h"

/*- CONSTANTS ----------------------------------------------*/
/*- ERRORS DEFINITIONS--------------------------------------*/

/**
* @brief: Module ID.
*/
#define           E_ADC_ID                      (Std_ReturnType)( 0xF0 )


/**
* @brief: This return value indicate that a function got an
* invalid value.
*/
#define           E_ADC_INVALID_VALUE           (Std_ReturnType)( 1 )

/**
* @brief: This return value indicate that the module was
* initialized before.
*/
#define           E_ADC_INIT_BEFORE             (Std_ReturnType)( 2 )

/**
* @brief: This return value indicate that the module received
* a null pointer.
*/
#define           E_ADC_NULL_PTR                (Std_ReturnType)( 3 )

/**
* @brief: This return value indicate that the module was
* not initialized.
*/
#define           E_ADC_NOT_INIT                (Std_ReturnType)( 4 )

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/
/* Initializes the ADC module. */
extern void Adc_Init(const Adc_ConfigType* ConfigPtr);

/* Initializes ADC driver with the group specific result buffer
 * start address where the conversion results will be stored. */
extern Std_ReturnType Adc_SetupResultBuffer(Adc_GroupType Group, Adc_ValueGroupType* DataBufferPtr);

/* Starts ADC Group Conversion. */
extern void Adc_StartGroupConversion(Adc_GroupType Group);

/* Stops ADC Group Conversion. */
extern void Adc_StopGroupConversion(Adc_GroupType Group);

/* Read ADC Group. */
extern Std_ReturnType Adc_ReadGroup(Adc_GroupType Group, Adc_ValueGroupType* DataBufferPtr);

/* Get ADC Group Status. */
extern Adc_StatusType Adc_GetGroupStatus(Adc_GroupType Group);

/* Get Pointer to Last entry in buffer. */
extern Adc_StreamNumSampleType Adc_GetStreamLastPointer(Adc_GroupType Group, Adc_ValueGroupType** PtrToSamplePtr);

/* Disable ADC Notification. */
extern void Adc_EnableGroupNotification(Adc_GroupType Group);

/* Enable ADC Notification. */
extern void Adc_DisableGroupNotification (Adc_GroupType Group);

#endif  /* __ADC_H__ */
