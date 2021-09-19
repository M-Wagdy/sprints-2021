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

#define ADDR_OFFSET_DATA   (uint8_t)(0x00)
#define ADDR_OFFSET_CTRL   (uint8_t)(0x01)
#define ADDR_OFFSET_STAT   (uint8_t)(0x02)

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/
/* This function Write data to the hardware registers. */
static ERROR_STATE_t DIOProxy_Marshall(STR_DIOProxy_t * const ProxyData, const STR_DIOData_t * PinData);

/* This function Gets data from the hardware registers. */
static ERROR_STATE_t DIOProxy_Unmarshall(STR_DIOProxy_t * const ProxyData, STR_DIOData_t * const PinData);

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/**
* @brief: This function Write data to the hardware registers.
*
* @param [in]  ProxyData   -  Struct containing Hardware address.
* @param [in]  PinData     -  Struct containing Pin Data to be written to the hardware registers.
*
* @return function error state.
*/
ERROR_STATE_t DIOProxy_Marshall(STR_DIOProxy_t * const ProxyData, const STR_DIOData_t * PinData)
{
   /* Variable to store function error state. */
   ERROR_STATE_t Proxy_ErrorState;
   
   /* Validate that Valid Parameters are passed. */
   if(NULL_PTR != ProxyData->u8_Addr && NULL_PTR != PinData)
   {
      /* Configuration Command */
      if(PIN_CMD_CONFIGURE == PinData->u8_CMD)
      {
         /* Set Pin Direction */
         BIT_WRITE(*(ProxyData->u8_Addr - ADDR_OFFSET_CTRL), PinData->u8_Pin, PinData->u8_PinDirection);
         
         /* Set Pin Resistor Type for Input Pins */
         if(PIN_INPUT == PinData->u8_PinDirection)
         {
            BIT_WRITE(*(ProxyData->u8_Addr - ADDR_OFFSET_DATA), PinData->u8_Pin, PinData->u8_PinPullUp);
         }
         
         /* Set Function Error State to OK */
         Proxy_ErrorState = ERROR_OK;
      }
      /* Mutation Command */
      else if(PIN_CMD_MUTATE == PinData->u8_CMD)
      {
         /* Make Sure Pin is Output */
         if(PIN_OUTPUT == PinData->u8_PinDirection)
         {
            /* Set Pin Value */
            BIT_WRITE(*(ProxyData->u8_Addr - ADDR_OFFSET_DATA), PinData->u8_Pin, PinData->u8_PinData);
            /* Set Function Error State to OK */
            Proxy_ErrorState = ERROR_OK;
         }
         else
         {
            /* Set Function Error State to NOT OK */
            Proxy_ErrorState = ERROR_NOK;
         }
      }
      else
      {
         /* Set Function Error State to NOT OK */
         Proxy_ErrorState = ERROR_NOK;
      }
   }
   else
   {
      /* Set Function Error State to NOT OK */
      Proxy_ErrorState = ERROR_NOK;
   }
   
   /* Return function error state. */
   return Proxy_ErrorState;
}

