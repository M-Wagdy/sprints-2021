/*
* DIO.h
*
* Created: 7/7/2021 1:49:17 PM
*  Author: Mohamed Wagdy
*/


#ifndef __DIO_H__
#define __DIO_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../Infrastructure/STD_types.h"
#include "DIO_Registers.h"
#include "DIO_retval.h"
#include "DIO_PbCfg.h"

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/**
* @brief: Set a certain bit in any register
*/
#define SET_BIT(REG,BIT) (REG|=((uint8_t)1<<BIT))

/**
* @brief: Clear a certain bit in any register
*/
#define CLEAR_BIT(REG,BIT) ((REG)&=(~((uint8_t)1<<BIT)))

/**
* @brief: Toggle a certain bit in any register
*/
#define TOGGLE_BIT(REG,BIT) ((REG)^=((uint8_t)1<<BIT))

/**
* @brief: Check if a specific bit is set in any register and return true if yes
*/
#define BIT_IS_SET(REG,BIT) ( (REG) & ((uint8_t)1<<BIT) )

/**
* @brief: Check if a specific bit is cleared in any register and return true if yes
*/
#define BIT_IS_CLEAR(REG,BIT) ( !((REG) & ((uint8_t)1<<BIT)) )


/*- FUNCTION DECLARATIONS ----------------------------------*/
DIO_ERROR_state_t DIO_init(const STR_DIO_config_t * configurations); 
DIO_ERROR_state_t DIO_write(uint8_t port, ENU_pins pin, uint8_t data); 
DIO_ERROR_state_t DIO_read(uint8_t port, ENU_pins pin, uint8_t * data);
DIO_ERROR_state_t DIO_toggle(uint8_t port, ENU_pins pin);

#endif /* __DIO_H__ */