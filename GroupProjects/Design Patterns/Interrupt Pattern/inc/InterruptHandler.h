#ifndef INTERRUPTHANDLER_H_
#define INTERRUPTHANDLER_H_

/*MACROS*/
#define NULL_PTR (void*)0
#define VECTOR_TABLE_SIZE	(20)

/*Typedefs*/
typedef unsigned char uint8_t;
typedef void(*VectorPtr)(void); /*Type Define of Pointer to function*/

/*Prototypes*/
uint8_t Install(uint8_t VectorNum, VectorPtr FunctionPointer);
uint8_t DeInstall(uint8_t VectorNum);

void InterruptHandler_1 (void);
void InterruptHandler_2 (void);
void InterruptHandler_3 (void);
void InterruptHandler_4 (void);
void InterruptHandler_5 (void);
void InterruptHandler_6 (void);
void InterruptHandler_7 (void);
void InterruptHandler_8 (void);
void InterruptHandler_9 (void);
void InterruptHandler_10(void);
void InterruptHandler_11(void);
void InterruptHandler_12(void);
void InterruptHandler_13(void);
void InterruptHandler_14(void);
void InterruptHandler_15(void);
void InterruptHandler_16(void);
void InterruptHandler_17(void);
void InterruptHandler_18(void);
void InterruptHandler_19(void);
void InterruptHandler_20(void);

#endif