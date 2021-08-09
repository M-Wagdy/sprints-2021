#ifndef _ADC_REG_H_
#define _ADC_REG_H_

#define TESTING 1

#if !(TESTING)

#define ADMUX     *( ( volatile uint8_t* ) 0x27 )
#define ADCSRA    *( ( volatile uint8_t* ) 0x26 )
#define ADCL      *( ( volatile uint8_t* ) 0x24 )
#define ADCH      *( ( volatile uint8_t* ) 0x25 )
#define ADC       *( ( volatile uint16_t*) 0x24 )
#define SFIOR     *( ( volatile uint8_t* ) 0x50 )
#else
extern uint8_t ADMUX ;
extern uint8_t ADCSRA ;
extern uint8_t ADCL ;
extern uint8_t ADCH ;
extern uint8_t ADC ;
extern uint8_t SFIOR ;

#endif /*TESTING*/
#endif /*_ADC_REG_H_*/
