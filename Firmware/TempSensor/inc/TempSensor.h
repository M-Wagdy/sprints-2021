/*
 * TempSensor.h
 *
 * Created: 8/22/2021 2:00:35 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __TEMP_SESNOR_H__
#define __TEMP_SESNOR_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_types.h"
#include "ADC.h"
#include "TempSensor_Lcfg.h"

/*- MACROS -------------------------------------------------*/
/* Temp Sensor Channels */
#define  TEMP_0                     (uint8_t)( 0 )
#define  TEMP_INVALID_CH            (uint8_t)( 1 )

/*- FUNCTION DECLARATIONS ----------------------------------*/

/* Initialize a Temperature Sensor */
ERROR_STATE_t TEMP_Init(uint8_t TEMP_CH);

/* Read Temperature. */
ERROR_STATE_t TEMP_Read(uint8_t TEMP_CH, uint8_t * TempData);

#endif /* __TEMP_SESNOR_H__ */