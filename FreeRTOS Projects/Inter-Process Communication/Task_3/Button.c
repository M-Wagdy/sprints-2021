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
#include "Comm_Lcfg.h"

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
extern TaskHandle_t Button1TaskHandler;
extern TaskHandle_t Button2TaskHandler;
extern const char * BUTTON_1_TASK_NAME;
extern const uint16_t BUTTON_1_TASK_STACK_DEPTH;
extern const UBaseType_t BUTTON_1_TASK_PRIORITY;
extern const char * BUTTON_2_TASK_NAME ;
extern const uint16_t BUTTON_2_TASK_STACK_DEPTH;
extern const UBaseType_t BUTTON_2_TASK_PRIORITY;
extern const portX_t BUTTON_1_PORT;
extern const pinX_t BUTTON_1_PIN;
extern const portX_t BUTTON_2_PORT;
extern const pinX_t BUTTON_2_PIN;
extern const CommMessage BTN1_RisingMessage;
extern const CommMessage BTN1_FallingMessage;
extern const CommMessage BTN2_RisingMessage;
extern const CommMessage BTN2_FallingMessage;
extern QueueHandle_t xMessageQueue;

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
* Description: Creates the button tasks.
************************************************************************************/
void Button_Task_Create(void)
{
	/* Creates Button Tasks */
	xTaskCreate(
			Button_1_Task,      /* Function that implements the task. */
			BUTTON_1_TASK_NAME,   /* Text name for the task. */
			BUTTON_1_TASK_STACK_DEPTH,      							/* Stack size in words, not bytes. */
			( void * ) 0,    				/* Parameter passed into the task. */
			BUTTON_1_TASK_PRIORITY,											/* Priority at which the task is created. */
			&Button1TaskHandler );   /* Used to pass out the created task's handle. */
			
	xTaskCreate(
			Button_2_Task,      /* Function that implements the task. */
			BUTTON_2_TASK_NAME,   /* Text name for the task. */
			BUTTON_2_TASK_STACK_DEPTH,      							/* Stack size in words, not bytes. */
			( void * ) 0,    				/* Parameter passed into the task. */
			BUTTON_2_TASK_PRIORITY,											/* Priority at which the task is created. */
			&Button2TaskHandler );   /* Used to pass out the created task's handle. */
}

/************************************************************************************
* Service Name: Button_1_Task
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sends message queue on rising/falling edges of button 1. 
************************************************************************************/
void Button_1_Task( void * pvParameters )
{
	/* Variable to store Old and new button states. */
	static pinState_t Button1State = PIN_IS_LOW, OldButton1State = PIN_IS_LOW;
	/* Main Task Loop. */
	for( ;; )
	{
		/* Get button 1 state. */
		Button1State = GPIO_read(BUTTON_1_PORT, BUTTON_1_PIN);
		/* Check Falling/Rising Edges. */
		if(PIN_IS_LOW == Button1State && PIN_IS_HIGH == OldButton1State)
		{
			/* Falling Edge */
			xQueueSend( xMessageQueue, ( void * ) &BTN1_FallingMessage, portMAX_DELAY );
		}
		else if(PIN_IS_HIGH == Button1State && PIN_IS_LOW == OldButton1State)
		{
			/* Rising Edge */
			xQueueSend( xMessageQueue, ( void * ) &BTN1_RisingMessage, portMAX_DELAY );
		}
		else
		{
			/* Do nothing */
		}
		/* Store new state in old button state. */
		OldButton1State = Button1State;
		/* Delay 100 MS. */
		vTaskDelay(DELAY_100_MSECOND);
	}
}

/************************************************************************************
* Service Name: Button_2_Task
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sends message queue on rising/falling edges of button 2. 
************************************************************************************/
void Button_2_Task( void * pvParameters )
{
	/* Variable to store Old and new button states. */
	static pinState_t Button2State = PIN_IS_LOW, OldButton2State = PIN_IS_LOW;
	/* Main Task Loop. */
	for( ;; )
	{
		/* Get button 2 state. */
		Button2State = GPIO_read(BUTTON_2_PORT, BUTTON_2_PIN);
		/* Check Falling/Rising Edges. */
		if(PIN_IS_LOW == Button2State && PIN_IS_HIGH == OldButton2State)
		{
			/* Falling Edge */
			xQueueSend( xMessageQueue, ( void * ) &BTN2_FallingMessage, portMAX_DELAY );
		}
		else if(PIN_IS_HIGH == Button2State && PIN_IS_LOW == OldButton2State)
		{
			/* Rising Edge */
			xQueueSend( xMessageQueue, ( void * ) &BTN2_RisingMessage, portMAX_DELAY );
		}
		else
		{
			/* Do nothing */
		}
		/* Store new state in old button state. */
		OldButton2State = Button2State;
		/* Delay 100 MS. */
		vTaskDelay(DELAY_100_MSECOND);
	}
}
