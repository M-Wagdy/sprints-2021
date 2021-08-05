/*
* registers.h
*
* Created: 7/8/2021 6:11:30 PM
*  Author: Marco
*/


#ifndef REGISTERS_H_
#define REGISTERS_H_

/******************************************************************************
*                              Includes			                          *
*******************************************************************************/
#include "types.h"

/******************************************************************************
*                              Constants			                          *
*******************************************************************************/

/*------------------------------ PORTA REGISTERS -----------------------------*/
#define PORTA_DATA  *((volatile uint8_t*) (0x3B))
#define PORTA_DIR   *((volatile uint8_t*) (0x3A))
#define PORTA_INPUT *((volatile uint8_t*) (0x39))

#define PORTA  *((volatile uint8_t*) (0x3B))
#define DDRA   *((volatile uint8_t*) (0x3A))
#define PINA   *((volatile uint8_t*) (0x39))

/*------------------------------ PORTB REGISTERS -----------------------------*/
#define PORTB_DATA  *((volatile uint8_t*) (0x38))
#define PORTB_DIR   *((volatile uint8_t*) (0x37))
#define PORTB_INPUT *((volatile uint8_t*) (0x36))

#define PORTB  *((volatile uint8_t*) (0x38))
#define DDRB   *((volatile uint8_t*) (0x37))
#define PINB   *((volatile uint8_t*) (0x36))

/*------------------------------ PORTC REGISTERS -----------------------------*/
#define PORTC_DATA  *((volatile uint8_t*) (0x35))
#define PORTC_DIR   *((volatile uint8_t*) (0x34))
#define PORTC_INPUT *((volatile uint8_t*) (0x33))

#define PORTC  *((volatile uint8_t*) (0x35))
#define DDRC   *((volatile uint8_t*) (0x34))
#define PINC *((volatile uint8_t*) (0x33))

/*------------------------------ PORTD REGISTERS -----------------------------*/
#define PORTD_DATA  *((volatile uint8_t*) (0x32))
#define PORTD_DIR   *((volatile uint8_t*) (0x31))
#define PORTD_INPUT *((volatile uint8_t*) (0x30))

#define PORTD  *((volatile uint8_t*) (0x32))
#define DDRD   *((volatile uint8_t*) (0x31))
#define PIND   *((volatile uint8_t*) (0x30))

#endif /* REGISTERS_H_ */