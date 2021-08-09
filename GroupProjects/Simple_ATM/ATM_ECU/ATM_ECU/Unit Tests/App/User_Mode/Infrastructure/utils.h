/*
 * utils.h
 *
 * Created: 7/20/2021 2:37:53 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __UTILS_H__
#define __UTILS_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_types.h"

/******************************************************************************
*                               FUNCTION-LIKE MACROS                          *
*******************************************************************************/

#define SET_BIT(PORT,BIT)	  (PORT|=(1<<BIT))
#define RESET_BIT(PORT,BIT)	  (PORT&=~(1<<BIT))
#define TOGGLE_BIT(PORT,BIT)  (PORT^=(1<<BIT))
#define READ_BIT(PORT,BIT)	  (PORT&(1<<BIT))

#define Clr_Bit(reg,bit)             (reg&=~((uint8_t)1<<bit))
#define Set_Bit(reg,bit)             (reg|=((uint8_t)1<<bit))
#define Get_Bit(reg,bit)            (((reg>>bit)&(uint8_t)(0x01)))

#define REG_WRITE(REG,VAL) REG=VAL

#define BIT_LOW 0
#define BIT_HIGH 1

#define BIT_WRITE(REG,BITNO,VAL) REG=(REG&(~(BIT_HIGH<<BITNO)))|(VAL<<BITNO)
//BIT_GET TO KNOW THE BIT VALUE
#define BIT_GET(REG,BITNO) ((REG>>BITNO)&BIT_HIGH)
#define TWO_BITS_GET(REG,FIRSTBITNO) ((REG>>FIRSTBITNO)&TWO_BITS_HIGH)

//REG_GET TO KNOW THE VALUE IN THE REGISTER
#define REG_GET(REG) (REG)

#define BIT_TOGGLE(REG,BITNO) REG^=(BIT_HIGH<<BITNO)
#define REG_TOGGLE(REG) REG=~REG

/*- FUNCTION DECLARATIONS ----------------------------------*/

/* dummy delay for nearly 50ms */
void dummy_delay(void);

/* compares two strings if identical */
uint8_t StringCompare(uint8_t * str1, uint8_t * str2);

/* get string size */
uint8_t StringLength(uint8_t * string);

#endif /* __UTILS_H__ */