/*
 * TempObserver.c
 *
 * Created: 8/22/2021 2:00:35 PM
 *  Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "TempObserver.h"

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/
/* Notify all Subscribers in the Observer Data. */
static ERROR_STATE_t TEMPObserver_Notify(STR_TEMPSensor_t * const ObserverData);

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/**
* @brief: This function notifies all Subscribers in the Observer Data.
*
* @param [in]  ObserverData   -  Struct containing Observer Data.
*
* @return function error state.
*/
ERROR_STATE_t TEMPObserver_Notify(STR_TEMPSensor_t * const ObserverData)
{
   /* Variable to store function error state. */
   ERROR_STATE_t Observer_ErrorState;
   
   /* Validate that Valid Parameters are passed. */
   if(NULL_PTR != ObserverData)
   {
      /* Loop on all Acceptor Functions. */
      for(uint8_t u8_Counter = 0; u8_Counter < 100; u8_Counter++)
      {
         /* Break from loop if found first null pointer. */
         if(NULL_PTR != ObserverData->NotificationHandler[u8_Counter])
         {
            /* Send To the Acceptor function the new temp data. */
            ObserverData->NotificationHandler[u8_Counter](ObserverData->TempData);
         }
         else
         {
            break;
         }
      }
      /* Set Function Error State to OK */
      Observer_ErrorState = ERROR_OK;
   }
   else
   {
      /* Set Function Error State to NOT OK */
      Observer_ErrorState = ERROR_NOK;
   }
   
   /* Return function error state. */
   return Observer_ErrorState;
}

/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function Initialize Observer Data.
*
* @param [in]  ObserverData   -  Struct containing Observer Data.
*
* @return function error state.
*/
ERROR_STATE_t TEMPObserver_Init(STR_TEMPSensor_t * const ObserverData)
{
   /* Variable to store function error state. */
   ERROR_STATE_t Observer_ErrorState;
   
   /* Validate that Valid Parameters are passed. */
   if(NULL_PTR != ObserverData)
   {
      /* Initialize observer data. */
      ObserverData->NotificationCounter = 0;
      ObserverData->TempData = 0;
      /* Set Function Error State to OK */
      Observer_ErrorState = ERROR_OK;
   }
   else
   {
      /* Set Function Error State to NOT OK */
      Observer_ErrorState = ERROR_NOK;
   }
   
   /* Return function error state. */
   return Observer_ErrorState;
}

/**
* @brief: This function Subscribe a new Acceptor in the Observer.
*
* @param [in]  ObserverData   -  Struct containing Observer Data.
* @param [in]  AcceptCallback -  Pointer to Acceptor Function.
*
* @return function error state.
*/
ERROR_STATE_t TEMPObserver_Subscribe(STR_TEMPSensor_t * const ObserverData, const AcceptorPtr * AcceptCallback)
{
   /* Variable to store function error state. */
   ERROR_STATE_t Observer_ErrorState;
   
   /* Validate that Valid Parameters are passed. */
   if(NULL_PTR != ObserverData && NULL_PTR != AcceptCallback)
   {
      /* Add Acceptor function to the Notification handler array. */
      ObserverData->NotificationHandler[ObserverData->NotificationCounter] = AcceptCallback;
      /* Increament the notification counter. */
      ObserverData->NotificationCounter++;
      /* Set Function Error State to OK */
      Observer_ErrorState = ERROR_OK;
   }
   else
   {
      /* Set Function Error State to NOT OK */
      Observer_ErrorState = ERROR_NOK;
   }
   
   /* Return function error state. */
   return Observer_ErrorState;
}

/**
* @brief: This function Unsubscribe an Acceptor from the observer.
*
* @param [in]  ObserverData   -  Struct containing Observer Data.
* @param [in]  AcceptCallback -  Pointer to Acceptor Function.
*
* @return function error state.
*/
ERROR_STATE_t TEMPObserver_Unsubscribe(STR_TEMPSensor_t * const ObserverData, const AcceptorPtr * AcceptCallback)
{
   /* Variable to store function error state. */
   ERROR_STATE_t Observer_ErrorState = ERROR_NOK;
   
   /* Validate that Valid Parameters are passed. */
   if(NULL_PTR != ObserverData && NULL_PTR != AcceptCallback)
   {
      /* Loop on all acceptors. */
      for(uint8_t u8_Counter = 0; u8_Counter < 100; u8_Counter++)
      {
         /* Check if this is the acceptor to unsubscribe. */
         if(ObserverData->NotificationHandler[u8_Counter] = AcceptCallback)
         {
            /* Decrement the Notification counter. */
            ObserverData->NotificationCounter--;
            /* Put the last acceptor in the list in the unsubscribed place. */
            ObserverData->NotificationHandler[u8_Counter] = ObserverData->NotificationHandler[ObserverData->NotificationCounter];
            /* Set the last acceptor place with null pointer. */
            ObserverData->NotificationHandler[ObserverData->NotificationCounter] = NULL_PTR;
            /* Set Function Error State to OK */
            Observer_ErrorState = ERROR_OK;
            /* Break from the loop. */
            break;
         }
      }
   }
   else
   {
      /* Set Function Error State to NOT OK */
      Observer_ErrorState = ERROR_NOK;
   }
   
   /* Return function error state. */
   return Observer_ErrorState;
}

/**
* @brief: This function Set New Sensor Data in the Observer.
*
* @param [in]  ObserverData   -  Struct containing Observer Data.
* @param [in]  NewTemp        -  New Temperature Data.
*
* @return function error state.
*/
ERROR_STATE_t TEMPObserver_SetNewData(STR_TEMPSensor_t * const ObserverData, uint8_t NewTemp)
{
   /* Variable to store function error state. */
   ERROR_STATE_t Observer_ErrorState;
   
   /* Validate that Valid Parameters are passed. */
   if(NULL_PTR != ObserverData)
   {
      /* Set New Temperature in the observer data. */
      ObserverData->TempData = NewTemp;
      /* Notify all acceptors. */
      Observer_ErrorState = TEMPObserver_Notify(ObserverData);
   }
   else
   {
      /* Set Function Error State to NOT OK */
      Observer_ErrorState = ERROR_NOK;
   }
   
   /* Return function error state. */
   return Observer_ErrorState;
}