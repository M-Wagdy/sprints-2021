#include "PORT.h"
#include "DIO.h"
#include "MCU.h"
#include "IntCtrl.h"
#include "ADC.h"
#include "Mcu_Hw.h"
#include "Bit_Math.h"

volatile uint8_t x = 0;

Adc_ValueGroupType SS3_Buffer[10];

extern const Port_ConfigType STR_PortsConfig[PORT_PINS_NUM];
extern const Adc_ConfigType STR_ADCConfig[ADC_CONFIGURED_CHS];
extern const STR_Mcu_ConfigType STR_MCUClockConfig[CLOCK_SETTINGS_NUM];

void SS3_notify(void)
{
    x++;
}

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

    /* Init ADC */
    Adc_Init(STR_ADCConfig);

    SET_BIT((*(volatile uint32_t *)(ADC0_BASE_ADDRESS + ADC_SS3_CTL_OFFSET)), (3));

    Adc_SetupResultBuffer(ADC_GROUP3, SS3_Buffer);

    Adc_EnableGroupNotification(ADC_GROUP3);

    Adc_StartGroupConversion(ADC_GROUP3);

    /* Superloop */
    while(1)
    {
        while(Adc_GetGroupStatus(ADC_GROUP3) != ADC_STATUS_READY);
        Adc_StartGroupConversion(ADC_GROUP3);
    }

}
