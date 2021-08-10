#ifndef DIO_REG_H_
#define DIO_REG_H_

#define PORTA_DATA      *((volatile uint8_t*)0x3B)
#define PORTA_DIR       *((volatile uint8_t*)0x3A)
#define PORTA_STAT      *((volatile uint8_t*)0x39)

#define PORTB_DATA      *((volatile uint8_t*)0x38)
#define PORTB_DIR       *((volatile uint8_t*)0x37)
#define PORTB_STAT      *((volatile uint8_t*)0x36)

#define PORTC_DATA      *((volatile uint8_t*)0x35)
#define PORTC_DIR       *((volatile uint8_t*)0x34)
#define PORTC_STAT      *((volatile uint8_t*)0x33)

#define PORTD_DATA      *((volatile uint8_t*)0x32)
#define PORTD_DIR       *((volatile uint8_t*)0x31)
#define PORTD_STAT      *((volatile uint8_t*)0x30)



#endif /* DIO_REG_H_ */
