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
#define DELAY_100_MSECOND		((uint16_t)100)
#define DELAY_500_MSECOND		((uint16_t)500)
#define DELAY_1_SECOND			((uint16_t)1000)

/*- LOCAL Dataypes
----------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/

/*- GLOBAL STATIC VARIABLES
-------------------------------*/

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern TaskHandle_t ToggleTask100MSHandler;
extern TaskHandle_t ToggleTask500MSHandler;
extern TaskHandle_t ToggleTask1000MSHandler;
extern const char * TOGGLE_TASK_100_NAME;
extern const uint16_t TOGGLE_TASK_100_STACK_DEPTH;
extern const UBaseType_t TOGGLE_TASK_100_PRIORITY;
extern const char * TOGGLE_TASK_500_NAME;
extern const uint16_t TOGGLE_TASK_500_STACK_DEPTH;
extern const UBaseType_t TOGGLE_TASK_500_PRIORITY;
extern const char * TOGGLE_TASK_1000_NAME;
extern const uint16_t TOGGLE_TASK_1000_STACK_DEPTH;
extern const UBaseType_t TOGGLE_TASK_1000_PRIORITY;
extern const portX_t LED_1_PORT;
extern const pinX_t LED_1_PIN;
extern const portX_t LED_2_PORT;
extern const pinX_t LED_2_PIN;
extern const portX_t LED_3_PORT;
extern const pinX_t LED_3_PIN;

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
	/* Creates Toggle Tasks */
	xTaskCreate(
			Toggle_100MS_Task,     		 		/* Function that implements the task. */
			TOGGLE_TASK_100_NAME,   			/* Text name for the task. */
			TOGGLE_TASK_100_STACK_DEPTH,	/* Stack size in words, not bytes. */
			( void * ) 0,    							/* Parameter passed into the task. */
			TOGGLE_TASK_100_PRIORITY,			/* Priority at which the task is created. */
			&ToggleTask100MSHandler );   	/* Used to pass out the created task's handle. */
			
	xTaskCreate(
			Toggle_500MS_Task,      			/* Function that implements the task. */
			TOGGLE_TASK_500_NAME,   			/* Text name for the task. */
			TOGGLE_TASK_500_STACK_DEPTH,  /* Stack size in words, not bytes. */
			( void * ) 0,    							/* Parameter passed into the task. */
			TOGGLE_TASK_500_PRIORITY,			/* Priority at which the task is created. */
			&ToggleTask500MSHandler );   	/* Used to pass out the created task's handle. */
	
	xTaskCreate(
			Toggle_1000MS_Task,     			/* Function that implements the task. */
			TOGGLE_TASK_1000_NAME,  			/* Text name for the task. */
			TOGGLE_TASK_1000_STACK_DEPTH, /* Stack size in words, not bytes. */
			( void * ) 0,    							/* Parameter passed into the task. */
			TOGGLE_TASK_1000_PRIORITY,		/* Priority at which the task is created. */
			&ToggleTask1000MSHandler );   /* Used to pass out the created task's handle. */
}

/************************************************************************************
* Service Name: Toggle_100MS_Task
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Toggle LED 1 each 100 MS. 
************************************************************************************/
void Toggle_100MS_Task( void * pvParameters )
{
	for( ;; )
	{
		/* Set Pin High */
		GPIO_write(LED_1_PORT, LED_1_PIN, PIN_IS_HIGH);

		/* Delay 100 Ticks */
		vTaskDelay(DELAY_100_MSECOND);

		/* Set Pin Low */
		GPIO_write(LED_1_PORT, LED_1_PIN, PIN_IS_LOW);

		/* Delay 100 Ticks */
		vTaskDelay(DELAY_100_MSECOND);
	}
}

/************************************************************************************
* Service Name: Toggle_500MS_Task
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Toggle LED 2 each 500 MS. 
************************************************************************************/
void Toggle_500MS_Task( void * pvParameters )
{
	for( ;; )
	{
		/* Set Pin High */
		GPIO_write(LED_2_PORT, LED_2_PIN, PIN_IS_HIGH);

		/* Delay 500 Ticks */
		vTaskDelay(DELAY_500_MSECOND);

		/* Set Pin Low */
		GPIO_write(LED_2_PORT, LED_2_PIN, PIN_IS_LOW);

		/* Delay 500 Ticks */
		vTaskDelay(DELAY_500_MSECOND);
	}
}

/************************************************************************************
* Service Name: Toggle_1000MS_Task
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Toggle LED 3 each 1000 MS. 
************************************************************************************/
void Toggle_1000MS_Task( void * pvParameters )
{
	for( ;; )
	{
		/* Set Pin High */	
		GPIO_write(LED_3_PORT, LED_3_PIN, PIN_IS_HIGH);

		/* Delay 1000 Ticks */
		vTaskDelay(DELAY_1_SECOND);

		/* Set Pin Low */
		GPIO_write(LED_3_PORT, LED_3_PIN, PIN_IS_LOW);

		/* Delay 1000 Ticks */
		vTaskDelay(DELAY_1_SECOND);
	}
}
