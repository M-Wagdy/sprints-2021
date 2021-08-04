/*
 * UART_Registers.h
 *
 * Created: 7/13/2021 2:54:14 PM
 *  Author: Mohamed Wagdy
 */ 

#ifndef __UART_REGISTERS_H__
#define __UART_REGISTERS_H__

#define TEST 0

#if !TEST
   /*- UART REGISTERS-----------------------------------------*/
   #define  UART_DATA_R                (*((volatile uint8_t *) (0x2C)))
   #define  UART_STATUS_R              (*((volatile uint8_t *) (0x2B)))
   #define  UART_CONTROL_R             (*((volatile uint8_t *) (0x2A)))
   #define  UART_CONTROL_2_R           (*((volatile uint8_t *) (0x40)))
   #define  UART_BAUDRATE_HIGH_R       (*((volatile uint8_t *) (0x40)))
   #define  UART_BAUDRATE_LOW_R		   (*((volatile uint8_t *) (0x29)))
#else
   /*- UART REGISTERS-----------------------------------------*/
   extern volatile uint8_t UART_DATA_R;
   extern volatile uint8_t UART_STATUS_R;
   extern volatile uint8_t UART_CONTROL_R;
   extern volatile uint8_t UART_CONTROL_2_R;
   extern volatile uint8_t UART_BAUDRATE_HIGH_R;
   extern volatile uint8_t UART_BAUDRATE_LOW_R;
#endif

#endif /* __UART_REGISTERS_H__ */