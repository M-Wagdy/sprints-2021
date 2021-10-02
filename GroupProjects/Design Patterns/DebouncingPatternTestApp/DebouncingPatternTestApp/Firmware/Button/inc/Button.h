/*
 * Button.h
 *
 * Created: 7/7/2021 1:50:18 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __BUTTON_H__
#define __BUTTON_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_types.h"
#include "DIO.h"
#include "Button_Lcfg.h"

/* Timer Channels */
#define  BTN_0                      (uint8_t)( 0 )
#define  BTN_INVALID_CH             (uint8_t)( 1 )

/*- ERRORS DEFINITIONS--------------------------------------*/

/**
* @brief: This return value indicate that a function
* got an uninitialized pointer.
*/
#define           BTN_E_NULL_PTR                (ERROR_STATE_t)( -1 )

/**
* @brief: This return value indicate that a function
* got an invalid channel.
*/
#define           BTN_E_INVALID_CH_NUM        (ERROR_STATE_t)( -2 )

/*- FUNCTION DECLARATIONS ----------------------------------*/
/* Initialize Button Channel. */
ERROR_STATE_t Button_Init(uint8_t BUTTON_CH);

/* Get Button State. */
ERROR_STATE_t BUTTON_getState(uint8_t BUTTON_CH, uint8_t * State);

#endif /* __BUTTON_H__ */