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
#define DELAY_100_MSECOND				((uint16_t)100)
#define DELAY_500_MSECOND				((uint16_t)500)

/*- LOCAL Dataypes
----------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/

/*- GLOBAL STATIC VARIABLES
-------------------------------*/

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern TaskHandle_t Comm1TaskHandler;
extern TaskHandle_t Comm2TaskHandler;
extern const char * COMM_1_TASK_NAME;
extern const uint16_t COMM_1_TASK_STACK_DEPTH;
extern const UBaseType_t COMM_1_TASK_PRIORITY;
extern const char * COMM_2_TASK_NAME;
extern const uint16_t COMM_2_TASK_STACK_DEPTH;
extern const UBaseType_t COMM_2_TASK_PRIORITY;
extern unsigned char txDataSizeLeftToSend;
extern signed char String_1[11];
extern signed char String_2[11];
extern SemaphoreHandle_t xUART1Mutex;

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
* Description: Creates the Comm tasks. 
************************************************************************************/
void Comm_Task_Create(void)
{
	/* Creates Comm Tasks */
	xTaskCreate(
			Comm_1_Task,      /* Function that implements the task. */
			COMM_1_TASK_NAME,   /* Text name for the task. */
			COMM_1_TASK_STACK_DEPTH,      							/* Stack size in words, not bytes. */
			( void * ) 0,    				/* Parameter passed into the task. */
			COMM_1_TASK_PRIORITY,											/* Priority at which the task is created. */
			&Comm1TaskHandler );   /* Used to pass out the created task's handle. */
			
	xTaskCreate(
			Comm_2_Task,      /* Function that implements the task. */
			COMM_2_TASK_NAME,   /* Text name for the task. */
			COMM_2_TASK_STACK_DEPTH,      							/* Stack size in words, not bytes. */
			( void * ) 0,    				/* Parameter passed into the task. */
			COMM_2_TASK_PRIORITY,											/* Priority at which the task is created. */
			&Comm2TaskHandler );   /* Used to pass out the created task's handle. */
}

/************************************************************************************
* Service Name: Comm_1_Task
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sends 10 strings to UART every 100 MS. 
************************************************************************************/
void Comm_1_Task( void * pvParameters )
{
	/* Counter for loop. */
	uint8_t i;
	
	for( ;; )
	{	
		/* Take the Mutex. */
		xSemaphoreTake(xUART1Mutex, portMAX_DELAY);
		
		/* Send the 10 strings */
		for(i = 0; i<10; i++)
		{
			/* Change 4th element in string to show the loop counter. */
			String_1[3] = i+'0'; 
			/* Send to UART. */
			vSerialPutString(String_1, 10);
			/* Wait until string is transmitted. */
			while(txDataSizeLeftToSend != 0);
		}
		/* Return the mutex. */
		xSemaphoreGive(xUART1Mutex);
		
		/* Delay 100 MS. */
		vTaskDelay(DELAY_100_MSECOND);
	}
}

/************************************************************************************
* Service Name: Comm_2_Task
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sends 10 strings to UART every 500 MS. 
************************************************************************************/
void Comm_2_Task( void * pvParameters )
{
	/* Counter for loop. */
	uint8_t i;
	/* Counter for dummy loop delay. */
	volatile uint32_t j;
	
	for( ;; )
	{
		/* Take the Mutex. */
		xSemaphoreTake(xUART1Mutex, portMAX_DELAY);

		/* Send the 10 strings */
		for(i = 0; i<10; i++)
		{
			/* Change 4th element in string to show the loop counter. */
			String_2[3] = i+'0'; 
			/* Send to UART. */
			vSerialPutString(String_2, 10);
			/* Simulate Heavy load. */
			for(j =0; j<100000; j++);
		}
		/* Return the mutex. */
		xSemaphoreGive(xUART1Mutex);
		/* Delay 500 MS. */
		vTaskDelay(DELAY_500_MSECOND);
	}
}
