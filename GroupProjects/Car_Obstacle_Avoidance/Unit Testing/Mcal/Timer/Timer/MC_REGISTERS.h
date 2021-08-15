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
/*                         GENERAL TIMERS REGISTERS                     */
/************************************************************************/
//GENERAL TIMERS REGISTERS
volatile uint8_t TIMSK;
volatile uint8_t TIFR;


//TIMSKR REGISTER BITS
#define TOIE0 BIT0
#define OCIE0 BIT1
#define TOIE1 BIT2
#define OCIE1B BIT3
#define OCIE1A BIT4
#define TICIE1 BIT5
#define TOIE2 BIT6
#define OCIE2 BIT7
//TIFR REGISTER BITS
#define TOV0 BIT0
#define OCF0 BIT1
#define TOV1 BIT2
#define OCF1B BIT3
#define OCF1A BIT4
#define ICF1 BIT5
#define TOV2 BIT6
#define OCF2 BIT7
/************************************************************************/
/*                         TIMER0 REGISTERS                             */
/************************************************************************/
//TIMER0 REGISTERS 
volatile uint8_t TCCR0;
volatile uint8_t TCNT0;
volatile uint8_t OCR0;


//TCCR0 REGISTER BITS
#define CS00 BIT0
#define CS01 BIT1
#define CS02 BIT2
#define WGM01 BIT3
#define COM00 BIT4
#define COM01 BIT5
#define WGM00 BIT6
#define FOC0 BIT7
/************************************************************************/
/*                         TIMER1 REGISTERS                             */
/************************************************************************/
//TIMER1 REGISTERS 
volatile uint8_t TCCR1A;
volatile uint8_t TCCR1B;
volatile uint8_t TCNT1H;
volatile uint8_t TCNT1L;
volatile uint16_t TCNT1;
volatile uint8_t OCR1AH;
volatile uint8_t OCR1AL;
volatile uint16_t OCR1A;
volatile uint8_t OCR1BH;
volatile uint8_t OCR1BL;
volatile uint16_t OCR1B;
volatile uint8_t ICR1H;
volatile uint8_t ICR1L;
volatile uint16_t ICR1;

//TCCR1A REGISTER BITS
#define WGM10 BIT0
#define WGM11 BIT1
#define FOC1B BIT2
#define FOC1A BIT3
#define COM1B0 BIT4
#define COM1B1 BIT5
#define COM1A0 BIT6
#define COM1A1 BIT7
//TCCR1B REGISTER BITS
#define CS10 BIT0
#define CS11 BIT1
#define CS12 BIT2
#define WGM12 BIT3
#define WGM13 BIT4
#define ICES1 BIT6
#define ICNC1 BIT7
/************************************************************************/
/*                         TIMER2 REGISTERS                             */
/************************************************************************/
//TIMER2 REGISTERS 
volatile uint8_t TCCR2;
volatile uint8_t TCNT2;
volatile uint8_t OCR2;


//TCCR2 REGISTER BITS
#define CS20 BIT0
#define CS21 BIT1
#define CS22 BIT2
#define WGM21 BIT3
#define COM20 BIT4
#define COM21 BIT5
#define WGM20 BIT6
#define FOC2 BIT7
#endif