/*
 * I2C.c
 *
 * Created: 7/16/2021 9:32:59 AM
 *  Author: Mohamed Wagdy
 */ 
/*- INCLUDES
----------------------------------------------*/
#include "I2C.h"

/*- LOCAL MACROS
------------------------------------------*/
#define HIGH                        (uint8_t)(1)
#define LOW                         (uint8_t)(0)

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static Ptr_VoidFuncVoid_t g_Callback[I2C_NUMBERS];

/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function initialize I2C channel.
*
* @param [in]  I2C_CH   -  I2C channel number.
*
* @return function error state.
*/
I2C_ERROR_state_t I2C_Init(uint8_t I2C_CH)
{
   
}

/**
* @brief: This function sets a start condition on the bus.
*
* @param [in]  I2C_CH      -  I2C channel number.
* @param [in]  SlaveAddr   -  Slave Address, with the read or write bit.
*
* @return function error state.
*/
I2C_ERROR_state_t I2C_Start(uint8_t I2C_CH, uint8_t SlaveAddr)
{
   
}

/**
* @brief: This function sets a repeated start condition on the bus.
*
* @param [in]  I2C_CH      -  I2C channel number.
* @param [in]  SlaveAddr   -  Slave Address, with the read or write bit.
*
* @return function error state.
*/
I2C_ERROR_state_t I2C_RepeatedStart(uint8_t I2C_CH, uint8_t SlaveAddr)
{
   
}

/**
* @brief: This function write a byte on I2C bus.
*
* @param [in]  I2C_CH      -  I2C channel number.
* @param [in]  Data        -  data byte to be sent.
*
* @return function error state.
*/
I2C_ERROR_state_t I2C_Write(uint8_t I2C_CH, uint8_t Data)
{
   
}

/**
* @brief: This function read a byte from I2C and sends an ack.
*
* @param [in]  I2C_CH      -  I2C channel number.
* @param [out] Data        -  pointer to where to store the read data.
*
* @return function error state.
*/
I2C_ERROR_state_t I2C_ReadAck(uint8_t I2C_CH, uint8_t * Data)
{
   
}

/**
* @brief: This function read a byte from I2C and doesn't send an ack.
*
* @param [in]  I2C_CH      -  I2C channel number.
* @param [out] Data        -  pointer to where to store the read data.
*
* @return function error state.
*/
I2C_ERROR_state_t I2C_ReadNoAck(uint8_t I2C_CH, uint8_t * Data)
{
   
}

/**
* @brief: This function sets a stop condition on the bus.
*
* @param [in]  I2C_CH      -  I2C channel number.
*
* @return function error state.
*/
I2C_ERROR_state_t I2C_Stop(uint8_t I2C_CH)
{
   
}

/**
* @brief: This function receives a stream of characters through I2C.
*
* @param [in]  I2C_CH      -  I2C channel number.
* @param [out] Status      -  pointer to where to store the status of I2C.
*
* @return function error state.
*/
I2C_ERROR_state_t I2C_Status(uint8_t I2C_CH, uint8_t * Status)
{
   
}

/**
* @brief: This function enables I2C interrupt.
*
* @param [in]  I2C_CH      -  I2C channel number.
*
* @return function error state.
*/
I2C_ERROR_state_t I2C_EnableInterrupt(uint8_t I2CNumber)
{
   
}

/**
* @brief: This function disables I2C interrupt.
*
* @param [in]  I2C_CH      -  I2C channel number.
*
* @return function error state.
*/
I2C_ERROR_state_t I2C_DisableInterrupt(uint8_t I2CNumber)
{
   
}

/**
* @brief: This function sets a callback function.
*
* @param [in]  I2C_CH      -  I2C channel number.
* @param [in]  Callback    -  address of the callback function.
*
* @return function error state.
*/
I2C_ERROR_state_t I2C_SetCallback(uint8_t I2CNumber, Ptr_VoidFuncVoid_t Callback)
{
   
}