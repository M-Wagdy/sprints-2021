/*
 * DIO_retval.h
 *
 * Created: 7/7/2021 7:20:40 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __BUTTON_RETVAL_H__
#define __BUTTON_RETVAL_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_types.h"

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef uint8_t BUTTON_ERROR_state_t;

/*- ERRORS DEFINITIONS--------------------------------------*/

/**
* @brief: This return value indicate that the function
* ran successfully and it returns no errors.
*/
#define           E_BUTTON_SUCCESS             (BUTTON_ERROR_state_t)( 0 )

#endif /* __BUTTON_RETVAL_H__ */