/*
 * DIO_Registers.h
 *
 * Created: 7/7/2021 1:49:29 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __DIO_REGISTERS_H__
#define __DIO_REGISTERS_H__

/*- PORTA REGISTERS-----------------------------------------*/
#define  PORTA_DATA      (*((volatile uint8_t *) (0x3B)))
#define  PORTA_DIR       (*((volatile uint8_t *) (0x3A)))
#define  PORTA_STAT      (*((volatile uint8_t *) (0x39)))

/*- PORTB REGISTERS-----------------------------------------*/
#define  PORTB_DATA      (*((volatile uint8_t *) (0x38)))
#define  PORTB_DIR       (*((volatile uint8_t *) (0x37)))
#define  PORTB_STAT      (*((volatile uint8_t *) (0x36)))

/*- PORTC REGISTERS-----------------------------------------*/
#define  PORTC_DATA      (*((volatile uint8_t *) (0x35)))
#define  PORTC_DIR       (*((volatile uint8_t *) (0x34)))
#define  PORTC_STAT      (*((volatile uint8_t *) (0x33)))

/*- PORTD REGISTERS-----------------------------------------*/
#define  PORTD_DATA      (*((volatile uint8_t *) (0x32)))
#define  PORTD_DIR       (*((volatile uint8_t *) (0x31)))
#define  PORTD_STAT      (*((volatile uint8_t *) (0x30)))

/*- PINS PULL UP REGISTER-----------------------------------*/
#define PORTS_PULL_UP    (*((volatile uint8_t *) (0x50)))

#endif /* __DIO_REGISTERS_H__ */