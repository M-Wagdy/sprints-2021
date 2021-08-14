/*
 * DIO_Registers.h
 *
 * Created: 7/7/2021 1:49:29 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __DIO_REGISTERS_H__
#define __DIO_REGISTERS_H__

#define TEST 0

#if !TEST

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

#else
/*- PORTA REGISTERS-----------------------------------------*/
extern volatile uint8_t  PORTA_DATA;
extern volatile uint8_t  PORTA_DIR;
extern volatile uint8_t  PORTA_STAT;

/*- PORTB REGISTERS-----------------------------------------*/
extern volatile uint8_t  PORTB_DATA;
extern volatile uint8_t  PORTB_DIR;
extern volatile uint8_t  PORTB_STAT;

/*- PORTC REGISTERS-----------------------------------------*/
extern volatile uint8_t  PORTC_DATA;
extern volatile uint8_t  PORTC_DIR;
extern volatile uint8_t  PORTC_STAT;

/*- PORTD REGISTERS-----------------------------------------*/
extern volatile uint8_t  PORTD_DATA;
extern volatile uint8_t  PORTD_DIR;
extern volatile uint8_t  PORTD_STAT;

/*- PINS PULL UP REGISTER-----------------------------------*/
extern volatile uint8_t PORTS_PULL_UP;
#endif

#endif /* __DIO_REGISTERS_H__ */