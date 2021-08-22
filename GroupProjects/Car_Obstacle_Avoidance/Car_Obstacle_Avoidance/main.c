/*
 * USonic_Car.c
 *
 * Created: 8/9/2021 11:56:36 AM
 * Author : Mohamed Wagdy
 */ 
#include "APP/ROBOT_Control/ROBOT_Control.h"

int main(void)
{
   RC_Init();
   while(1)
   {
      RC_Update();
   }
}

