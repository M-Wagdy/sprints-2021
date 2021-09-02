/*
 * SPI_retval.h
 *
 * Created: 7/14/2021 2:08:56 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __SPI_RETVAL_H__
#define __SPI_RETVAL_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_types.h"

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef uint8_t SPI_ERROR_state_t;

/*- ERRORS DEFINITIONS--------------------------------------*/

/**
* @brief: This return value indicate that the function
* ran successfully and it returns no errors.
*/
#define           E_SPI_SUCCESS              (SPI_ERROR_state_t)( 0 )

/**
* @brief: This return value indicate that the SPI Data Register
* is written during a data transfer.
*/
#define           E_SPI_WRITE_COLLISION      (SPI_ERROR_state_t)( 1 )

/**
* @brief: This return value indicate that the init function was
* called before.
*/
#define           E_SPI_INIT_BEFORE          (SPI_ERROR_state_t)( 2 )

/**
* @brief: This return value indicate that a function was called
* before Init function.
*/
#define           E_SPI_NOT_INIT             (SPI_ERROR_state_t)( 3 )

/**
* @brief: This return value indicate that a function got a null pointer.
*/
#define           E_SPI_NULL_PTR             (SPI_ERROR_state_t)( 4 )

/**
* @brief: This return value indicate that a function got an invalid slave channel.
*/
#define           E_SPI_INVALID_SS_CH        (SPI_ERROR_state_t)( 5 )

/**
* @brief: This return value indicate that a function got an invalid SPI channel.
*/
#define           E_SPI_INVALID_CH           (SPI_ERROR_state_t)( 6 )

#endif /* __SPI_RETVAL_H__ */