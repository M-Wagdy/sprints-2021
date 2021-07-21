/*
 * ADC_Config.h
 *
 * Created: 7/21/2021 6:23:12 PM
 *  Author: Mohamed Wagdy
 */


#ifndef __ADC_CONFIG_H__
#define __ADC_CONFIG_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../Infrastructure/STD_types.h"

/*- MACROS -------------------------------------------------*/
#define ADC_ENABLE                     (uint8_t)(0X80)
#define ADC_AUTO_TRIGGER_EN            (uint8_t)(0X20)
#define ADC_INTERRUPT_EN               (uint8_t)(0X08)

#define ADC_START_CONVERSION           (uint8_t)(0X40)
#define ADC_INTERRUPT_FLAG             (uint8_t)(0X10)

#define ADC_PRESCALAR_1                (uint8_t)(0X00)
#define ADC_PRESCALAR_2                (uint8_t)(0X01)
#define ADC_PRESCALAR_4                (uint8_t)(0X02)
#define ADC_PRESCALAR_8                (uint8_t)(0X03)
#define ADC_PRESCALAR_16               (uint8_t)(0X04)
#define ADC_PRESCALAR_32               (uint8_t)(0X05)
#define ADC_PRESCALAR_64               (uint8_t)(0X06)
#define ADC_PRESCALAR_128              (uint8_t)(0X07)

#define ADC_VREF_OFF                   (uint8_t)(0X00)
#define ADC_VREF_AVCC                  (uint8_t)(0X40)
#define ADC_VREF_INTERNAL              (uint8_t)(0XC0)

#define ADC_CH_0                       (uint8_t)(0)
#define ADC_CH_1                       (uint8_t)(1)
#define ADC_CH_2                       (uint8_t)(2)
#define ADC_CH_3                       (uint8_t)(3)
#define ADC_CH_4                       (uint8_t)(4)
#define ADC_CH_5                       (uint8_t)(5)
#define ADC_CH_6                       (uint8_t)(6)
#define ADC_CH_7                       (uint8_t)(7)

#define ADC_REFERENCE_SELECTION        (ADC_VREF_AVCC)
#define ADC_CONTROL_MASK               (ADC_ENABLE | ADC_PRESCALAR_2)

#endif /* __ADC_CONFIG_H__ */