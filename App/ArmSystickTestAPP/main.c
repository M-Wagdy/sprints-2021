#include "SYSTICK.h"
#include "Mcu_Hw.h"

/************************************************************************************
* Service Name: SYSTICK_INTHANDLER
* Service ID[hex]: 0x01
* Sync/Async: Asynchronous
* Reentrancy: Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: SYSTICK ISR.
************************************************************************************/
void SysTick_Handler(void)
{
   /* Toggles the leds */
   PORTF_DATA ^= 0x0E;
}

void main(void)
{
   /* Start PortF Clock */
   SYSCTL_RCGCGPIO |= 0x20;
   /* Wait till clock is running */
   while((SYSCTL_PRGPIO & 0x20) == 0);
   
   /* Enable Write Access */
   PORTF_LOCK = 0x4C4F434;
   /* Set Pin 1,2,3 to output */
   PORTF_DIR |= 0x0E;
   /* Digital enable Pin 1,2,3 */
   PORTF_DEN |= 0x0E;
   /* Commit Changes */
   PORTF_CR = 0x1F;

   /* Init Systick Module */
   SYSTICK_Init();

   /* Superloop */
   while(1);

}
