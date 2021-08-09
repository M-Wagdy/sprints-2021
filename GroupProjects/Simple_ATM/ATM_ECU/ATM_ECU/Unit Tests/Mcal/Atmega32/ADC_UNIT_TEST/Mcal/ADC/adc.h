#ifndef _ADC_H_
#define _ADC_H_
/*- INCLUDES ----------------------------------------------*/
#include"../../Infrastructure/TypeDef.h"
#include"../../Infrastructure/Macros.h"
#include"adcConfig.h"
#include"adcRetVal.h"
/*- MACROS -----------------------------------*/
#define ADC0_CH0     (uint8_t)0
#define ADC0_CH1     (uint8_t)1
#define ADC0_CH2     (uint8_t)2
#define ADC0_CH3     (uint8_t)3
#define ADC0_CH4     (uint8_t)4
#define ADC0_CH5     (uint8_t)5
#define ADC0_CH6     (uint8_t)6
#define ADC0_CH7     (uint8_t)7
/*- APIs DECLARATIONS -----------------------------------*/
ADC_ERROR_state_t ADC_Init(uint8_t ACD_CH);
ADC_ERROR_state_t ADC_StartSingleConversion(uint8_t ADC_Ch);
ADC_ERROR_state_t ADC_Read(uint8_t ADC_Ch, uint16_t*ADC_DATA);
ADC_ERROR_state_t ADC_EnInterrupt(void);
ADC_ERROR_state_t ADC_DisInterrupt(void);
ADC_ERROR_state_t ADC_SetCallback(Ptr_VoidFuncVoid_t Callback);
#endif /*_ADC_H_*/
