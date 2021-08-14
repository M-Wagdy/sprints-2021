/*
 * SPI_Driver.c
 *
 * Created: 7/14/2021 2:05:16 PM
 * Author : Mohamed Wagdy
 */ 
/*- INCLUDES
----------------------------------------------*/
#include "Mcal/Atmega32/SPI/SPI.h"

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
/**
* @brief: This function is the master node main function.
*/
static void ECU_1_Function(void)
{
   SPI_Init(SPI_CH_0);

   SPI_TransmitChar(SPI_CH_0, 0x1F, SPI_CH_0_SS_CH_0);
}

/**
* @brief: This function is the slave node main function.
*/
static void ECU_2_Function(void)
{
   PORTA_DIR = 0xFF;

   SPI_Init(SPI_CH_0);
   
   
   uint8_t character;
   SPI_ReceiveChar(SPI_CH_0, &character, SLAVE_SS_CH);
   PORTA_DATA = character;   
}

/*- APIs IMPLEMENTATION
-----------------------------------*/


int main(void)
{
   ECU_1_Function();
   //ECU_2_Function();
}

