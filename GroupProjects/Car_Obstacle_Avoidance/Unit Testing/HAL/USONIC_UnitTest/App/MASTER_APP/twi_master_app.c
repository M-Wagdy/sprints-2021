/*
 * app.c
 *
 *  Created on: Jul 18, 2021
 *      Author: Ahmed
 */
#include "twi_master_app.h"
uint8_t data=0x55;

void App_Init(void){

	TWI_Init(0);
}
void App_Update(void){
	TWI_SendChar(TWI_1,24,data);
}

