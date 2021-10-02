/*
 * TempSensor_Lcfg.h
 *
 * Created: 8/22/2021 2:01:35 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __TEMP_SENSOR_LCFG_H__
#define __TEMP_SENSOR_LCFG_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_TYPES.h"
#include "ADC_Config.h"

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct STR_TEMP_config_t{
   uint8_t u8_ADCCh;
   uint16_t u8_TempHighestValue;
   uint16_t u8_TempHighValueDigital;
} STR_TEMP_config_t;

/*- MACROS -------------------------------------------------*/
#define  TEMPS_NUMBER               (uint8_t)( 1 )

#endif /* __TEMP_SENSOR_LCFG_H__ */