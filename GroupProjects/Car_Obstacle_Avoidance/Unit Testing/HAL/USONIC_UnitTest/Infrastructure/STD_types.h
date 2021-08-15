/*
 * File Name: STD_TYPES.h
 * Creation Date: 08/09/2021
 * Author: AMR Team
 * Description: Header File for standard data types....
 */

#ifndef __STD_TYPES__
#define __STD_TYPES__

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long int uint64_t;

typedef signed char int8_t;
typedef signed short int int16_t;
typedef signed long int int32_t;
typedef signed long long int int64_t;

typedef float float32_t;
typedef double double64_t;

typedef uint8_t* ptr_uint8_t;
typedef uint16_t* ptr_uint16_t;
typedef uint32_t* ptr_uint32_t;
typedef uint64_t* ptr_uint64_t;

typedef int8_t* ptr_int8_t;
typedef int16_t* ptr_int16_t;
typedef int32_t* ptr_int32_t;
typedef int64_t* ptr_int64_t;

typedef float* ptr_float32_t;
typedef double* ptr_double64_t;

typedef void (*Ptr_VoidFuncVoid_t)(void);
#define OK              (uint8_t)0
#define NOT_OK          (uint8_t)0
//#define NULL_PTR        ((void*)(0))
//#define NULL_TERMINATOR (uint8_t)('\0')
//#define END_OF_STRING   (uint8_t)('\0')
//#define NEW_LINE        (uint8_t)('\r')
//#define BACKSPACE       (uint8_t)('\b')

#endif
