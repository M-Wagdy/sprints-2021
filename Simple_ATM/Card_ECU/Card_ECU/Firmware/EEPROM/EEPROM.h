/*
 * EEPROM.h
 *
 * Created: 7/20/2021 10:53:23 AM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __EEPROM_H__
#define __EEPROM_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../Mcal/I2C/I2C.h"
#include "EEPROM_retval.h"
#include "EEPROM_Config.h"

/*- FUNCTION DECLARATIONS ----------------------------------*/

/* Function that initialize EEPROM channel */
EEPROM_ERROR_state_t EEPROM_Init(uint8_t EEPROM_CH);

/* Function that reads from the EEPROM */
EEPROM_ERROR_state_t EEPROM_Read(uint8_t EEPROM_CH, uint8_t address, uint8_t * data);

/* Function that write to the EEPROM */
EEPROM_ERROR_state_t EEPROM_Write(uint8_t EEPROM_CH, uint8_t address, uint8_t data);

#endif /* __EEPROM_H__ */