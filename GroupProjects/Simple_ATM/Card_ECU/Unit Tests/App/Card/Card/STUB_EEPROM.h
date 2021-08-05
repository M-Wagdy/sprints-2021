/*
* STUB_EEPROM.h
*
* Created: 8/5/2021 10:49:17 AM
*  Author: Mohamed Wagdy
*/


#ifndef __STUB_EEPROM_H__
#define __STUB_EEPROM_H__

/*- INCLUDES -----------------------------------------------*/
#include "Infrastructure/STD_types.h"
#include "Firmware/EEPROM/EEPROM_retval.h"
#include "Firmware/EEPROM/EEPROM_Config.h"

/*- STUB FUNCTION DECLARATIONS ----------------------------------*/

EEPROM_ERROR_state_t EEPROM_Init(uint8_t EEPROM_CH);
EEPROM_ERROR_state_t EEPROM_ReadBytes(uint8_t EEPROM_CH, uint8_t memoryBlock, uint8_t start_address, uint8_t* data, uint8_t bytes_num);
EEPROM_ERROR_state_t EEPROM_WriteBytes(uint8_t EEPROM_CH, uint8_t memoryBlock, uint8_t start_address, uint8_t* data, uint8_t bytes_num);

#endif /* __STUB_EEPROM_H__ */