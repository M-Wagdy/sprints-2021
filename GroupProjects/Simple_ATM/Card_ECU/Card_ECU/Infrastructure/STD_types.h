/*
 * STD_types.h
 *
 * Created: 7/7/2021 1:49:46 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __STD_TYPES_H__
#define __STD_TYPES_H__

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef unsigned char uint8_t;               /*                       0 .. 255                        */
typedef unsigned short uint16_t;             /*                        0 .. 65535                     */
typedef unsigned int uint32_t;               /*                   0 .. 4294967295                     */
typedef unsigned long long uint64_t;         /*                0..18446744073709551615                */

typedef signed char sint8_t;                 /*                      -128 .. +127                     */
typedef signed short sint16_t;               /*                    -32768 .. +32767                   */
typedef signed int sint32_t;                 /*             -2147483648 .. +2147483647                */
typedef signed long long sint64_t;           /*-9,223,372,036,854,775,808 .. 9,223,372,036,854,775,807*/

typedef uint8_t * ptr_uint8_t;

typedef void(*Ptr_VoidFuncVoid_t)(void);

/*- MACROS -------------------------------------------------*/
#define NULL_PTR        ((void*)(0))

#define END_OF_STRING   (uint8_t)('\0')
#define NULL_TERMINATOR   (uint8_t)('\0')
#define NEW_LINE        (uint8_t)('\r')
#define BACKSPACE       (uint8_t)('\b')
#define EMPTY_STRING    (uint8_t)(0x00)

#endif /* __STD_TYPES_H__ */