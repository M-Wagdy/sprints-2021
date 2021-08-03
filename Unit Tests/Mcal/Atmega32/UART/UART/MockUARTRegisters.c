/*
 * MockUARTRegisters.c
 *
 * Created: 7/13/2021 6:05:33 PM
 *  Author: Mohamed Wagdy
 */ 
#include "Infrastructure/STD_types.h"

/* initialize registers valaues */
uint8_t UART_DATA_R = 0x00;
uint8_t UART_STATUS_R = 0x40;
uint8_t UART_CONTROL_R = 0x00;
uint8_t UART_CONTROL_2_R = 0x86;
uint8_t UART_BAUDRATE_LOW_R = 0x00;
uint8_t UART_BAUDRATE_HIGH_R = 0x00;