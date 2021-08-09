#ifndef _TEMP_SENSOR_H_
#define _TEMP_SENSOR_H_

#include "../../Infrastructure/STD_types.h"


#define VREF1_mV           (uint16_t)1500
#define ADC1_RESLUATION    (f32_t)307
#define STEPSIZE_TEMP1_mV  (uint16_t)10
#define TEMP1_MAX_VOLT_mV  (uint16_t)1500

#define TEMP_CH_0     (uint8_t)0
#define TEMP_CH_1     (uint8_t)1
#define TEMP_CH_2     (uint8_t)2
#define TEMP_CH_3     (uint8_t)3
#define TEMP_CH_4     (uint8_t)4
#define TEMP_CH_5     (uint8_t)5
#define TEMP_CH_6     (uint8_t)6
#define TEMP_CH_7     (uint8_t)7

uint8_t TEMP_Init(uint8_t Temp_ch);
uint8_t TEMP_GetTemp(uint8_t Temp_ch, uint8_t* temp);






#endif
