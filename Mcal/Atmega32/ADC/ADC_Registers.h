/*
 * ADC_Registers.h
 *
 * Created: 7/21/2021 6:23:25 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __ADC_REGISTERS_H__
#define __ADC_REGISTERS_H__

#define TEST 0

#if !TEST
/*- ADC REGISTERS-----------------------------------------*/
#define  ADC_DATA_LOW_R                (*((volatile uint8_t *) (0x24)))
#define  ADC_DATA_HIGH_R               (*((volatile uint8_t *) (0x25)))
#define  ADC_MUX_R                     (*((volatile uint8_t *) (0x27)))
#define  ADC_CONTROL_AND_STATUS_R      (*((volatile uint8_t *) (0x26)))
#define  ADC_AUTO_TRIGGER_R            (*((volatile uint8_t *) (0x50)))

#else
/*- ADC REGISTERS-----------------------------------------*/
extern volatile uint8_t  ADC_DATA_LOW_R;
extern volatile uint8_t  ADC_DATA_HIGH_R;
extern volatile uint8_t  ADC_MUX_R;
extern volatile uint8_t  ADC_CONTROL_AND_STATUS_R;
extern volatile uint8_t  ADC_AUTO_TRIGGER_R;
#endif

#endif /* __ADC_REGISTERS_H__ */