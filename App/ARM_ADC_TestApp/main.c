#include "PORT.h"
#include "DIO.h"
#include "MCU.h"
#include "IntCtrl.h"
#include "ADC.h"
#include "Mcu_Hw.h"
#include "Bit_Math.h"

extern const Port_ConfigType STR_PortsConfig[PORT_PINS_NUM];
extern const Adc_ConfigType STR_ADCConfig[ADC_CONFIGURED_CHS];
extern const STR_Mcu_ConfigType STR_MCUClockConfig[CLOCK_SETTINGS_NUM];

void main(void)
{
    /* Init MCU */
    Mcu_Init(STR_MCUClockConfig);
    Mcu_InitClock(0);

    /* Init Interrupts */
    IntCtrl_Init();
    IntCtrl_EnableGlobal();

    /* Init Pins. */
    Port_Init(STR_PortsConfig);

    /* Init Timers */
    Adc_Init(STR_ADCConfig);

    SET_BIT((*(volatile uint32_t *)(ADC0_BASE_ADDRESS + ADC_SS3_CTL_OFFSET)), (3));

    SET_BIT((*(volatile uint32_t *)(ADC0_BASE_ADDRESS + ADC_ACTIVE_OFFSET)), (3));

    SET_BIT((*(volatile uint32_t *)(ADC0_BASE_ADDRESS + ADC_PSSI_OFFSET)), (3));
    /* Superloop */
    while(1)
    {

    }

}
