#include "WDT.h"
#include "Mcu_Hw.h"

void Wdg_Callback(void)
{
    /* Dummy code to make sure it enters the function. */
    volatile int x;
    x++;
}

extern const Wdg_ConfigType STR_WDTConfig;

void main(void)
{
    Enable_Interrupts();

    volatile uint32_t * u32_DataReg = (volatile uint32_t *)(PORTF_APB_BASE_ADDRESS + PORT_DATA_ALL_PINS_OFFSET);

    /* Start PortF Clock */
    SYSCTL_RCGCUART |= 0x01;
    /* Wait till clock is running */
    while((SYSCTL_RCGCUART & 0x01) == 0);

    /* Start WDT1 Clock */
    SYSCTL_RCGCWD |= 0x02;

    /* Wait till clock is running */
    while((SYSCTL_RCGCWD & 0x02) != 0x02);

    /* Enable Interrupts. */
    PRI5 = (PRI5 & 0xFF1FFFFF) | (2<<21);
    EN0  |= (1<<18);

    /* Init WDT. */
    Wdg_Init(&STR_WDTConfig);

    /* Superloop */
    while(1)
    {
        volatile uint32_t i;
        for( i = 0; i<1500000; i++)
        {
            i=i;
        }
        /* Reload Wdg. */
        Wdg_SetTriggerCondition(1000);
    }

}
