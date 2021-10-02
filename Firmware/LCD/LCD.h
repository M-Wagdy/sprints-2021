/*
 * LCD.h
 *
 * Created: 7/25/2021 5:29:55 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __LCD_H__
#define __LCD_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_types.h"
#include "utils.h"
#include "DIO.h"
#include "LCD_retval.h"
#include "LCD_Config.h"

/*- FUNCTION DECLARATIONS ----------------------------------*/

/* Initialize LCD channel */
LCD_ERROR_state_t LCD_Init(uint8_t LCD_CH);

/* Send command to LCD */
LCD_ERROR_state_t LCD_SendCommand(uint8_t LCD_CH, uint8_t Command);

/* Send character to LCD */
LCD_ERROR_state_t LCD_SendCharacter(uint8_t LCD_CH, uint8_t Data);

/* Send String to LCD */
LCD_ERROR_state_t LCD_SendString(uint8_t LCD_CH, uint8_t * Data);

/* Set cursor position on LCD */
LCD_ERROR_state_t LCD_SetToRowCol(uint8_t LCD_CH, uint8_t Row, uint8_t Col);

#endif /* __LCD_H__ */