/**
* @brief: This function Gets data from the hardware registers.
*
* @param [in]     ProxyData   -  Struct containing Hardware address.
* @param [in,out] PinData     -  Struct containing Pin Data to be read from the hardware registers.
*
* @return function error state.
*/
ERROR_STATE_t DIOProxy_Unmarshall(STR_DIOProxy_t * const ProxyData, STR_DIOData_t * const PinData)
{
   /* Variable to store function error state. */
   ERROR_STATE_t Proxy_ErrorState;
   
   /* Validate that Valid Parameters are passed. */
   if(NULL_PTR != ProxyData->u8_Addr && NULL_PTR != PinData)
   {
      /* Read Pin Direction from Control Register. */
      PinData->u8_PinDirection = BIT_GET(*(ProxyData->u8_Addr - ADDR_OFFSET_CTRL), PinData->u8_Pin);
      /* In Case Output Direction Pin. */
      if(PIN_OUTPUT == PinData->u8_PinDirection)
      {
         /* Get Pin Value From Data Register. */
         PinData->u8_PinData = BIT_GET(*(ProxyData->u8_Addr - ADDR_OFFSET_DATA), PinData->u8_Pin);
         /* Set Function Error State to OK */
         Proxy_ErrorState = ERROR_OK;
      }
      /* In Case Input Direction Pin. */
      else if(PIN_INPUT == PinData->u8_PinDirection)
      {
         /* Get Resistor Type From Data Register */
         PinData->u8_PinPullUp = BIT_GET(*(ProxyData->u8_Addr - ADDR_OFFSET_DATA), PinData->u8_Pin);
         /* Get Pin Value From State Register */
         PinData->u8_PinData = BIT_GET(*(ProxyData->u8_Addr - ADDR_OFFSET_STAT), PinData->u8_Pin);
         /* Set Function Error State to OK */
         Proxy_ErrorState = ERROR_OK;
      }
      else
      {
         /* Set Function Error State to OK */
         Proxy_ErrorState = ERROR_NOK;
      }
   }
   else
   {
      /* Set Function Error State to OK */
      Proxy_ErrorState = ERROR_NOK;
   }
   
   /* Return function error state. */
   return Proxy_ErrorState;
}
/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function Initialize Hardware Proxy Struct.
*
* @param [in]  ProxyData   -  Struct containing Hardware address.
* @param [in]  Addr        -  Start Address of the hardware register.
*
* @return function error state.
*/
ERROR_STATE_t DIOProxy_Init(STR_DIOProxy_t * const ProxyData, uint8_t * Addr)
{
   /* Variable to store function error state. */
   ERROR_STATE_t Proxy_ErrorState;
   
   /* Validate that Valid Parameters are passed. */
   if(NULL_PTR != Addr && NULL_PTR != ProxyData)
   {
      /* Set Hardware PRoxy Start Register Address. */
      ProxyData->u8_Addr = Addr;
      /* Set Function Error State to OK */
      Proxy_ErrorState = ERROR_OK;
   }      
   else
   {
      /* Set Function Error State to OK */
      Proxy_ErrorState = ERROR_NOK;
   }
   
   /* Return function error state. */
   return Proxy_ErrorState;
}

/**
* @brief: This function Configures a Pin in Hardware Port.
*
* @param [in]  ProxyData   -  Struct containing Hardware address.
* @param [in]  Pin         -  Pin Number.
* @param [in]  Direction   -  Direction of pin [Input/Output].
* @param [in]  PullUp      -  If pin to be pulled up in case of input.
*
* @return function error state.
*/
ERROR_STATE_t DIOProxy_Configure(STR_DIOProxy_t * const ProxyData, uint8_t Pin, uint8_t Direction, uint8_t PullUp)
{
   /* Variable to store function error state. */
   ERROR_STATE_t Proxy_ErrorState;
   
   /* Validate that Valid Parameters are passed. */
   if(NULL_PTR != ProxyData && NULL_PTR != ProxyData->u8_Addr && Pin < PIN_INVALID)
   {
      /* Set Pin Data. */
      STR_DIOData_t Data;
      Data.u8_Pin = Pin;
      Data.u8_PinDirection = Direction;
      Data.u8_PinPullUp = PullUp;
      /* Set Configuration Command */
      Data.u8_CMD = PIN_CMD_CONFIGURE;
      
      /* Marshall Data to Hardware. */
      Proxy_ErrorState = DIOProxy_Marshall(ProxyData, &Data);
   }
   else
   {
      /* Set Function Error State to OK */
      Proxy_ErrorState = ERROR_NOK;
   }
   
   /* Return function error state. */
   return Proxy_ErrorState;
}

