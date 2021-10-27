/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Toggle.c
 *       Module:  Toggle
 *
 *  Description:  source file for Toggle module.    
 *  
 *********************************************************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "Toggle.h"

/*- LOCAL MACROS
------------------------------------------*/
#define DELAY_200_MSECOND				((uint16_t)200)

/*- LOCAL Dataypes
----------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/

/*- GLOBAL STATIC VARIABLES
-------------------------------*/

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern TaskHandle_t ToggleTaskHandler;
extern const char * TOGGLE_TASK_NAME;
extern const uint16_t TOGGLE_TASK_STACK_DEPTH;
extern const UBaseType_t TOGGLE_TASK_PRIORITY;
extern const portX_t LED_PORT;
extern const pinX_t LED_PIN;
extern SemaphoreHandle_t LEDToggleSem;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

/*- APIs IMPLEMENTATION
-----------------------------------*/
/************************************************************************************
* Service Name: Toggle_Task_Create
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Creates the toggle task. 
************************************************************************************/
void Toggle_Task_Create(void)
{
	/* Creates Toggle Task */
	xTaskCreate(
			Toggle_Task,       			/* Function that implements the task. */
			TOGGLE_TASK_NAME,       /* Text name for the task. */
			TOGGLE_TASK_STACK_DEPTH,/* Stack size in words, not bytes. */
			( void * ) 0,    				/* Parameter passed into the task. */
			TOGGLE_TASK_PRIORITY,		/* Priority at which the task is created. */
			&ToggleTaskHandler );   /* Used to pass out the created task's handle. */
}

/************************************************************************************
* Service Name: Toggle_Task
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Toggle Led. 
************************************************************************************/
void Toggle_Task( void * pvParameters )
{
	/* Variable to store current led state. */
	static pinState_t LEDState;
	/* Task main loop. */
	for( ;; )
	{
		/* If semaphore is taken successfully. */
		if(xSemaphoreTake( LEDToggleSem, portMAX_DELAY ) == pdTRUE)
		{
			/* Get LED state. */
			LEDState = GPIO_read(LED_PORT, LED_PIN);
			/* Toggle LED. */
			if(LEDState == PIN_IS_HIGH)
			{
				/* Set Pin Low. */
				GPIO_write(LED_PORT, LED_PIN, PIN_IS_LOW);
			}
			else
			{
				/* Set Pin High. */
				GPIO_write(LED_PORT, LED_PIN, PIN_IS_HIGH);
			}
		}	
		/* Delay 200 MS. */		
		vTaskDelay(DELAY_200_MSECOND);
	}
}
