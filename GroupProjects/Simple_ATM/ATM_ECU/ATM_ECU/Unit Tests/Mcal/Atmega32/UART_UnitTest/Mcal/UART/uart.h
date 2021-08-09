#ifndef uart_H_
#define uart_H_
/*- INCLUDES -----------------------------------------------*/
#include"../../Infrastructure/TypeDef.h"
#include"../../Infrastructure/Macros.h"
#include"uartConfig.h"
#include"uartRetVal.h"
/*- MACROS--------------------------------------------------*/
/*UART CHANNELS*/
#define UART_1             (uint8_t)0
/*UART INTERRUPTS*/
#define RECIVE_INT         (uint8_t)0
#define TRANSMIT_INT       (uint8_t)1
#define EMPTY_BUFFERR_INT  (uint8_t)2

/*- FUNCTION DECLARATIONS ----------------------------------*/
UART_ERROR_state_t UART_Init(uint8_t UartNumber);
UART_ERROR_state_t UART_TransmitChar(uint8_t UartNumber,uint8_t TxChar);
UART_ERROR_state_t UART_TransmitString(uint8_t UartNumber,ptr_uint8_t TxString);
UART_ERROR_state_t UART_ReceiveChar(uint8_t UartNumber,ptr_uint8_t RxChar);
UART_ERROR_state_t UART_ReceiveString(uint8_t UartNumber,ptr_uint8_t RxString);
UART_ERROR_state_t UART_EnableInterrupt(uint8_t UartNumber,uint8_t UartInterruptType);
UART_ERROR_state_t UART_DisableInterrupt(uint8_t UartNumber,uint8_t UartInterruptType);
UART_ERROR_state_t UART_SetCallback(uint8_t UartNumber,uint8_t UartInterruptType,Ptr_VoidFuncVoid_t Callback);



#endif /*uart_H_*/