/**
* @brief: This function Disables a Hardware Proxy.
*
* @param [in]  ProxyData   -  Struct containing Hardware address.
*
* @return function error state.
*/
ERROR_STATE_t DIOProxy_Disable(STR_DIOProxy_t * const ProxyData)
{
   /* Variable to store function error state. */
   ERROR_STATE_t Proxy_ErrorState;
   
   /* Validate that Valid Parameters are passed. */
   if(NULL_PTR != ProxyData)
   {
      /* Unset Hardware Proxy Address */
      ProxyData->u8_Addr = NULL_PTR;
      /* Set Function Error State to OK */
      Proxy_ErrorState = ERROR_OK;
   }
   else
   {
      /* Set Function Error State to OK */
      Proxy_ErrorState = ERROR_NOK;
   }
   
   /* Return function error state. */
   return Proxy_ErrorState;
}

/**
* @brief: This function Access Pin data and returns it to client.
*
* @param [in]  ProxyData   -  Struct containing Hardware address.
* @param [in]  Pin         -  Pin Number.
* @param [out] PinData     -  Pin Value.
*
* @return function error state.
*/
ERROR_STATE_t DIOProxy_AccessPin(STR_DIOProxy_t * const ProxyData, uint8_t Pin, uint8_t * PinData)
{
   /* Variable to store function error state. */
   ERROR_STATE_t Proxy_ErrorState;
   
   /* Validate that Valid Parameters are passed. */
   if(NULL_PTR != ProxyData && NULL_PTR != ProxyData->u8_Addr && NULL_PTR != PinData && Pin < PIN_INVALID)
   {
      /* Set The Pin Number */
      STR_DIOData_t Data;
      Data.u8_Pin = Pin;
      /* Unmarshall Data from Hardware. */
      Proxy_ErrorState = DIOProxy_Unmarshall(ProxyData, &Data);
      if(ERROR_OK == Proxy_ErrorState)
      {
         /* Put Pin Value In the output Variable. */
         *PinData = Data.u8_PinData;
         /* Set Function Error State to OK */
         Proxy_ErrorState = ERROR_OK;
      }
      else
      {
         /* Set Function Error State to OK */
         Proxy_ErrorState = ERROR_NOK;
      }
   }
   else
   {
      /* Set Function Error State to OK */
      Proxy_ErrorState = ERROR_NOK;
   }
   
   /* Return function error state. */
   return Proxy_ErrorState;
}

/**
* @brief: This function Changes Pin Data in the hardware registers.
*
* @param [in]  ProxyData   -  Struct containing Hardware address.
* @param [in]  Pin         -  Pin Number.
* @param [in]  PinData     -  Pin Value in Hardware [HIGH/LOW].
*
* @return function error state.
*/
ERROR_STATE_t DIOProxy_MutatePin(STR_DIOProxy_t * const ProxyData, uint8_t Pin, uint8_t PinData)
{
   /* Variable to store function error state. */
   ERROR_STATE_t Proxy_ErrorState;
   
   /* Validate that Valid Parameters are passed. */
   if(NULL_PTR != ProxyData && NULL_PTR != ProxyData->u8_Addr && Pin < PIN_INVALID)
   {
      /* Set The Pin Number */
      STR_DIOData_t Data;
      Data.u8_Pin = Pin;
      /* Unmarshall Data from Hardware. */
      Proxy_ErrorState = DIOProxy_Unmarshall(ProxyData, &Data);
      if(ERROR_OK == Proxy_ErrorState)
      {
         if(PIN_OUTPUT == Data.u8_PinDirection)
         {
            /* Set New Pin Value. */
            Data.u8_PinData = PinData;
            /* Set Mutation Command. */
            Data.u8_CMD = PIN_CMD_MUTATE;
            /* Marshall Data to Hardware. */
            Proxy_ErrorState = DIOProxy_Marshall(ProxyData, &Data);
         }
         else
         {
            /* Set Function Error State to OK */
            Proxy_ErrorState = ERROR_NOK;
         }
      }
      else
      {
         /* Set Function Error State to OK */
         Proxy_ErrorState = ERROR_NOK;
      }
   }
   else
   {
      /* Set Function Error State to OK */
      Proxy_ErrorState = ERROR_NOK;
   }
   
   /* Return function error state. */
   return Proxy_ErrorState;
}