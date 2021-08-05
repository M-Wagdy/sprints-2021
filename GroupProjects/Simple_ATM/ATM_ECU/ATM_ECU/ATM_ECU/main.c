/*
 * ATM_ECU.c
 *
 * Created: 7/28/2021 3:54:21 PM
 * Author : Mohamed Wagdy
 */ 

#include "App/ATM/ATM.h"

int main(void)
{
   ATM_Init();

   while (1)
   {
      ATM_SelectMode();  
   }
}

