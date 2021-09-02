/*
 * TransmitterApp.c
 *
 * Created: 8/23/2021 2:08:52 PM
 * Author : Mohamed Wagdy
 */ 

#include "Interrupts.h"
#include "BCM.h"

uint8_t gau8_DataBuffer[15];

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
void I2C_TXCallback(void)
{
   /*Do Nothing*/
}
void SPI_RXCallback(void)
{

   BCM_Send(COMM_I2C_CH, 10, gau8_DataBuffer, I2C_TXCallback);
}

int main(void)
{   

   INTERRUPTS_Enable();

   BCM_Receive(COMM_SPI_CH, 10, gau8_DataBuffer, SPI_RXCallback);
   while (TRUE) 
   {
      BCM_RxMainFunction();
      BCM_TxMainFunction();
   }
}

