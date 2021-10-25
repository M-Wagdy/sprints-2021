/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Button.h
 *       Module:  Button
 *
 *  Description:  header file for Button module.    
 *  
 *********************************************************************************************************************/
#ifndef __BUTTON_H__
#define __BUTTON_H__

/*- INCLUDES -----------------------------------------------*/
/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "lpc21xx.h"

/* Peripheral includes. */
#include "GPIO.h"

/*- CONSTANTS ----------------------------------------------*/

/*- ERRORS DEFINITIONS--------------------------------------*/

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/
/* Creates the toggle task. */
extern void Button_Task_Create( void );

/* Toggle Task */
extern void Button_Task( void * pvParameters );

#endif  /* __BUTTON_H__ */
