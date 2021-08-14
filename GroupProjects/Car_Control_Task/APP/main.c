#include "CarControl.h"

int main() {
	CAR_ERROR_state_t CAR_InitState;
   CAR_InitState = CAR_Init();
	if(CAR_InitState != E_CAR_SUCCESS)
   {
      while(1)
      {
         
      }
   }
   
   while (1) 
   {
      CAR_Update();
	}
	return 0;
}
