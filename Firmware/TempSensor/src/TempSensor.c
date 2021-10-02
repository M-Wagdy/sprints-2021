/*
 * TempSensor.c
 *
 * Created: 8/22/2021 2:00:35 PM
 *  Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "TempSensor.h"

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern const STR_TEMP_config_t gastr_Temp_Config[TEMPS_NUMBER];

/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function configures a Temperature Sensor Channel.
*
* @param [in]  TEMP_CH -  Temperature channel number.
*
* @return function error state.
*/
ERROR_STATE_t TEMP_Init(uint8_t TEMP_CH)
{
   ERROR_STATE_t Temp_ErrorState;
   
   if(TEMP_CH >= TEMP_INVALID_CH)
   {
      Temp_ErrorState = ERROR_NOK;
   }
   else
   {
      ADC_Init();
      Temp_ErrorState = ERROR_OK;
   }
   
   return Temp_ErrorState;
}

/**
* @brief: This function Reads Temperature Value.
*
* @param [in]  TEMP_CH  -  Temperature channel number.
* @param [out] TempData -  Address Pointing to where to store the Temperature readings.
*
* @return function error state.
*/
ERROR_STATE_t TEMP_Read(uint8_t TEMP_CH, uint8_t * TempData)
{
   ERROR_STATE_t Temp_ErrorState;
   if(TEMP_CH >= TEMP_INVALID_CH)
   {
      Temp_ErrorState = ERROR_NOK;
   }
   else
   {
      uint16_t u16_ADCReadings;
      Temp_ErrorState = ADC_Read(gastr_Temp_Config[TEMP_CH].u8_ADCCh, &u16_ADCReadings);
      
      if(ERROR_OK == Temp_ErrorState)
      {
         /* map ADC resolution to the current temprature */
         *TempData = (
            u16_ADCReadings * gastr_Temp_Config[TEMP_CH].u8_TempHighestValue /
            gastr_Temp_Config[TEMP_CH].u8_TempHighValueDigital
         );
      }
      else
      {
         Temp_ErrorState = ERROR_NOK;
      }
   }
   
   return Temp_ErrorState;
}