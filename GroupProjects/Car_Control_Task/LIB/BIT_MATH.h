/*
 * File Name: BIT_MATH.h
 * Creation Date: 07/20/2020
 * Author: Rehab
 * Description: Header File for Bit Math....
 */ 

#ifndef __BIT_MATH__
#define __BIT_MATH__

/*****************************************************GENERAL MACROS*************************************************/
//GENERAL MACROS
#define BIT_LOW 0
#define TWO_BITS_LOW 0
#define THREE_BITS_LOW 0
#define FOUR_BITS_LOW 0
#define FIVE_BITS_LOW 0
#define SIX_BITS_LOW 0
#define SEVEN_BITS_LOW 0
#define EIGHT_BITS_LOW 0


#define BIT_HIGH 1
#define TWO_BITS_HIGH 3
#define THREE_BITS_HIGH 7
#define FOUR_BITS_HIGH 15
#define FIVE_BITS_HIGH 31
#define SIX_BITS_HIGH 63
#define SEVEN_BITS_HIGH 127
#define EIGHT_BITS_HIGH 255
/********************************************************************************************************************/

/**************************************************MACROS_LIKE_FUNCTIONS*********************************************/
//MACROS_LIKE_FUNCTIONS
#define BIT_WRITE(REG,BITNO,VAL) REG=(REG&(~(BIT_HIGH<<BITNO)))|(VAL<<BITNO)
#define TWO_BITS_WRITE(REG,FIRSTBITNO,VAL) REG=(REG&(~(TWO_BITS_HIGH<<FIRSTBITNO)))|(VAL<<FIRSTBITNO)
#define THREE_BITS_WRITE(REG,FIRSTBITNO,VAL) REG=(REG&(~(THREE_BITS_HIGH<<FIRSTBITNO)))|(VAL<<FIRSTBITNO)
#define FOUR_BITS_WRITE(REG,FIRSTBITNO,VAL) REG=(REG&(~(FOUR_BITS_HIGH<<FIRSTBITNO)))|(VAL<<FIRSTBITNO)
#define FIVE_BITS_WRITE(REG,FIRSTBITNO,VAL) REG=(REG&(~(FIVE_BITS_HIGH<<FIRSTBITNO)))|(VAL<<FIRSTBITNO)
#define SIX_BITS_WRITE(REG,FIRSTBITNO,VAL) REG=(REG&(~(SIX_BITS_HIGH<<FIRSTBITNO)))|(VAL<<FIRSTBITNO)
#define SEVEN_BITS_WRITE(REG,FIRSTBITNO,VAL) REG=(REG&(~(SEVEN_BITS_HIGH<<FIRSTBITNO)))|(VAL<<FIRSTBITNO)
#define EIGHT_BITS_WRITE(REG,FIRSTBITNO,VAL) REG=(REG&(~(EIGHT_BITS_HIGH<<FIRSTBITNO)))|(VAL<<FIRSTBITNO)

#define REG_WRITE(REG,VAL) REG=VAL

//BIT_GET TO KNOW THE BIT VALUE
#define BIT_GET(REG,BITNO) ((REG>>BITNO)&BIT_HIGH)
#define TWO_BITS_GET(REG,FIRSTBITNO) ((REG>>FIRSTBITNO)&TWO_BITS_HIGH)

//REG_GET TO KNOW THE VALUE IN THE REGISTER 
#define REG_GET(REG) (REG)

#define BIT_TOGGLE(REG,BITNO) REG^=(BIT_HIGH<<BITNO)
#define REG_TOGGLE(REG) REG=~REG
/********************************************************************************************************************/ 
#endif