/*INCLUDES
 ---------------------------------*/

#include "adc.h"
#include"adcReg.h"

/*GLOBAL STATIC VARIABLE
 ----------------------------*/
//POINTER TO void func(void) TO BE CALLED IN ADC_ISR
uint8_t gu8_InitFlag = NOT_INIT;
Ptr_VoidFuncVoid_t G_ADC_CALLBACK=NULL_PTR;

/*- LOCAL MACROS
 ------------------------------------------*/
//ADC Multiplexer SelectionRegister – ADMUX
#define REFS1 (uint8_t)7
#define REFS0 (uint8_t)6
#define ADLAR (uint8_t)5
#define MUX4  (uint8_t)4
#define MUX3  (uint8_t)3
#define MUX2  (uint8_t)2
#define MUX1  (uint8_t)1
#define MUX0  (uint8_t)0

//ADC Control and Status Register A – ADCSRA
#define ADEN  (uint8_t)7 //ADC Enable
#define ADSC  (uint8_t)6 //Start Single Conversion
#define ADATE (uint8_t)5 //ADC Auto trigger Enable
#define ADIF  (uint8_t)4 //ADC interrupt Flag
#define ADIE  (uint8_t)3 //ADC interrupt Enable
#define ADPS2 (uint8_t)2 //ADPS2 Along with ADPS1 and ADPS0 are the ADC Prescaler Select Bits
#define ADPS1 (uint8_t)1
#define ADPS0 (uint8_t)0

//PRESCLAER
#define Division_Factor_0   	(uint8_t)0x00   //0b00000000
#define Division_Factor_2   	(uint8_t)0x01   //0b0000 0001
#define Division_Factor_4   	(uint8_t)0x02	//0b0000 0010
#define Division_Factor_8   	(uint8_t)0x03	//0b0000 0011
#define Division_Factor_16  	(uint8_t)0x04	//0b0000 0100
#define Division_Factor_32  	(uint8_t)0x05	//0b0000 0101
#define Division_Factor_64  	(uint8_t)0x06	//0b0000 0110
#define Division_Factor_128     (uint8_t)0x07	//0b0000 0111

//VOLTAGE SOURRCES
#define VrefExternal_Source     (uint8_t)0x00   //0b0000 0000
#define VrefInternal_source_5V  (uint8_t)0x40   //0b0100 0000
#define VrefInternal_source_2V  (uint8_t)0xC0   //0b1100 0000
//ADJUSTING
#define ADC_ADJUST_RIGHT        (uint8_t)0x00
#define ADC_ADJUST_LEFT         (uint8_t)0x20
//TRRIGGERING SOURCES
#define FreeRunningMode		    (uint8_t)0x00
#define AnalogComparator	    (uint8_t)0x20
#define EX_INT0                 (uint8_t)0x40
#define Timer0CmprMth           (uint8_t)0x60
#define Timer0OvrFlw            (uint8_t)0x80
#define Timer0CmprMthB          (uint8_t)0xA0
#define Timer1OvrFlw            (uint8_t)0xC0
#define Timer1CprEvent          (uint8_t)0xE0


/*- APIs IMPLEMENTATION
 -----------------------------------*/
/**************
 *INIT THE ADC*
 **************/
ADC_ERROR_state_t ADC_Init(uint8_t ACD_CH) {
	uint8_t au8_ERROR_STAT=ADC_SUCCESS;//ERRROR STAT HAS A SUCCESS VALUE AS DEFAULT
	if (INIT==gu8_InitFlag){
		au8_ERROR_STAT=ADC_SEC_INIT;
	}
	else if (NOT_INIT==gu8_InitFlag){
	/*Enable the ADC*/
	Set_Bit(ADCSRA, ADEN);
	/*Set the prescaler*/
	ADCSRA |= ADC_PRESCALER;
	/*Set the voltage Ref.*/
	ADMUX |= ADC_Voltage_Ref;
	/*Adjust left or right*/
	ADMUX |= ADC_ADJUST;
	/*Set the Auto trigger*/
#if ADC_AUTO_TRIGGER
	Set_Bit(ADCSRA, ADATE);//IF AUTO TRIGGER IS ON
	SFIOR |= ADC_AUTO_TRIGGER_SOURCE; //SET THE AUTO TRIGGER SOURCE
#else
	Clr_Bit(ADCSRA,ADATE);//IF AUTO TRRIGGERR IS OFF
#endif
	}
	else{
	//DO NOTHING
	}
	gu8_InitFlag=INIT;
	return au8_ERROR_STAT;
}
/***************************
 *START A SINGLE CONVERSION*
 ***************************/
