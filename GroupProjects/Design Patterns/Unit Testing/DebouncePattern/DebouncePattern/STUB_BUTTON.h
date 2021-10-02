/*
 * STUB_BUTTON.h
 *
 * Created: 9/2/2021 1:50:18 PM
 *  Author: Mohamed Wagdy
 */


#ifndef __STUB_BUTTON_H__
#define __STUB_BUTTON_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_types.h"

/* Timer Channels */
#define  BTN_0                      (uint8_t)( 0 )
#define  BTN_INVALID_CH             (uint8_t)( 1 )

/*- FUNCTION DECLARATIONS ----------------------------------*/

/* Get Button State. */
ERROR_STATE_t BUTTON_getState(uint8_t BUTTON_CH, uint8_t* State);

#endif /* __STUB_BUTTON_H__ */