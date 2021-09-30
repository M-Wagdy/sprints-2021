#include "PORT.h"
#include "DIO.h"
#include "Mcu_Hw.h"

extern const Port_ConfigType STR_PortsConfig[PORT_PINS_NUM];

void PORTF_Handler(void)
{
    (*(volatile uint32_t *)((volatile uint8_t *)PORTF_APB_BASE_ADDRESS + PORT_DATA_OFFSET + (7<<1+2))) ^= 0x0E;
    (*(volatile uint32_t *)((volatile uint8_t *)PORTF_APB_BASE_ADDRESS + PORT_ICR_OFFSET)) |= 0x11;
}

void main(void)
{

    /* Start PortF Clock */
    SYSCTL_RCGCGPIO |= 0x3F;
    /* Wait till clock is running */
    while((SYSCTL_PRGPIO & 0x3F) != 0x3F);

//    PRI7 = (PRI7 & 0xFF1FFFFF) | (2<<21);
//    EN0  |= 0x40000000;   /* Enable NVIC Interrupt for GPIO PORTF by set bit number 30 in EN0 Register */

    Port_Init(STR_PortsConfig);

    Dio_WritePort(DIO_PORT_D, 0xAA);
    Dio_ReadPort(DIO_PORT_D);
    /* Superloop */
    while(1)
    {
        if(STD_LOW == Dio_ReadChannel(DIO_CH_PF0) && STD_LOW == Dio_ReadChannel(DIO_CH_PF4))
        {
            Dio_FlipChannel(DIO_CH_PF1);
            Dio_FlipChannel(DIO_CH_PF2);
            Dio_FlipChannel(DIO_CH_PF3);
        }
        else if(STD_LOW == Dio_ReadChannel(DIO_CH_PF0))
        {
            Dio_WriteChannel(DIO_CH_PF1, STD_HIGH);
            Dio_WriteChannel(DIO_CH_PF2, STD_HIGH);
            Dio_WriteChannel(DIO_CH_PF3, STD_HIGH);
        }
        else if(STD_LOW == Dio_ReadChannel(DIO_CH_PF4))
        {
            Dio_WriteChannel(DIO_CH_PF1, STD_LOW);
            Dio_WriteChannel(DIO_CH_PF2, STD_LOW);
            Dio_WriteChannel(DIO_CH_PF3, STD_LOW);
        }
    }

}
