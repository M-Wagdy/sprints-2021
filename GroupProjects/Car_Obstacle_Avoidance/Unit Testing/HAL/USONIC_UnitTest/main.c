#include <stdio.h>
#include <stdlib.h>
#include"Firmware/USONIC/usonic.h"
extern uint8_t gu8_InitFlag ;
void TEST1_USONICINIT(void);
void TEST2_USONICGETDISTANC(void);
float32_t distance =0;


int main()
{
    TEST1_USONICINIT();
    TEST2_USONICGETDISTANC();
    return 0;
}
void TEST1_USONICINIT(void){

    gu8_InitFlag=INIT;
    uint8_t error_stat;
    error_stat=USONIC_Init();
    if(USONIC_SEC_INIT==error_stat){
        printf("TEST 1-1 SUCCESS\n");
    }
    else{
        printf("TEST 1-1 FAILED\n");
    }

    gu8_InitFlag=NOT_INIT;

    error_stat=USONIC_Init();
    if(USONIC_SUCCESS==error_stat){
        printf("TEST 1-2 SUCCESS\n");
    }
    else{
        printf("TEST 1-2 FAILED\n");
    }
}



void TEST2_USONICGETDISTANC(void){

    gu8_InitFlag=NOT_INIT;
    uint8_t error_stat;
    error_stat=USONIC_GetDistance(&distance);
    if(USONIC_NOT_INIT==error_stat){
        printf("TEST 2-1 SUCCESS\n");
    }
    else{
        printf("TEST 2-1 FAILED\n");
    }
    gu8_InitFlag=INIT;
    error_stat=USONIC_GetDistance(NULL_PTR);
    if(USONIC_NULL_POINTER==error_stat){
        printf("TEST 2-2 SUCCESS\n");
    }
    else{
        printf("TEST 2-2 FAILED\n");
    }
    gu8_InitFlag=INIT;
    /*ICU TAKES AT LEAST 4 TIMES CALLING TO CALCULATE THE TIME */
    error_stat=USONIC_GetDistance(&distance);
    error_stat=USONIC_GetDistance(&distance);
    error_stat=USONIC_GetDistance(&distance);
    if(USONIC_PENDING==error_stat){
        printf("TEST 2-3 SUCCESS\n");
    }
    else{
        printf("TEST 2-3 FAILED\n");
    }
    error_stat=USONIC_GetDistance(&distance);
    if(OK==error_stat){
        printf("TEST 2-4 SUCCESS\n");
    }
    else{
        printf("TEST 2-4 FAILED\n");
    }
//printf("distancce is %d\n",(uint32_t)distance);







}
