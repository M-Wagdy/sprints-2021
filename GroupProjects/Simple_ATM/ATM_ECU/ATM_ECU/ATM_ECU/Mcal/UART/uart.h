#ifndef uart_H_
#define uart_H_
#include "../../Infrastructure/STD_types.h"
#include "Macros.h"
#include "uartConfig.h"
/*UART CHANNELS*/
#define UART_1             (uint8_t)0
/*UART INTERRUPTS*/
#define RECIVE_INT         (uint8_t)0
#define TRANSMIT_INT       (uint8_t)1
#define EMPTY_BUFFERR_INT  (uint8_t)2





uint8_t UART_Init(uint8_t UartNumber);
uint8_t UART_TransmitChar(uint8_t UartNumber,uint8_t TxChar);
uint8_t UART_TransmitString(uint8_t UartNumber,ptr_uint8_t TxString);
uint8_t UART_ReceiveChar(uint8_t UartNumber,ptr_uint8_t RxChar);
uint8_t UART_ReceiveString(uint8_t UartNumber,ptr_uint8_t RxString);
uint8_t UART_EnableInterrupt(uint8_t UartNumber,uint8_t UartInterruptType);
uint8_t UART_DisableInterrupt(uint8_t UartNumber,uint8_t UartInterruptType);
uint8_t UART_SetCallback(uint8_t UartNumber,uint8_t UartInterruptType,Ptr_VoidFuncVoid_t Callback);
void UART_FlushReceiveBuffer(void);


#endif /*uart_H_*/
