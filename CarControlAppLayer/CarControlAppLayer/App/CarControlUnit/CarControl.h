/*
 * CarControl.h
 *
 * Created: 7/12/2021 6:54:13 AM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __CARCONTROL_H__
#define __CARCONTROL_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../Motor.h"
#include "../../PushButton.h"
#include "CarControl_retval.h"

/*- FUNCTION DECLARATIONS ----------------------------------*/

/* Function that initialize car hardware. */
CAR_ERROR_state_t CAR_Init(void);

/* Function that updates the car state. */
CAR_ERROR_state_t CAR_Update(void);

#endif /* __CARCONTROL_H__ */