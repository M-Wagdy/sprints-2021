/*
 * usonicRetVal.h
 *
 *  Created on: Aug 9, 2021
 *      Author: Ahmed
 */

#ifndef USONICRETVAL_H_
#define USONICRETVAL_H_

/*- INCLUDES -----------------------------------------------*/
#include"../../Infrastructure/TypeDef.h"
/*- PRIMITIVE TYPES ----------------------------------------*/
typedef   uint8_t      USONIC_ERROR_state_t;


//INIT STAT
#define INIT     (uint8_t)1
#define NOT_INIT (uint8_t)0

/*- LOCAL MACROS
------------------------------------------*/
/*
		This Happens when API do what is suppose to do
 */
#define           USONIC_SUCCESS             (USONIC_ERROR_state_t)( 0 )

/*
		This Error happens if UART is already initialized before
*/
#define           USONIC_SEC_INIT             (USONIC_ERROR_state_t)( -1 )
/*
 *     This Error happens if UART is not  initialized before
 */
#define           USONIC_NOT_INIT             (USONIC_ERROR_state_t)(- 2 )

/*
 *     This Error happens if pointer is null
 */
#define           USONIC_NULL_POINTER         (USONIC_ERROR_state_t)( -3 )
/*
*      This Error happens if INVALID UART CHANNEL
*/
#define           USONIC_PENDING      (USONIC_ERROR_state_t)( -4 )


#endif /* USONICRETVAL_H_ */
