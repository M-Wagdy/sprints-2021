/*
 * I2C_Driver.c
 *
 * Created: 7/16/2021 9:29:12 AM
 * Author : Mohamed Wagdy
 */ 

#include "Mcal/Atmega32/I2C/I2C.h"

/*- LOCAL MACROS
------------------------------------------*/
#define  PORTA_DATA        (*((volatile uint8_t *) (0x3B)))
#define  PORTA_DIR         (*((volatile uint8_t *) (0x3A)))
#define  SLAVE_ADDR        (uint8_t)(0xA0)

/**
* @brief: Master node main function.
*/
void master(void)
{
   uint8_t status;
   /* initialize I2C */
   I2C_Init(I2C_CH_0);
   
   /* send start condition */
   I2C_Start(I2C_CH_0);
   
   /* get the status */
   I2C_Status(I2C_CH_0, &status);
   /* make sure the master node got the bus. */
   if(status != I2C_STATUS_START)
   {
      return;
   }
   /* send the slave address + master write */
   I2C_Write(I2C_CH_0, SLAVE_ADDR);
   /* get the status */
   I2C_Status(I2C_CH_0, &status);
   /* make sure the master node got ack from slave. */
   if(status != I2C_STATUS_T_ACK_ADDR)
   {
      return;
   }
   /* send the data bytes */
   I2C_Write(I2C_CH_0, 0x97);
   /* get the status */
   I2C_Status(I2C_CH_0,&status);
   /* make sure the master node got ack from slave. */
   if(status != I2C_STATUS_T_ACK_DATA)
   {
      return;
   }
   /* stop condition */
   I2C_Stop(I2C_CH_0);
}

/**
* @brief: Slave node main function.
*/
void slave(void)
{
   /* set all PORTA pins to output */
   PORTA_DIR = 0xFF;
   
   uint8_t data;
   uint8_t status;
   
   /* set slave address */
   I2C_SetSlaveAddress(I2C_CH_0, SLAVE_ADDR);
   /* initialize I2C */
   I2C_Init(I2C_CH_0);
   /* get data from bus */
   I2C_ReadAck(I2C_CH_0, &data);
   /* get the status */
   I2C_Status(I2C_CH_0, &status);
   /* make sure the slave node received it's address and send ack to master. */
   if(status != I2C_STATUS_R_ACK_ADDR)
   {
      return;
   }
   /* get data from bus */
   I2C_ReadAck(I2C_CH_0, &data);
   /* get the status */
   I2C_Status(I2C_CH_0, &status);
   /* make sure the slave node received the data and send ack to master. */
   if(status != I2C_STATUS_R_ACK_DATA)
   {
      return;
   }
   /* set portA pins to the received data */
   PORTA_DATA = data;
}

int main(void)
{
   slave();
}

