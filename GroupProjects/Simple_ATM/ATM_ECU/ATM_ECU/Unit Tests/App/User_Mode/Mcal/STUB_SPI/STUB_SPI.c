/*
* STUB_SPI.c
*
* Created: 8/5/2021 10:49:17 AM
*  Author: Mohamed Wagdy
*/

/*- INCLUDES -----------------------------------------------*/
#include "STUB_SPI.h"

/*- STUB FUNCTION DECLARATIONS ----------------------------------*/
uint8_t CARD_PAN[10]={'0','1','2','3','4','5','6','7','8',NULL_TERMINATOR};
uint8_t CARD_PIN[5]={'0','1','2','3',NULL_TERMINATOR};

uint8_t flag =0;
uint8_t SPI_Init(uint8_t SpiNumber)
{
   return 1;
}

uint8_t SPI_EnableInterrupt(uint8_t SpiNumber)
{
   return 1;
}

uint8_t SPI_Set_TX_CompleteCallback(uint8_t SpiNumber, void(*callBack)(void))
{
   return 1;
}

uint8_t SPI_TransmitString(uint8_t SpiNumber, ptr_uint8_t TxString, uint8_t slave_CH)
{
   return 1;
}
uint8_t SPI_ReceiveString(uint8_t SpiNumber,ptr_uint8_t RxString,uint8_t slave_CH){
    uint8_t au8_counter=0;
    if(0== flag){
            for(au8_counter=0;au8_counter<=9;au8_counter++){
                RxString[au8_counter]=CARD_PAN[au8_counter];//should fill the PAN 0->8
            }
            flag=1;
    }
    else if(1==flag){
            for(au8_counter=0;au8_counter<4;au8_counter++){
                RxString[au8_counter]=CARD_PIN[au8_counter];//should fill the PAN 0->3
            }
            flag=0;

    }
}
