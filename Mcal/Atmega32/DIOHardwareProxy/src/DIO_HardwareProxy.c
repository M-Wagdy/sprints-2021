/*
 * DIO_HardwareProxy.c
 *
 * Created: 8/19/2021 1:50:18 PM
 * Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "DIO_HardwareProxy.h"

/*- LOCAL MACROS
------------------------------------------*/
#define PIN_CMD_CONFIGURE  (uint8_t)(0)
#define PIN_CMD_MUTATE     (uint8_t)(1)

#define ADDR_OFFSET_DATA   (uint8_t)(0)
#define ADDR_OFFSET_CTRL   (uint8_t)(1)
#define ADDR_OFFSET_STAT   (uint8_t)(2)

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/
static ERROR_STATE_t DIOProxy_Marshall(STR_DIOProxy_t * const ProxyData, const STR_DIOData_t * PinData);
static ERROR_STATE_t DIOProxy_Unmarshall(STR_DIOProxy_t * const ProxyData, STR_DIOData_t * const PinData);

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
ERROR_STATE_t DIOProxy_Marshall(STR_DIOProxy_t * const ProxyData, const STR_DIOData_t * PinData)
{
   ERROR_STATE_t Proxy_ErrorState;
   
   if(NULL_PTR != ProxyData->u8_Addr && NULL_PTR != PinData)
   {
      if(PIN_CMD_CONFIGURE == PinData->u8_CMD)
      {
         BIT_WRITE(*(ProxyData->u8_Addr - ADDR_OFFSET_CTRL), PinData->u8_Pin, PinData->u8_PinDirection);
         
         if(PIN_INPUT == PinData->u8_PinDirection)
         {
            BIT_WRITE(*(ProxyData->u8_Addr - ADDR_OFFSET_DATA), PinData->u8_Pin, PinData->u8_PinPullUp);
         }
         Proxy_ErrorState = ERROR_OK;
      }
      else if(PIN_CMD_MUTATE == PinData->u8_CMD)
      {
         if(PIN_OUTPUT == PinData->u8_PinDirection)
         {
            BIT_WRITE(*(ProxyData->u8_Addr - ADDR_OFFSET_DATA), PinData->u8_Pin, PinData->u8_PinData);
            Proxy_ErrorState = ERROR_OK;
         }
         else
         {
            Proxy_ErrorState = ERROR_NOK;
         }
      }
      else
      {
         Proxy_ErrorState = ERROR_NOK;
      }
   }
   else
   {
      Proxy_ErrorState = ERROR_NOK;
   }
   
   return Proxy_ErrorState;
}

ERROR_STATE_t DIOProxy_Unmarshall(STR_DIOProxy_t * const ProxyData, STR_DIOData_t * const PinData)
{
   ERROR_STATE_t Proxy_ErrorState;
   
   if(NULL_PTR != ProxyData->u8_Addr && NULL_PTR != PinData)
   {
      PinData->u8_PinDirection = BIT_GET(*(ProxyData->u8_Addr - ADDR_OFFSET_CTRL), PinData->u8_Pin);
      if(PIN_OUTPUT == PinData->u8_PinDirection)
      {
         PinData->u8_PinData = BIT_GET(*(ProxyData->u8_Addr - ADDR_OFFSET_DATA), PinData->u8_Pin);
         Proxy_ErrorState = ERROR_OK;
      }
      else if(PIN_INPUT == PinData->u8_PinDirection)
      {
         PinData->u8_PinPullUp = BIT_GET(*(ProxyData->u8_Addr - ADDR_OFFSET_DATA), PinData->u8_Pin);
         PinData->u8_PinData = BIT_GET(*(ProxyData->u8_Addr - ADDR_OFFSET_STAT), PinData->u8_Pin);
         Proxy_ErrorState = ERROR_OK;
      }
      else
      {
         Proxy_ErrorState = ERROR_NOK;
      }
   }
   else
   {
      Proxy_ErrorState = ERROR_NOK;
   }
   
   return Proxy_ErrorState;
}
/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function Initialize Client Struct.
*
* @param [in]  ClientData  -  Struct containing Client Data.
*
* @return function error state.
*/
ERROR_STATE_t DIOProxy_Init(STR_DIOProxy_t * const ProxyData, uint8_t * Addr)
{
   ERROR_STATE_t Proxy_ErrorState;
   
   if(NULL_PTR != Addr && NULL_PTR != ProxyData)
   {
      ProxyData->u8_Addr = Addr;
      Proxy_ErrorState = ERROR_OK;
   }      
   else
   {
      Proxy_ErrorState = ERROR_NOK;
   }
   
   return Proxy_ErrorState;
}

