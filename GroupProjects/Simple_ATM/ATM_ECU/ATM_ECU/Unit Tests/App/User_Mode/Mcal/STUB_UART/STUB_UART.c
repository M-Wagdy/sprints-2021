/*
* STUB_UART.c
*
* Created: 8/5/2021 10:49:17 AM
*  Author: Mohamed Wagdy
*/

/*- INCLUDES -----------------------------------------------*/
#include "STUB_UART.h"

/*- STUB FUNCTION DECLARATIONS ----------------------------------*/

uint8_t UART_Init(uint8_t UartNumber)
{
   return 1;
}

uint8_t UART_EnableInterrupt(uint8_t UartNumber, uint8_t UartInterruptType)
{
   return 1;
}

uint8_t UART_SetCallback(uint8_t UartNumber, uint8_t UartInterruptType, Ptr_VoidFuncVoid_t Callback)
{
   return 1;
}

uint8_t UART_TransmitString(uint8_t UartNumber, ptr_uint8_t TxString)
{
   return 1;
}

uint8_t UART_ReceiveString(uint8_t UartNumber, ptr_uint8_t RxString)
{
   return 1;
}

uint8_t UART_GetData(uint8_t UartNumber, ptr_uint8_t RxChar)
{
   return 1;
}
