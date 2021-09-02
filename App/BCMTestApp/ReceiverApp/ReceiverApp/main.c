/*
 * ReceiverApp.c
 *
 * Created: 8/23/2021 2:09:31 PM
 * Author : Mohamed Wagdy
 */ 

#include "BCM.h"
#include "Interrupt_Design_Pattern.h"

uint8_t DataSPI[30];
uint8_t DataI2C[30];
uint8_t u8_FlagSPI = 0;
uint8_t u8_FlagI2C = 0;
uint8_t test[10];
uint8_t test2[5] = "ABCDE";

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
void VoidFunc(void)
{
   
}

void send_SPI(void)
{
   //BCM_Send(COMM_UART_CH, 5, test2, VoidFunc);
}

void text_CBF(void)
{
   BCM_Send(COMM_SPI_CH, 10, test, send_SPI);
}

void GetRxSPI(void)
{
   u8_FlagSPI = 1;
}

void GetRxI2C(void)
{
   BCM_Send(COMM_UART_CH, 10, DataI2C, VoidFunc);
   
   //u8_FlagI2C = 1;
}

int main(void)
{
   /* Enable Globale Interrupt */
 
   INTERRUPTS_Enable();
   
   //BCM_Receive(COMM_SPI_CH, 30, DataSPI, GetRxSPI);
   BCM_Receive(COMM_I2C_CH, 10, DataI2C, GetRxI2C);
   BCM_Receive(COMM_UART_CH, 10, test, text_CBF);
   /* Replace with your application code */
   while (1)
   {
      /*if(1 == u8_FlagSPI)
      {
         if(ERROR_OK == BCM_Send(COMM_UART_CH, 30, DataSPI, text_CBF))
         {
            u8_FlagSPI = 0;
         }
      }
      if(1 == u8_FlagI2C)
      {
         if(ERROR_OK == BCM_Send(COMM_UART_CH, 30, DataI2C, text_CBF))
         {
            u8_FlagI2C = 0;
         }
      }*/
      BCM_RxMainFunction();
      BCM_TxMainFunction();
   }
}