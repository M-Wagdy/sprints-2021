/*
 * TempObserver.h
 *
 * Created: 8/22/2021 2:00:35 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __TEMP_OBSERVER_H__
#define __TEMP_OBSERVER_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_types.h"
#include "TempSensor.h"

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef void (*AcceptorPtr)(uint8_t TempData);

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct STR_TEMPSensor_t{
   uint8_t TempData;
   uint8_t NotificationCounter;
   AcceptorPtr NotificationHandler[100];
} STR_TEMPSensor_t;

/*- FUNCTION DECLARATIONS ----------------------------------*/

/* Initialize Observer Data. */
ERROR_STATE_t TEMPObserver_Init(STR_TEMPSensor_t * const ObserverData);

/* Subscribe a new Acceptor in the Observer. */
ERROR_STATE_t TEMPObserver_Subscribe(STR_TEMPSensor_t * const ObserverData, const AcceptorPtr * AcceptCallback);

/* Unsubscribe an Acceptor from the observer. */
ERROR_STATE_t TEMPObserver_Unsubscribe(STR_TEMPSensor_t * const ObserverData, const AcceptorPtr * AcceptCallback);

/* Set New Sensor Data in the Observer. */
ERROR_STATE_t TEMPObserver_SetNewData(STR_TEMPSensor_t * const ObserverData, uint8_t NewTemp);

#endif /* __TEMP_OBSERVER_H__ */