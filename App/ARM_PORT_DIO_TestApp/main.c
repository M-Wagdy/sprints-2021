#include "PORT.h"
#include "Mcu_Hw.h"

extern const Port_ConfigType STR_PortsConfig[PORT_PINS_NUM];

void main(void)
{

    /* Start PortF Clock */
    SYSCTL_RCGCGPIO |= 0x3F;
    /* Wait till clock is running */
    while((SYSCTL_PRGPIO & 0x3F) != 0x3F);

    Port_Init(STR_PortsConfig);

    /* Superloop */
    while(1);

}
