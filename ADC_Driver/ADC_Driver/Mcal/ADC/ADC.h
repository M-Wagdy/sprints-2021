/*
 * ADC.h
 *
 * Created: 7/21/2021 6:25:50 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __ADC_H__
#define __ADC_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../Infrastructure/STD_types.h"
#include "ADC_Registers.h"
#include "ADC_retval.h"
#include "ADC_Config.h"

/*- FUNCTION DECLARATIONS ----------------------------------*/

/* Initialize ADC */
ADC_ERROR_state_t ADC_Init(void);

/* Read ADC Channel */
ADC_ERROR_state_t ADC_Read(uint8_t ADC_CH, uint16_t * Data);

/* Enable Interrupt */
ADC_ERROR_state_t ADC_EnableInterrupt(void);

/* Disable Interrupt */
ADC_ERROR_state_t ADC_DisableInterrupt(void);

/* Set Callback Function */
ADC_ERROR_state_t ADC_SetCallback(Ptr_VoidFuncVoid_t Callback);

#endif /* __ADC_H__ */