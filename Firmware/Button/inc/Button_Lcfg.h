/*
 * Button_Lcfg.h
 *
 * Created: 8/21/2021 2:07:12 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __BUTTON_LCFG_H__
#define __BUTTON_LCFG_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_TYPES.h"
#include "DIO_Config.h"

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct STR_BUTTON_config_t{
   uint8_t u8_Port;
   uint8_t u8_Pin;
   uint8_t u8_PullUp;
} STR_BUTTON_config_t;

/*- MACROS -------------------------------------------------*/
#define  BUTTONS_NUMBER             (uint8_t)( 1 )

#endif /* __BUTTON_LCFG_H__ */