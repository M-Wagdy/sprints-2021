/*
* STUB_EEPROM.c
*
* Created: 8/5/2021 10:49:17 AM
*  Author: Mohamed Wagdy
*/
/*- INCLUDES -----------------------------------------------*/
#include "STUB_EEPROM.h"

uint8_t gau8_Memory[255];
uint8_t gau8_MaxAmount[4];
uint8_t Mocking_data=0;
uint8_t Memory_counter=1;
/*- STUB FUNCTION DECLARATIONS ----------------------------------*/

EEPROM_ERROR_state_t EEPROM_Init(uint8_t EEPROM_CH)
{
	//NO NEED TO DO ANYTHING
   return E_EEPROM_SUCCESS;
}

EEPROM_ERROR_state_t EEPROM_ReadBytes(uint8_t EEPROM_CH, uint8_t memoryBlock, uint8_t start_address, uint8_t* data, uint8_t bytes_num)
{
    uint8_t u8_MemoryCounter;
	//READ DATA(NUMBER OF BYTE) FROM OUR BUFFER WHICH SIMULATE EEPROM
	if(memoryBlock==MEMORY_BLOCK_2)
	{
	   for ( u8_MemoryCounter = 0; u8_MemoryCounter < bytes_num; u8_MemoryCounter++)
	   {
		  data[u8_MemoryCounter] = gau8_MaxAmount[start_address + u8_MemoryCounter];
	   }		
	}
	else if(memoryBlock==MEMORY_BLOCK_4)
	{
	   for ( u8_MemoryCounter = 0; u8_MemoryCounter < bytes_num; u8_MemoryCounter++)
	   {
		  data[u8_MemoryCounter] = gau8_Memory[start_address + u8_MemoryCounter];
	   }		
	}
   return E_EEPROM_SUCCESS;
}

EEPROM_ERROR_state_t EEPROM_WriteBytes(uint8_t EEPROM_CH, uint8_t memoryBlock, uint8_t start_address, uint8_t* data, uint8_t bytes_num)
{
    uint8_t u8_MemoryCounter;
	//WRITE DATA(NUMBER OF BYTE) TO OUR BUFFER WHICH SIMULATE EEPROM
	if(memoryBlock==MEMORY_BLOCK_2)
	{
		for ( u8_MemoryCounter = 0; u8_MemoryCounter < bytes_num; u8_MemoryCounter++)
		{
		  gau8_MaxAmount[start_address + u8_MemoryCounter] = data[u8_MemoryCounter];
		}		
	}
	else if(memoryBlock==MEMORY_BLOCK_4)
	{
		for ( u8_MemoryCounter = 0; u8_MemoryCounter < bytes_num; u8_MemoryCounter++)
		{
		  gau8_Memory[start_address + u8_MemoryCounter] = data[u8_MemoryCounter];
		}		
	}


   return E_EEPROM_SUCCESS;
}
EEPROM_ERROR_state_t EEPROM_Read(uint8_t EEPROM_CH, uint8_t memoryBlock, uint8_t address, uint8_t * data)
{
	*data=Mocking_data;//NEEDD TO WRITE 'N' IN FIRST PLACE IN MEMORY TO CHECK FOR THE FUNCTION
	return E_EEPROM_SUCCESS;
}
EEPROM_ERROR_state_t EEPROM_Write(uint8_t EEPROM_CH, uint8_t memoryBlock, uint8_t address, uint8_t data)
{
	return E_EEPROM_SUCCESS;
}
