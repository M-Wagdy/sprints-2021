/*
 * LCD_retval.h
 *
 * Created: 7/25/2021 5:30:04 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __LCD_RETVAL_H__
#define __LCD_RETVAL_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../Infrastructure/STD_types.h"

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef uint8_t LCD_ERROR_state_t;

/*- ERRORS DEFINITIONS--------------------------------------*/

/**
* @brief: This return value indicate that the function
* ran successfully and it returns no errors.
*/
#define           E_LCD_SUCCESS                    (LCD_ERROR_state_t)( 0 )

/**
* @brief: This return value indicate that a function got an
* uninitialized pointer.
*/
#define           E_LCD_NULL_PTR                   (LCD_ERROR_state_t)( 1 )

/**
* @brief: This return value indicate that a function got an
* invalid channel.
*/
#define           E_LCD_INVALID_CH                 (LCD_ERROR_state_t)( 2 )

#endif /* __LCD_RETVAL_H__ */