/*
* STUB_DIO.h
*
* Created: 8/5/2021 10:49:17 AM
*  Author: Mohamed Wagdy
*/


#ifndef __STUB_DIO_H__
#define __STUB_DIO_H__

/*- INCLUDES -----------------------------------------------*/
#include "..\..\Infrastructure\STD_types.h"
#include "DIO_Config.h"
#include "DIO_retval.h"

/*- STUB FUNCTION DECLARATIONS ----------------------------------*/

uint8_t DIO_ReadPin(uint8_t PortName, uint8_t PinNo, uint8_t* PinData);

#endif /* __STUB_DIO_H__ */
