/*
 * admin.h
 *
 * Created: 7/15/2021 1:05:48 AM
 *  Author: Marco
 */ 


#ifndef ATM_H_
#define ATM_H_

/******************************************************************************
*                              Includes													*
*******************************************************************************/
//#include <math.h>
#include "admin_Config.h"


#define TEST_ADMIN 0 
/******************************************************************************
*                               FUNCTION DECLARATIONS                         *
*******************************************************************************/
void ADMIN_Mode(void);
void ADMIN_Authenticate(void);
void ADMIN_Interface(ptr_uint8_t pu8_choice);
void ADMIN_SetAccount(void);
void ADMIN_GetAccount(void);
void ADMIN_SetMaxBalance(void);
void ADMIN_GetMaxBalance(void);


#endif /* ATM_H_ */