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
#define TOGGLE_RATE_OFF					( (uint8_t) 0)
#define TOGGLE_RATE_100MS				( (uint8_t) 2)
#define TOGGLE_RATE_400MS				( (uint8_t) 1)

#define PRESSED_2_SECONDS				( (uint16_t) 20)
#define PRESSED_4_SECONDS				( (uint16_t) 40)

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
extern uint8_t gu8_ToggleRate;

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
* Description: Set Toggle Rate based on button pressed time. 
************************************************************************************/
void Button_Task( void * pvParameters )
{
	/* Variable to store button state. */
	static pinState_t ButtonState;
	/* Variable to store button pressed ticks. */
	static uint16_t u16_ButtonPressedCounter = 0;
	
	for( ;; )
	{
		/* Read button state. */
		ButtonState = GPIO_read(BUTTON_PORT, BUTTON_PIN);
		
		/* Increament Counter if button is pressed. */
		if(PIN_IS_HIGH == ButtonState)
		{
			u16_ButtonPressedCounter++;
		}
		else
		{
			/* Set Toggle Rate Depending on Ticks. */
			if(u16_ButtonPressedCounter > 0 && u16_ButtonPressedCounter < PRESSED_2_SECONDS)
			{
				gu8_ToggleRate = TOGGLE_RATE_OFF;
			}
			else if(u16_ButtonPressedCounter >= PRESSED_2_SECONDS && u16_ButtonPressedCounter < PRESSED_4_SECONDS)
			{
				gu8_ToggleRate = TOGGLE_RATE_400MS;
			}
			else if(u16_ButtonPressedCounter >= PRESSED_4_SECONDS)
			{
				gu8_ToggleRate = TOGGLE_RATE_100MS;
			}
			else
			{
				/* Do nothing. */
			}
			
			/* Reset counter. */
			u16_ButtonPressedCounter = 0;
		}
		
		/* Delay 100 MS. */
		vTaskDelay(DELAY_100_MSECOND);
	}
}