ADC_ERROR_state_t ADC_StartSingleConversion(uint8_t ADC_Ch) {
	uint8_t au8_ERROR_STAT=ADC_SUCCESS;//ERRROR STAT HAS A SUCCESS VALUE AS DEFAULT
	if(NOT_INIT==gu8_InitFlag){
		au8_ERROR_STAT=ADC_NOT_INIT;
	}
	else if (INIT==gu8_InitFlag){
	/*Select the ADC channel*/
	ADMUX |= ADC_Ch;
	/*Start Single Conversion*/
	Set_Bit(ADCSRA, ADSC);
	}
	else{
		//DO NOTHING
	}
	return au8_ERROR_STAT;
}
ADC_ERROR_state_t ADC_Read(uint8_t ADC_Ch, uint16_t *  ADC_DATA) {
	uint8_t au8_ERROR_STAT=ADC_SUCCESS;//ERRROR STAT HAS A SUCCESS VALUE AS DEFAULT
#if (!ADC_AUTO_TRIGGER)//In case ADC NOT WORKING IN AUTO TRIGGERING MODE START THE CONVERSION
	ADC_StartSingleConversion(ADC_Ch);
#endif
	//MAKE SURE THE POINTER PASSED TO FUNCTION IS NOT NULL
	if(NULL_PTR==ADC_DATA){
		au8_ERROR_STAT=ADC_NULL_POINTER;
	}
	//IF ADC IS NOT  INITIALIZED
	if(NOT_INIT==gu8_InitFlag){
		au8_ERROR_STAT=ADC_NOT_INIT;
	}
	else if (INIT==gu8_InitFlag){
    /*wait for the conversion*/
	while (!Get_Bit(ADCSRA, ADIF))
		;
     /*ADC Flag Clear*/
	Set_Bit(ADCSRA, ADIF);
	/*Return the value*/
	*ADC_DATA = ADC;
	}
	else{
        //DO NOTHING
	}
	return au8_ERROR_STAT;
}
ADC_ERROR_state_t ADC_EnInterrupt(void){
	uint8_t au8_ERROR_STAT=ADC_SUCCESS;//ERRROR STAT HAS A SUCCESS VALUE AS DEFAULT
	//IF ADC IS NOT  INITIALIZED
	if(NOT_INIT==gu8_InitFlag){
		au8_ERROR_STAT=ADC_NOT_INIT;
	}
	//MAKE SURE ADC IS INITIALIZED
	else if (INIT==gu8_InitFlag){
	Set_Bit(ADCSRA, ADIE);
	}
	else{
		//DO NOTHING
	}
	return au8_ERROR_STAT;
}
ADC_ERROR_state_t ADC_DisInterrupt(void){
	uint8_t au8_ERROR_STAT=ADC_SUCCESS;//ERRROR STAT HAS A SUCCESS VALUE AS DEFAULT
	//IF ADC IS NOT  INITIALIZED
	if(NOT_INIT==gu8_InitFlag){
		au8_ERROR_STAT=ADC_NOT_INIT;
	}
	//MAKE SURE ADC IS INITIALIZED
	else if (INIT==gu8_InitFlag){
	Clr_Bit(ADCSRA, ADIE);
	}
	else{
		//DO NOTHING
	}
	return au8_ERROR_STAT;
}
ADC_ERROR_state_t ADC_SetCallback(Ptr_VoidFuncVoid_t Callback){
	uint8_t au8_ERROR_STAT=0;
	//MAKE SURE THE POINTER PASSED TO FUNCTION IS NOT NULL
	if(NULL_PTR==Callback){
		au8_ERROR_STAT=ADC_NULL_POINTER;
	}
	//IF ADC IS NOT  INITIALIZED
	if(NOT_INIT==gu8_InitFlag){
		au8_ERROR_STAT=ADC_NOT_INIT;
	}
	//MAKE SURE ADC IS INITIALIZED
	else if (INIT==gu8_InitFlag){
		//ASSIGN THE FUNCTION TO THE POINTER
		G_ADC_CALLBACK=Callback;
	}
	else{
		//DO NOTHING
	}
	//RETURN THE ERROR STAT IF IT'S = 0 THEN SUCCESS
	return au8_ERROR_STAT;
}

void __vector_16 (void) __attribute__((signal));

void __vector_16(void) {
	G_ADC_CALLBACK();
}
