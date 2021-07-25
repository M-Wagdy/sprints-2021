/*
 * Card.h
 *
 * Created: 7/24/2021 8:36:44 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __CARD_H__
#define __CARD_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../Infrastructure/utils.h"
#include "../../Mcal/Global_Interrupts/Global_Interrupts.h"
#include "../../Mcal/SPI/SPI.h"
#include "../../Firmware/Terminal/Terminal.h"
#include "../../Firmware/EEPROM/EEPROM.h"

/*- STRUCTS AND UNIONS -------------------------------------*/

/* card data struct */
typedef struct STR_cardData_t {
   uint8_t au8_CardHolderName[10];
   uint8_t au8_PAN[10];
   uint8_t au8_PIN[5];
} STR_cardData_t;

/*- FUNCTION DECLARATIONS ----------------------------------*/

/* Function that initialize Card ECU*/
void CARD_Init();

/* Function that reads from the EEPROM */
void CARD_GetUserData(STR_cardData_t * CardData);

/* Function that write to the EEPROM */
void CARD_SetUserData(void);



#endif /* __CARD_H__ */