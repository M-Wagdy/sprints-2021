/*
 * DIOHardwareProxyPatternTestApp.c
 *
 * Created: 8/21/2021 4:20:08 PM
 * Author : Mohamed Wagdy
 */ 

#include "DIO_HardwareProxy.h"

#define PORT_A_ADDR (*((volatile uint8_t *) (0x3B)))
#define PORT_B_ADDR (*((volatile uint8_t *) (0x38)))

static STR_DIOProxy_t PortA_Proxy;
static STR_DIOProxy_t PortB_Proxy;

int main(void)
{
   
    DIOProxy_Init(&PortA_Proxy, &PORT_A_ADDR);
    DIOProxy_Init(&PortB_Proxy, &PORT_B_ADDR);
    
    DIOProxy_Configure(&PortA_Proxy, PIN_0, PIN_OUTPUT, PIN_NO_RES);
    DIOProxy_Configure(&PortA_Proxy, PIN_1, PIN_INPUT, PIN_PULLUP);
    DIOProxy_Configure(&PortB_Proxy, PIN_0, PIN_OUTPUT, PIN_NO_RES);
    DIOProxy_Configure(&PortB_Proxy, PIN_1, PIN_INPUT, PIN_PULLUP);
    
    uint8_t Pin_A1_Data;
    uint8_t Pin_B1_Data;
    
    while (1) 
    {
       DIOProxy_AccessPin(&PortA_Proxy, PIN_1, &Pin_A1_Data);
       if(PIN_LOW == Pin_A1_Data)
       {
          DIOProxy_MutatePin(&PortA_Proxy, PIN_0, PIN_HIGH);
       }
       else
       {
          DIOProxy_MutatePin(&PortA_Proxy, PIN_0, PIN_LOW);
       }
       
       DIOProxy_AccessPin(&PortB_Proxy, PIN_1, &Pin_B1_Data);
       if(PIN_LOW == Pin_B1_Data)
       {
          DIOProxy_MutatePin(&PortB_Proxy, PIN_0, PIN_HIGH);
       }
       else
       {
          DIOProxy_MutatePin(&PortB_Proxy, PIN_0, PIN_LOW);
       }
    }
}

