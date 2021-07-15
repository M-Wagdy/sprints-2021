/*
 * MCUs_Over_SPI.c
 *
 * Created: 7/15/2021 7:32:16 PM
 * Author : Mohamed Wagdy
 */ 
/*- INCLUDES
----------------------------------------------*/
#include "Mcal/UART/UART.h"
#include "Mcal/SPI/SPI.h"

/*- LOCAL MACROS
------------------------------------------*/
#define MAX_STRING_SIZE (uint8_t)(254)

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/
static void ECU_1_MasterMain(void);
static void ECU_2_SlaveMain(void);

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/**
* @brief: This function is the master node main function.
*/
static void ECU_1_MasterMain(void)
{
   uint8_t string[MAX_STRING_SIZE];
   
   UART_Init(UART_CH_0);
   SPI_Init(SPI_CH_0);
   
   while (1)
   {
      UART_ReceiveString(UART_CH_0, string);
      UART_TransmitString(UART_CH_0, string);
      SPI_TransmitString(SPI_CH_0, string, SPI_CH_0_SS_CH_0);
   }
}

/**
* @brief: This function is the slave node main function.
*/
static void ECU_2_SlaveMain(void)
{
   uint8_t string[MAX_STRING_SIZE];
   
   UART_Init(UART_CH_0);
   SPI_Init(SPI_CH_0);
   
   while (1)
   {
      SPI_ReceiveChar(SPI_CH_0, string, SLAVE_SS_CH);
      UART_TransmitString(UART_CH_0, string);
   }
}

int main(void)
{
   ECU_1_MasterMain();
}

