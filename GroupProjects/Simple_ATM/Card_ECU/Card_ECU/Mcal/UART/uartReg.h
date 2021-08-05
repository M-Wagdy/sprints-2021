/*
 * UART_REG.h
 *
 *  Created on: July 16, 2021
 *      Author: Ahmed
 */

#ifndef UART_REG_H_
#define UART_REG_H_

#define UDR       *( ( volatile uint8_t* ) 0x2C )
#define UCSRC     *( ( volatile uint8_t* ) 0x40 )
#define UBRRH     *( ( volatile uint8_t* ) 0x40 )
#define UCSRA     *( ( volatile uint8_t* ) 0x2B )
#define UCSRB     *( ( volatile uint8_t* ) 0x2A )
#define UBRRL     *( ( volatile uint8_t* ) 0x29 )

#endif /* UART_REG_H_ */


