/*
 * DIO_HardwareProxy.h
 *
 * Created: 8/19/2021 1:50:18 PM
 * Author: Mohamed Wagdy
 */ 

#ifndef __DIO_HARDWARE_PROXY_H__
#define __DIO_HARDWARE_PROXY_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_types.h"
#include "BIT_MATH.h"

/*- MACROS -------------------------------------------------*/
#define PIN_0        (uint8_t)(0)
#define PIN_1        (uint8_t)(1)
#define PIN_2        (uint8_t)(2)
#define PIN_3        (uint8_t)(3)
#define PIN_4        (uint8_t)(4)
#define PIN_5        (uint8_t)(5)
#define PIN_6        (uint8_t)(6)
#define PIN_7        (uint8_t)(7)
#define PIN_INVALID  (uint8_t)(8)

#define PIN_INPUT    (uint8_t)(0)
#define PIN_OUTPUT   (uint8_t)(1)

#define PIN_NO_RES   (uint8_t)(0)
#define PIN_PULLUP   (uint8_t)(1)

#define PIN_LOW      (uint8_t)(0)
#define PIN_HIGH     (uint8_t)(1)

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct STR_DIOProxy_t{
   volatile uint8_t * u8_Addr;
} STR_DIOProxy_t;

typedef struct STR_DIOData_t{
   uint8_t u8_Pin;
   uint8_t u8_PinDirection;
   uint8_t u8_PinData;
   uint8_t u8_PinPullUp;
   uint8_t u8_CMD;
} STR_DIOData_t;

/*- FUNCTION DECLARATIONS ----------------------------------*/
ERROR_STATE_t DIOProxy_Init(STR_DIOProxy_t * const ProxyData, uint8_t * Addr);
ERROR_STATE_t DIOProxy_Configure(STR_DIOProxy_t * const ProxyData, uint8_t Pin, uint8_t Direction, uint8_t PullUp);
ERROR_STATE_t DIOProxy_Disable(STR_DIOProxy_t * const ProxyData);
ERROR_STATE_t DIOProxy_AccessPin(STR_DIOProxy_t * const ProxyData, uint8_t Pin, uint8_t * PinData);
ERROR_STATE_t DIOProxy_MutatePin(STR_DIOProxy_t * const ProxyData, uint8_t Pin, uint8_t PinData);

#endif /* __DIO_HARDWARE_PROXY_H__ */