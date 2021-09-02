/*
 * DIO_retval.h
 *
 * Created: 7/7/2021 5:14:40 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __DIO_RETVAL_H__
#define __DIO_RETVAL_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_types.h"

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef uint8_t DIO_ERROR_state_t;

/*- ERRORS DEFINITIONS--------------------------------------*/

/**
* @brief: This return value indicate that the function
* ran successfully and it returns no errors.
*/
#define           E_DIO_SUCCESS              (DIO_ERROR_state_t)( 0 )

/**
* @brief: This return value indicate that the DIO set pin direction
* API got an invalid direction value.
*/
#define           E_DIO_INVALID_DIRECTION    (DIO_ERROR_state_t)( 1 )

/**
* @brief: This return value indicate that a DIO function
* got an invalid pin number.
*/
#define           E_DIO_INVALID_PIN          (DIO_ERROR_state_t)( 2 )

/**
* @brief: This return value indicate that a DIO function
* got invalid port number.
*/
#define           E_DIO_INVALID_PORT         (DIO_ERROR_state_t)( 3 )

/**
* @brief: This return value indicate that a DIO write function
* got an invalid data.
*/
#define           E_DIO_INVALID_WRITE_DATA   (DIO_ERROR_state_t)( 4 )

/**
* @brief: This return value indicate that a DIO function
* got an uninitialized pointer.
*/
#define           E_DIO_NULL_PTR             (DIO_ERROR_state_t)( 5 )

#endif /* __DIO_RETVAL_H__ */