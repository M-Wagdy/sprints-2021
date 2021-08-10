/*
 * usonic.h
 *
 *  Created on: Aug 9, 2021
 *      Author: Ahmed
 */

#ifndef USONIC_H_
#define USONIC_H_
/*INCLUDES-------------------------------*/
#include "usonicConig.h"
#include "usonicRetVal.h"
#include "../../Mcal/DIO/DIO.h"
#include "../../Mcal/Timer/Timer.h"
#include "../../Mcal/ICU/ICU.h"
/*APIs DECLARATIONS------------------------*/
USONIC_ERROR_state_t USONIC_Init(void);
USONIC_ERROR_state_t USONIC_GetDistance(ptr_double64_t distance);


#endif /* USONIC_H_ */
