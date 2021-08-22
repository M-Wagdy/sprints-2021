#include <stdio.h>
#include <stdlib.h>
#include "HAL/MOTOR/MOTOR.h"
/*- LOCAL MACROS
------------------------------------------*/
#define INIT     (uint8_t)1
#define NOT_INIT (uint8_t)0
#define INVALID_MOTOR3   (uint8_t)2
#define DUMMY_SPEED      (uint8_t)30
#define INVALID_DIR     (uint8_t)2
/*----GLOBAL STATIC VARIABLES----*/
extern uint8_t gu8_InitFlag ;
void TEST1_MOTOR_init(void);
void TEST2_MOTOR_stop(void);
void TEST3_MOTOR_start(void);
void TEST4_MOTOR_Update_dir(void);
int main()
{
    TEST1_MOTOR_init();
    TEST2_MOTOR_stop();
    TEST3_MOTOR_start();
    TEST4_MOTOR_Update_dir();
    return 0;
}

/*APIs IMPLEMENTATION------------------------*/
void TEST1_MOTOR_init(void){
    /*PRE-CONDITION*/
    gu8_InitFlag=INIT;
    uint8_t error_stat;
    /*RE_INIT THE MOTOR*/
    error_stat=MOTOR_init();
    if(MOTOR_SEC_INIT==error_stat){
        printf("TEST 1-1 SUCCESS\n");
    }
    else{
        printf("TEST 1-1 FAILED\n");
    }
    gu8_InitFlag=NOT_INIT;
    /*INIT WHEN THE MOTOR IS NOT INIT BEFORE */
    error_stat=MOTOR_init();
    if(ERROR_OK==error_stat){
        printf("TEST 1-2 SUCCESS\n");
    }
    else{
        printf("TEST 1-2 FAILED\n");
    }
}
void TEST2_MOTOR_stop(void){
    gu8_InitFlag=NOT_INIT;
    uint8_t error_stat;
    /*CALL MOTOR API WITHOUT INIT THE MOTOR*/
    error_stat=MOTOR_stop(MOTOR1);
    if(MOTOR_NOT_INIT==error_stat){
        printf("TEST 2-1 SUCCESS\n");
    }
    else{
        printf("TEST 2-1 FAILED\n");
    }
     gu8_InitFlag=INIT;
     /*CALL MOTOR WITH INVALID CHANNEL*/
    error_stat=MOTOR_stop(INVALID_MOTOR3);
    if(MOTOR_INVALID_CH==error_stat){
        printf("TEST 2-2 SUCCESS\n");
    }
    else{
        printf("TEST 2-2 FAILED\n");
    }
    /*CALL MOTOR WITH CORRECT CHANNEL*/
    gu8_InitFlag=INIT;
    error_stat=MOTOR_stop(MOTOR1);
    if(ERROR_OK==error_stat){
        printf("TEST 2-3 SUCCESS\n");
    }
    else{
        printf("TEST 2-3 FAILED\n");
    }
}
void TEST3_MOTOR_start(void){
    gu8_InitFlag=NOT_INIT;
    uint8_t error_stat;
    /*CALL MOTOR API WITHOUT INIT THE MOTOR*/
    error_stat=MOTOR_start(MOTOR1,DUMMY_SPEED,MOTOR_FORWARD);
    if(MOTOR_NOT_INIT==error_stat){
        printf("TEST 3-1 SUCCESS\n");
    }
    else{
        printf("TEST 3-1 FAILED\n");
    }
     gu8_InitFlag=INIT;
    /*CALL MOTOR API WITH INVALID CHANNEL*/
    error_stat=MOTOR_start(INVALID_MOTOR3,DUMMY_SPEED,MOTOR_FORWARD);
    if(MOTOR_INVALID_CH==error_stat){
        printf("TEST 3-2 SUCCESS\n");
    }
    else{
        printf("TEST 3-2 FAILED\n");
    }
     gu8_InitFlag=INIT;
     /*CALL MOTOR API WITH INVALID DIR*/
    error_stat=MOTOR_start(MOTOR1,DUMMY_SPEED,MOTOR_INVALID_DIR);
    if(MOTOR_INVALID_DIR==error_stat){
        printf("TEST 3-3 SUCCESS\n");
    }
    else{
        printf("TEST 3-3 FAILED\n");
    }
    gu8_InitFlag=INIT;
    /*CALL MOTOR API WITH VALID DIRECATIO AND MOTOR CHANNEL*/
    error_stat=MOTOR_start(MOTOR1,DUMMY_SPEED,MOTOR_FORWARD);
    if(ERROR_OK==error_stat){
        printf("TEST 3-4 SUCCESS\n");
    }
    else{
        printf("TEST 3-4 FAILED\n");
    }
}
void TEST4_MOTOR_Update_dir(void){
    gu8_InitFlag=NOT_INIT;
    uint8_t error_stat;
    /*CALL MOTOR API WITHOUT INIT THE MOTOR*/
    error_stat=MOTOR_Update_dir(MOTOR1,MOTOR_FORWARD);
    if(MOTOR_NOT_INIT==error_stat){
        printf("TEST 4-1 SUCCESS\n");
    }
    else{
        printf("TEST 4-1 FAILED\n");
    }
     gu8_InitFlag=INIT;
     /*CALL MOTOR API WITH INVALID CHANNEL*/
    error_stat=MOTOR_Update_dir(INVALID_MOTOR3,MOTOR_FORWARD);
    if(MOTOR_INVALID_CH==error_stat){
        printf("TEST 4-2 SUCCESS\n");
    }
    else{
        printf("TEST 4-2 FAILED\n");
    }
     gu8_InitFlag=INIT;
     /*CALL MOTOR API WITH INVALID DIR*/
    error_stat=MOTOR_Update_dir(MOTOR1,MOTOR_INVALID_DIR);
    if(MOTOR_INVALID_DIR==error_stat){
        printf("TEST 4-3 SUCCESS\n");
    }
    else{
        printf("TEST 4-3 FAILED\n");
    }
    gu8_InitFlag=INIT;
    error_stat=MOTOR_Update_dir(MOTOR1,MOTOR_FORWARD);
  /*  printf("%d\n",error_stat);
    printf("%d\n",MOTOR_INVALID_DIR);*/
    if(ERROR_OK==error_stat){
        printf("TEST 4-4 SUCCESS\n");
    }
    else{
        printf("TEST 4-4 FAILED\n");
    }

}

