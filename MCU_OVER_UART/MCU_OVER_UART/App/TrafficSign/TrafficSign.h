/*
 * TrafficSign.h
 *
 * Created: 7/14/2021 10:13:54 AM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __TRAFFICSIGN_H__
#define __TRAFFICSIGN_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../Mcal/UART/UART.h"
#include "../../Firmware/LED/LED.h"

/*- FUNCTION DECLARATIONS ----------------------------------*/
void Traffic_init(void);
void Traffic_update(void);

#endif /* __TRAFFICSIGN_H__ */