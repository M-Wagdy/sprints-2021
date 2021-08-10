#ifndef __DIO_DRIVER_PRIV_H__
	#define __DIO_DRIVER_PRIV_H__
	
	/* Group A Registers */
	#define PORTA_Register  *((volatile uint8_t*)0x3B)
	#define DDRA_Register   *((volatile uint8_t*)0x3A)
	#define PINA_Register   *((volatile uint8_t*)0x39)
	
	/* Group B Registers */
	#define PORTB_Register  *((volatile uint8_t*)0x38)
	#define DDRB_Register   *((volatile uint8_t*)0x37)
	#define PINB_Register   *((volatile uint8_t*)0x36)
	
	/* Group C Registers */
	#define PORTC_Register  *((volatile uint8_t*)0x35)
	#define DDRC_Register   *((volatile uint8_t*)0x34)
	#define PINC_Register   *((volatile uint8_t*)0x33)
	
	/* Group D Registers */
	#define PORTD_Register  *((volatile uint8_t*)0x32)
	#define DDRD_Register   *((volatile uint8_t*)0x31)
	#define PIND_Register   *((volatile uint8_t*)0x30)
	
#endif	