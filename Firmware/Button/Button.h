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

/*- FUNCTION DECLARATIONS ----------------------------------*/
ERROR_STATE_t BUTTON_getState(uint8_t * State);

#endif /* __BUTTON_H__ */