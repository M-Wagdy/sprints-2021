/*
 * COMMProxy.h
 *
 * Created: 8/24/2021 1:50:18 PM
 * Author: Mohamed Wagdy
 */ 

#ifndef __COMMPROXY_H__
#define __COMMPROXY_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_types.h"

/*- MACROS -------------------------------------------------*/
#define COMM_NUMBERS                 (uint8_t)(3)
#define COMM_UART_CH                 (uint8_t)(0)
#define COMM_SPI_CH                  (uint8_t)(1)
#define COMM_I2C_CH                  (uint8_t)(2)
#define COMM_INVALID_CH              (uint8_t)(3)

/*- FUNCTION DECLARATIONS ----------------------------------*/
/* This function Initialize COM Channel. */
ERROR_STATE_t COMMProxy_Init(uint8_t COMM_CH);

/* This function Sends a byte on the given COM channel. */
ERROR_STATE_t COMMProxy_Send(uint8_t COMM_CH, uint8_t Data);

/* This function Sets the Callback to call after sending a byte on I2C channel. */
ERROR_STATE_t COMMProxy_SetTxCallback(uint8_t COMM_CH, Ptr_VoidFuncVoid_t Callback);

/* This function Sets the Callback to call after receiving a byte on I2C channel. */
ERROR_STATE_t COMMProxy_SetRxCallback(uint8_t COMM_CH, Ptr_VoidFuncU8_t Callback);

#endif /* __COMMPROXY_H__ */