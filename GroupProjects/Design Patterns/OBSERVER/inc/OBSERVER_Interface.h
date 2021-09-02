/*
 * OBSERVER_Interface.h
 *
 * Created: 8/21/2021 02:43:40 PM
 *  Author: Ahmed Essam
 */

#ifndef __OBSERVER_INTERFACE_H__
#define __OBSERVER_INTERFACE_H__

 /*INCLUDES-------------------------------*/
#include "STD_TYPES.h"
/*- LOCAL MACROS
 ------------------------------------------*/
#define NUMBER_OF_CLIENTS     (uint8_t)20
#define EMPTY                (uint8_t)0
/*- FUNCTION DECLARATIONS ----------------------------------*/
extern ERROR_STATE_t OBSERVER_Subscribe(Ptr_VoidFuncVoid_t ClientFunction);
extern ERROR_STATE_t OBSERVER_Unsubscribe(Ptr_VoidFuncVoid_t ClientFunction);
extern ERROR_STATE_t OBSERVER_Get(ptr_double64_t Distance);
extern ERROR_STATE_t OBSERVER_Set(double64_t Distance);

#endif /*__OBSERVER_INTERFACE_H__*/