ERROR_STATE_t DIOProxy_Configure(STR_DIOProxy_t * const ProxyData, uint8_t Pin, uint8_t Direction, uint8_t PullUp)
{
   ERROR_STATE_t Proxy_ErrorState;
   
   if(NULL_PTR != ProxyData->u8_Addr && Pin < PIN_INVALID)
   {
      STR_DIOData_t Data;
      Data.u8_Pin = Pin;
      Data.u8_PinDirection = Direction;
      Data.u8_PinPullUp = PullUp;
      Data.u8_CMD = PIN_CMD_CONFIGURE;
      
      Proxy_ErrorState = DIOProxy_Marshall(ProxyData, &Data);
   }
   else
   {
      Proxy_ErrorState = ERROR_NOK;
   }
   return Proxy_ErrorState;
}

ERROR_STATE_t DIOProxy_Disable(STR_DIOProxy_t * const ProxyData)
{
   ERROR_STATE_t Proxy_ErrorState;
   if(NULL_PTR != ProxyData)
   {
      ProxyData->u8_Addr = NULL_PTR;
      Proxy_ErrorState = ERROR_OK;
   }
   else
   {
      Proxy_ErrorState = ERROR_NOK;
   }
   
   return Proxy_ErrorState;
}

ERROR_STATE_t DIOProxy_AccessPin(STR_DIOProxy_t * const ProxyData, uint8_t Pin, uint8_t * PinData)
{
   ERROR_STATE_t Proxy_ErrorState;
   
   if(NULL_PTR != ProxyData->u8_Addr && NULL_PTR != PinData && Pin < PIN_INVALID)
   {
      STR_DIOData_t Data;
      Data.u8_Pin = Pin;
      Proxy_ErrorState = DIOProxy_Unmarshall(ProxyData, &Data);
      if(ERROR_OK == Proxy_ErrorState)
      {
         *PinData = Data.u8_PinData;
         Proxy_ErrorState = ERROR_OK;
      }
      else
      {
         Proxy_ErrorState = ERROR_NOK;
      }
   }
   else
   {
      Proxy_ErrorState = ERROR_NOK;
   }
   return Proxy_ErrorState;
}


ERROR_STATE_t DIOProxy_MutatePin(STR_DIOProxy_t * const ProxyData, uint8_t Pin, uint8_t PinData)
{
   ERROR_STATE_t Proxy_ErrorState;
   
   if(NULL_PTR != ProxyData->u8_Addr && Pin < PIN_INVALID)
   {
      STR_DIOData_t Data;
      Data.u8_Pin = Pin;
      Proxy_ErrorState = DIOProxy_Unmarshall(ProxyData, &Data);
      if(ERROR_OK == Proxy_ErrorState)
      {
         if(PIN_OUTPUT == Data.u8_PinDirection)
         {
            Data.u8_PinData = PinData;
            Data.u8_CMD = PIN_CMD_MUTATE;
            Proxy_ErrorState = DIOProxy_Marshall(ProxyData, &Data);
         }
         else
         {
            Proxy_ErrorState = ERROR_NOK;
         }
      }
      else
      {
         Proxy_ErrorState = ERROR_NOK;
      }
   }
   else
   {
      Proxy_ErrorState = ERROR_NOK;
   }
   return Proxy_ErrorState;
}