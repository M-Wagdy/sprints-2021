/*
* DIO.h
*
* Created: 7/7/2021 1:49:17 PM
*  Author: Mohamed Wagdy
*/


#ifndef __DIO_H__
#define __DIO_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_types.h"
#include "DIO_Registers.h"
#include "DIO_retval.h"
#include "DIO_Config.h"

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/**
* @brief: Set a certain bit in any register
*/
#define SET_BIT(REG,BIT) (REG|=((uint8_t)(1)<<BIT))

/**
* @brief: Clear a certain bit in any register
*/
#define CLEAR_BIT(REG,BIT) ((REG)&=(~((uint8_t)(1)<<BIT)))

/**
* @brief: Toggle a certain bit in any register
*/
#define TOGGLE_BIT(REG,BIT) ((REG)^=((uint8_t)(1)<<BIT))

/**
* @brief: Check if a specific bit is set in any register and return true if yes
*/
#define BIT_IS_SET(REG,BIT) ( (REG) & ((uint8_t)(1)<<BIT) )

/**
* @brief: Check if a specific bit is cleared in any register and return true if yes
*/
#define BIT_IS_CLEAR(REG,BIT) ( !((REG) & ((uint8_t)(1)<<BIT)) )


/*- FUNCTION DECLARATIONS ----------------------------------*/

/* Function that initialize all DIO pins. */
DIO_ERROR_state_t DIO_SetPinDirection(uint8_t port , uint8_t pin ,uint8_t direction);
DIO_ERROR_state_t DIO_EnablePinPullup(uint8_t port,uint8_t pin);

/* Function that writes value to a pin. */
DIO_ERROR_state_t DIO_WritePin(uint8_t port , uint8_t pin ,uint8_t data);

/* Function that reads a pin. */
DIO_ERROR_state_t DIO_ReadPin(uint8_t port,uint8_t pin,uint8_t * data);

/* Function that toggles a pin. */
DIO_ERROR_state_t DIO_TogglePin(uint8_t port,uint8_t pin);



#endif /* __DIO_H__ */