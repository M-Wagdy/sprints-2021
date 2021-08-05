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
#include "../../Mcal/UART/uart.h"
#include "../../Mcal/DIO/DIO.h"
#include "../../Firmware/EEPROM/EEPROM.h"

#define TEST 0

/*- STRUCTS AND UNIONS -------------------------------------*/

/* card data struct */
typedef struct STR_cardData_t {
   uint8_t au8_CardHolderName[10];
   uint8_t au8_PAN[10];
   uint8_t au8_PIN[5];
} STR_cardData_t;

/*- FUNCTION DECLARATIONS ----------------------------------*/

/* Function that initialize Card ECU*/
void CARD_Init(void);

/* Function that reads from the EEPROM */
void CARD_GetData(void);

/* Function that write to the EEPROM */
void CARD_SetData(void);

/* Function that send data through SPI */
void CARD_Send(void);

/* Function that receive data from uart */
void CARD_Receive(void);



#endif /* __CARD_H__ */