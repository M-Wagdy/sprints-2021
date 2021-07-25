/*
 * Terminal.h
 *
 * Created: 7/24/2021 5:39:58 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __TERMINAL_H__
#define __TERMINAL_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../Mcal/UART/UART.h"
#include "Terminal_retval.h"
#include "Terminal_Config.h"

/*- FUNCTION DECLARATIONS ----------------------------------*/

/* Function that initialize Terminal channel */
TERMINAL_ERROR_state_t TERMINAL_Init(uint8_t Terminal_CH);

/* Function that read terminal buffer */
TERMINAL_ERROR_state_t Terminal_Read(uint8_t * Data);

/* Function that write to the Terminal */
TERMINAL_ERROR_state_t Terminal_Write(uint8_t Terminal_CH, uint8_t * Data);

/* CallBack function upon receiving character */
void TERMINAL_ReadCallBack(void);

#endif /* __TERMINAL_H__ */