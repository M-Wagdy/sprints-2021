/*
 * UART_REG.h
 *
 *  Created on: July 16, 2021
 *      Author: Ahmed
 */

#ifndef UART_REG_H_
#define UART_REG_H_

#define TESTING 1


#if !(TESTING)
#define UDR       *( ( volatile uint8_t* ) 0x2C )
#define UCSRC     *( ( volatile uint8_t* ) 0x40 )
#define UBRRH     *( ( volatile uint8_t* ) 0x40 )
#define UCSRA     *( ( volatile uint8_t* ) 0x2B )
#define UCSRB     *( ( volatile uint8_t* ) 0x2A )
#define UBRRL     *( ( volatile uint8_t* ) 0x29 )
#else
extern uint8_t UDR ;
extern uint8_t UCSRC ;
extern uint8_t UBRRH ;
extern uint8_t UCSRA ;
extern uint8_t UCSRB ;
extern uint8_t UBRRL ;
#endif


#endif /* UART_REG_H_ */


