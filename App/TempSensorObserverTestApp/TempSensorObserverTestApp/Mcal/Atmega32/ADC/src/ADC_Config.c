/*
 * ADC_Config.c
 *
 * Created: 8/3/2021 11:58:46 AM
 *  Author: Mohamed Wagdy
 */ 
/*- INCLUDES
----------------------------------------------*/
#include "ADC_Config.h"

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
const uint8_t ADC_REFERENCE_SELECTION = (ADC_VREF_AVCC);
const uint8_t ADC_CONTROL_MASK = (ADC_ENABLE | ADC_PRESCALAR_2);
