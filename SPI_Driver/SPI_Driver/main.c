/*
 * SPI_Driver.c
 *
 * Created: 7/14/2021 2:05:16 PM
 * Author : Mohamed Wagdy
 */ 
/*- INCLUDES
----------------------------------------------*/
#include "Mcal/SPI/SPI.h"

/*- LOCAL MACROS
------------------------------------------*/
#define  PORTA_DATA      (*((volatile uint8_t *) (0x3B)))
#define  PORTA_DIR       (*((volatile uint8_t *) (0x3A)))

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/
static void ECU_1_Function(void);
static void ECU_2_Function(void);

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
static void ECU_1_Function(void)
{
   SPI_Init();
   
   SPI_SendChar(0x1F);
}

static void ECU_2_Function(void)
{
   PORTA_DIR = 0xFF;

   SPI_Init();

   uint8_t character;
   SPI_ReadChar(&character);
   PORTA_DATA = character;   
}

/*- APIs IMPLEMENTATION
-----------------------------------*/


int main(void)
{
   ECU_1_Function();
   //ECU_2_Function();
}

