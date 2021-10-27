/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Comm.c
 *       Module:  Comm
 *
 *  Description:  source file for Comm module.    
 *  
 *********************************************************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "Comm.h"

/*- LOCAL MACROS
------------------------------------------*/
#define DELAY_500_MSECOND				((uint16_t)500)

/*- LOCAL Dataypes
----------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/

/*- GLOBAL STATIC VARIABLES
-------------------------------*/

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern TaskHandle_t CommTaskHandler;
extern const char * COMM_TASK_NAME;
extern const uint16_t COMM_TASK_STACK_DEPTH;
extern const UBaseType_t COMM_TASK_PRIORITY;
extern unsigned char txDataSizeLeftToSend;
extern QueueHandle_t xMessageQueue;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

/*- APIs IMPLEMENTATION
-----------------------------------*/
/************************************************************************************
* Service Name: Comm_Task_Create
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Creates the Comm task. 
************************************************************************************/
void Comm_Task_Create(void)
{
	/* Creates Comm Tasks */
	xTaskCreate(
			Comm_Task,      /* Function that implements the task. */
			COMM_TASK_NAME,   /* Text name for the task. */
			COMM_TASK_STACK_DEPTH,      							/* Stack size in words, not bytes. */
			( void * ) 0,    				/* Parameter passed into the task. */
			COMM_TASK_PRIORITY,											/* Priority at which the task is created. */
			&CommTaskHandler );   /* Used to pass out the created task's handle. */
}

/************************************************************************************
* Service Name: Comm_Task
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sends String to the uart. 
************************************************************************************/
void Comm_Task( void * pvParameters )
{
	/* Variable to receive Queue Messages. */
	static struct CommMessage RxMessage;
	/* Task Main Loop. */
	for( ;; )
	{
		/* If there is data in Queue */
		if( xQueueReceive( xMessageQueue, &( RxMessage ), portMAX_DELAY) == pdPASS )
		{
			/* Send Received String to UART. */
			vSerialPutString(RxMessage.string, RxMessage.size);
			/* Wait till message is send. */
			while(txDataSizeLeftToSend != 0);
		}
		/* Delay 500 MS. */
		vTaskDelay(DELAY_500_MSECOND);
	}
}
