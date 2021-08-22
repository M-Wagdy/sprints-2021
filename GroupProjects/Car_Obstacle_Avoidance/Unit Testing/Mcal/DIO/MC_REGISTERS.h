/*
 * File Name: MC_REGISTERS.h
 * Creation Date: 07/20/2020
 * Author: Rehab
 * Description: Header File for registers' addresses of ATMAGA32, bits' names....
 */ 

#ifndef __MC_REGISTERS__
#define __MC_REGISTERS__

#define F_CPU 8000000ul

//FILES INCLUDING
#include "STD_TYPES.h"

//BITS
#define BIT0 0
#define BIT1 1
#define BIT2 2
#define BIT3 3
#define BIT4 4
#define BIT5 5
#define BIT6 6
#define BIT7 7

/************************************************************************/
/*                         GPIO REGISTERS                               */
/************************************************************************/
//PORTA REGISTERS
uint8_t PINA; 
uint8_t DDRA; 
uint8_t PORTA; 

//PORTB REGISTERS 
uint8_t PINB; 
uint8_t DDRB;
uint8_t PORTB;

//PORTC REGISTERS
uint8_t PINC; 
uint8_t DDRC;
uint8_t PORTC;

//PORTD REGISTERS
uint8_t PIND; 
uint8_t DDRD;
uint8_t PORTD;
/************************************************************************/
#endif