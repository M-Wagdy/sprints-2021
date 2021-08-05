#ifndef _ADC_REG_H_
#define _ADC_REG_H_


#define ADMUX     *( ( volatile uint8_t* ) 0x27 )
#define ADCSRA    *( ( volatile uint8_t* ) 0x26 )
#define ADCL      *( ( volatile uint8_t* ) 0x24 )
#define ADCH      *( ( volatile uint8_t* ) 0x25 )
#define ADC       *( ( volatile uint16_t*) 0x24 )
#define SFIOR     *( ( volatile uint8_t* ) 0x50 )

#endif /*_ADC_REG_H_*/
