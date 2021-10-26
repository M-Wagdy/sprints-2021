/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Periodic.c
 *       Module:  Periodic
 *
 *  Description:  source file for Periodic module.    
 *  
 *********************************************************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "Periodic.h"
#include "Comm_Lcfg.h"

/*- LOCAL MACROS
------------------------------------------*/
#define DELAY_300_MSECOND				((uint16_t)300)

/*- LOCAL Dataypes
----------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/

/*- GLOBAL STATIC VARIABLES
-------------------------------*/

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern TaskHandle_t PeriodicTaskHandler;
extern const char * PERIODIC_TASK_NAME;
extern const uint16_t PERIODIC_TASK_STACK_DEPTH;
extern const UBaseType_t PERIODIC_TASK_PRIORITY;
extern const CommMessage PeriodicMessage;
extern QueueHandle_t xMessageQueue;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

/*- APIs IMPLEMENTATION
-----------------------------------*/
/************************************************************************************
* Service Name: Periodic_Task_Create
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Creates the periodic task. 
************************************************************************************/
void Periodic_Task_Create(void)
{
	/* Creates Periodic Tasks */
	xTaskCreate(
			Periodic_Task,      /* Function that implements the task. */
			PERIODIC_TASK_NAME,   /* Text name for the task. */
			PERIODIC_TASK_STACK_DEPTH,      							/* Stack size in words, not bytes. */
			( void * ) 0,    				/* Parameter passed into the task. */
			PERIODIC_TASK_PRIORITY,											/* Priority at which the task is created. */
			&PeriodicTaskHandler );   /* Used to pass out the created task's handle. */
}

/************************************************************************************
* Service Name: Periodic_Task
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sends String to the uart. 
************************************************************************************/
void Periodic_Task( void * pvParameters )
{	
	for( ;; )
	{	
		/* Send Periodic Message to queue */
		xQueueSend( xMessageQueue, ( void * ) &PeriodicMessage, portMAX_DELAY );
		/* Delay 300 MS. */
		vTaskDelay(DELAY_300_MSECOND);
	}
}
