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



#endif /*_ADCCONFIG_H_*/
