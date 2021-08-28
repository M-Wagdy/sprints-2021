/*
 * TransmitterApp.c
 *
 * Created: 8/23/2021 2:08:52 PM
 * Author : Mohamed Wagdy
 */ 

#include "Interrupts.h"
#include "BCM.h"
#include "BIT_MATH.h"
#include "MC_REGISTERS.h"


uint8_t DataUART[15];

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
void VoidFunc(void)
{
   
}
void text_CBF(void)
{
   REG_WRITE(PORTD_R, DataUART[9]);
   BCM_Send(COMM_I2C_CH, 10, DataUART, VoidFunc);
}

void SendReceivedUART(void)
{
//    BCM_Send(COMM_SPI_CH, 30, DataUART, text_CBF);
//    BCM_Send(COMM_I2C_CH, 30, DataUART, text_CBF);
}

int main(void)
{   
   REG_WRITE(DDRD, 0xFF);
   INTERRUPTS_Enable();
   //uint8_t DataUART[10] = "1234567890";
   //BCM_Send(COMM_SPI_CH, 10, DataUART, text_CBF);
   
   BCM_Receive(COMM_SPI_CH, 10, DataUART, text_CBF);
   while (1) 
   {
      BCM_RxMainFunction();
      BCM_TxMainFunction();
   }
}

