#ifndef _ADCCONFIG_H_
#define _ADCCONFIG_H_


/*This macro controls the ADC prescaler (Choose a freq. between 50-200khz)
 -Presscaler 2  -> Division_Factor_2
 -Presscaler 4  -> Division_Factor_4
 -Presscaler 8  -> Division_Factor_8
 -Presscaler 16 -> Division_Factor_16
 -Presscaler 32 -> Division_Factor_32
 -Presscaler 64 -> Division_Factor_64
 -Presscaler 128-> Division_Factor_128
 * */
#define ADC_PRESCALER Division_Factor_2



/*This Macro sets the voltage ref.
 * For external Voltage ref.         -> VrefExternal_Source
 * For internal (5V) Voltage ref.    -> VrefInternal_source_5V
 * For internal (2.56V) Voltage ref. -> VrefInternal_source_2V
 * */
#define ADC_Voltage_Ref  VrefExternal_Source

/*This macro controls the adjust of the bits
 * -For left adjust -> ADC_ADJUST_LEFT
 * -For Right adjust -> ADC_ADJUST_RIGHT (This is the default )
 * */
#define ADC_ADJUST                      ADC_ADJUST_RIGHT


/*This macro select the source of the auto trigger(auto trigger must be set)
 * For Free Running mode             -> FreeRunningMode
 * For Analog Comparator mode        -> AnalogComparator
 * For External Interrupt(Ch_0) mode -> EX_INT0
 * For Timer 0 compare match mode    -> Timer0CmprMth
 * For Timer 0 Overflow mode         -> Timer0OvrFlw
 * For Timer 1 compare match mode    -> Timer1OvrFlw
 * For Timer 1 Overflow mode         -> Timer1OvrFlw
 * For Timer 1 Capture Event mode    -> Timer1CprEvent
 * */
#define ADC_AUTO_TRIGGER_SOURCE             EX_INT0
/*This macro controls if auto trigger is on or off
 * To enable it  -> ON
 * To disable it -> OFF
 * If you choose not to enable the auto trigger then the ADC will start conversion manually
 * */
#define ADC_AUTO_TRIGGER                    OFF
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


#endif /*_ADCCONFIG_H_*/
