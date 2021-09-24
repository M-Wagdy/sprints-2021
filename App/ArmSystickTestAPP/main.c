#include "SYSTICK.h"
#include "CPU.h"
#include "Mcu_Hw.h"
#include "Bit_Math.h"

/************************************************************************************
* Service Name: SYSTICK_Handler
* Service ID[hex]: 0x01
* Sync/Async: Asynchronous
* Reentrancy: Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: SYSTICK ISR.
************************************************************************************/
void SYSTICK_Handler(void)
{
   /* Toggles the leds */
   PORTF_DATA ^= 0x0E;
}

void main(void)
{


   /* Switch to unprivileged mode. */
   CPU_UnPrivilegedMode();

   /* Switch to privileged mode. */
   CPU_PrivilegedMode();

   /* Start PortF Clock */
   SYSCTL_RCGCGPIO |= 0x20;
   /* Wait till clock is running */
   while((SYSCTL_PRGPIO & 0x20) == 0);
   
   /* Enable Write Access */
   PORTF_LOCK = 0x4C4F434;
   /* Set Pin 1,2,3 to output */
   SET_BIT_PER_BB(PORTF_DIR, 1);
   SET_BIT_PER_BB(PORTF_DIR, 2);
   SET_BIT_PER_BB(PORTF_DIR, 3);
   /* Digital enable Pin 1,2,3 */
   SET_BIT_PER_BB(PORTF_DEN, 1);
   SET_BIT_PER_BB(PORTF_DEN, 2);
   SET_BIT_PER_BB(PORTF_DEN, 3);
   /* Commit Changes */
   PORTF_CR = 0x1F;

   /* Init Systick Module */
   SYSTICK_Init();

   /* Superloop */
   while(1);

}
