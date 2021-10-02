/*
 * DIOHardwareProxyPatternTestApp.c
 *
 * Created: 8/21/2021 4:20:08 PM
 * Author : Mohamed Wagdy
 */ 
/*- INCLUDES
----------------------------------------------*/
#include "DIO_HardwareProxy.h"

/*- LOCAL MACROS
------------------------------------------*/
/* Port A Start Address */
#define PORT_A_ADDR (*((volatile uint8_t *) (0x3B)))
/* Port B Start Address */
#define PORT_B_ADDR (*((volatile uint8_t *) (0x38)))

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static STR_DIOProxy_t PortA_Proxy;
static STR_DIOProxy_t PortB_Proxy;

/*- APIs IMPLEMENTATION
-----------------------------------*/
int main(void)
{
   /* Initialize Ports Hardware Proxy. */
   DIOProxy_Init(&PortA_Proxy, &PORT_A_ADDR);
   DIOProxy_Init(&PortB_Proxy, &PORT_B_ADDR);
   
   /* Configure Pins */
   DIOProxy_Configure(&PortA_Proxy, PIN_0, PIN_OUTPUT, PIN_NO_RES);
   DIOProxy_Configure(&PortA_Proxy, PIN_1, PIN_INPUT, PIN_PULLUP);
   DIOProxy_Configure(&PortB_Proxy, PIN_0, PIN_OUTPUT, PIN_NO_RES);
   DIOProxy_Configure(&PortB_Proxy, PIN_1, PIN_INPUT, PIN_PULLUP);
   
   /* Local Variables to Store Input Pins Values. */
   uint8_t Pin_A1_Data;
   uint8_t Pin_B1_Data;
    
   while (1) 
   {
      /* Get PortA Pin1 Value  */
      DIOProxy_AccessPin(&PortA_Proxy, PIN_1, &Pin_A1_Data);
      /* If Pressed. */
      if(PIN_LOW == Pin_A1_Data)
      {
         /* Set PortA Pin0 To High. */
         DIOProxy_MutatePin(&PortA_Proxy, PIN_0, PIN_HIGH);
      }
      else
      {
         /* Set PortA Pin0 To Low. */
         DIOProxy_MutatePin(&PortA_Proxy, PIN_0, PIN_LOW);
      }
       
      /* Get PortB Pin1 Value  */
      DIOProxy_AccessPin(&PortB_Proxy, PIN_1, &Pin_B1_Data);
      if(PIN_LOW == Pin_B1_Data)
      {
         /* Set PortB Pin0 To High. */
         DIOProxy_MutatePin(&PortB_Proxy, PIN_0, PIN_HIGH);
      }
      else
      {
         /* Set PortB Pin0 To Low. */
         DIOProxy_MutatePin(&PortB_Proxy, PIN_0, PIN_LOW);
      }
   }
}

