/*
* STUB_EEPROM.c
*
* Created: 8/5/2021 10:49:17 AM
*  Author: Mohamed Wagdy
*/
/*- INCLUDES -----------------------------------------------*/
#include "STUB_EEPROM.h"

uint8_t gau8_Memory[25];

/*- STUB FUNCTION DECLARATIONS ----------------------------------*/

EEPROM_ERROR_state_t EEPROM_Init(uint8_t EEPROM_CH)
{
   return E_EEPROM_SUCCESS;
}

EEPROM_ERROR_state_t EEPROM_ReadBytes(uint8_t EEPROM_CH, uint8_t memoryBlock, uint8_t start_address, uint8_t* data, uint8_t bytes_num)
{
   for (uint8_t u8_MemoryCounter = 0; u8_MemoryCounter < bytes_num; u8_MemoryCounter++)
   {
      data[u8_MemoryCounter] = gau8_Memory[start_address + u8_MemoryCounter];
   }

   return E_EEPROM_SUCCESS;
}

EEPROM_ERROR_state_t EEPROM_WriteBytes(uint8_t EEPROM_CH, uint8_t memoryBlock, uint8_t start_address, uint8_t* data, uint8_t bytes_num)
{
   for (uint8_t u8_MemoryCounter = 0; u8_MemoryCounter < bytes_num; u8_MemoryCounter++)
   {
      gau8_Memory[start_address + u8_MemoryCounter] = data[u8_MemoryCounter];
   }

   return E_EEPROM_SUCCESS;
}