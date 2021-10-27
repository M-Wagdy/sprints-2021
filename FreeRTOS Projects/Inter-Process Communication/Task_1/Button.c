/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Button.c
 *       Module:  Button
 *
 *  Description:  source file for Button module.    
 *  
 *********************************************************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "Button.h"

/*- LOCAL MACROS
------------------------------------------*/
#define DELAY_100_MSECOND				((uint16_t)100)

/*- LOCAL Dataypes
----------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/

/*- GLOBAL STATIC VARIABLES
-------------------------------*/

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern TaskHandle_t ButtonTaskHandler;
extern const char * BUTTON_TASK_NAME;
extern const uint16_t BUTTON_TASK_STACK_DEPTH;
extern const UBaseType_t BUTTON_TASK_PRIORITY;
extern const portX_t BUTTON_PORT;
extern const pinX_t BUTTON_PIN;
extern SemaphoreHandle_t LEDToggleSem;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

/*- APIs IMPLEMENTATION
-----------------------------------*/
/************************************************************************************
* Service Name: Button_Task_Create
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Creates the button task. 
************************************************************************************/
void Button_Task_Create(void)
{
	/* Creates Button Task */
	xTaskCreate(
			Button_Task,      				/* Function that implements the task. */
			BUTTON_TASK_NAME,   			/* Text name for the task. */
			BUTTON_TASK_STACK_DEPTH,  /* Stack size in words, not bytes. */
			( void * ) 0,    					/* Parameter passed into the task. */
			BUTTON_TASK_PRIORITY,			/* Priority at which the task is created. */
			&ButtonTaskHandler );   	/* Used to pass out the created task's handle. */
}

/************************************************************************************
* Service Name: Button_Task
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Give Semaphore to Led Task on press. 
************************************************************************************/
void Button_Task( void * pvParameters )
{
	/* Variable to store Old and new button states. */
	static pinState_t ButtonState = PIN_IS_LOW, OldButtonState = PIN_IS_LOW;
	/* Task main loop. */
	for( ;; )
	{
		/* Get button state. */
		ButtonState = GPIO_read(BUTTON_PORT, BUTTON_PIN);
		/* On Button Falling Edge. */
		if(PIN_IS_LOW == ButtonState && PIN_IS_HIGH == OldButtonState)
		{
			/* Give Semaphore. */
			xSemaphoreGive( LEDToggleSem );
		}
		else
		{
			/* Do nothing */
		}
		
		/* Store new state in old button state. */
		OldButtonState = ButtonState;
		/* Delay 100 MS. */
		vTaskDelay(DELAY_100_MSECOND);
	}
}
