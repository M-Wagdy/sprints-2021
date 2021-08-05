#include "temp.h"

uint8_t TEMP_Init(uint8_t Temp_ch) {
	switch (Temp_ch) {
	case TEMP_CH_0 :
		ADC_Init(ADC0_CH0);
		break;
	case TEMP_CH_1 :
		ADC_Init(ADC0_CH1);
		break;
	case TEMP_CH_2 :
		ADC_Init(ADC0_CH2);
		break;
	case TEMP_CH_3 :
		ADC_Init(ADC0_CH3);
		break;
	case TEMP_CH_4 :
		ADC_Init(ADC0_CH4);
		break;
	case TEMP_CH_5 :
		ADC_Init(ADC0_CH5);
		break;
	case TEMP_CH_6 :
		ADC_Init(ADC0_CH6);
		break;
	case TEMP_CH_7 :
		DIO_SetPinDirection(PORTA,PIN7,PIN_INPUT);
		ADC_Init(ADC0_CH7);
		break;
	default:
		break;
	}
	return 0;
}
uint8_t TEMP_GetTemp(uint8_t Temp_ch, uint8_t* temp) {
	uint16_t ADC_READ=0;
	switch (Temp_ch) {
		case TEMP_CH_0 :
			ADC_Read(ADC0_CH0,&ADC_READ);
			ADC_READ=((((uint32_t)ADC_READ)*(150))/ADC1_RESLUATION);
			*(temp)=(uint8_t)ADC_READ;
			break;
		case TEMP_CH_1 :
			ADC_Read(ADC0_CH1,&ADC_READ);
			break;
		case TEMP_CH_2 :
			ADC_Read(ADC0_CH2,&ADC_READ);
			break;
		case TEMP_CH_3 :
			ADC_Read(ADC0_CH3,&ADC_READ);
			break;
		case TEMP_CH_4 :
			ADC_Read(ADC0_CH4,&ADC_READ);
			break;
		case TEMP_CH_5 :
			ADC_Read(ADC0_CH5,&ADC_READ);
			break;
		case TEMP_CH_6 :
			ADC_Read(ADC0_CH6,&ADC_READ);
			break;
		case TEMP_CH_7 :
			ADC_Read(ADC0_CH7,&ADC_READ);
			ADC_READ=((((uint32_t)ADC_READ)*(150))/ADC1_RESLUATION);
			*(temp)=(uint8_t)ADC_READ;
			break;
		default:
			break;
		}

	return 0;
}
