/*
 * usonicRetVal.h
 *
 *  Created on: Aug 9, 2021
 *      Author: Ahmed
 */

#ifndef MOTORRETVAL_H_
#define MOTORRETVAL_H_

/*- INCLUDES -----------------------------------------------*/
//#include"../../Infrastructure/TypeDef.h"
/*- PRIMITIVE TYPES ----------------------------------------*/
typedef   uint8_t      MOTOR_ERROR_state_t;
/*- LOCAL MACROS------------------------------------------*/
//INIT STAT
#define INIT     (uint8_t)1
#define NOT_INIT (uint8_t)0


/*
		This Happens when API do what is suppose to do
 */
#define           MOTOR_SUCCESS             (MOTOR_ERROR_state_t)( 0 )

/*
		This Error happens if USONIC is already initialized before
*/
#define           MOTOR_SEC_INIT             (MOTOR_ERROR_state_t)( -1 )
/*
 *     This Error happens if USONIC is not  initialized before
 */
#define           MOTOR_NOT_INIT             (MOTOR_ERROR_state_t)(- 2 )
/*
 *     This Error happens if USONIC is not  initialized before
 */
#define           MOTOR_INVALID_DIR             (MOTOR_ERROR_state_t)(- 3 )
/*
 *     This Error happens if USONIC is not  initialized before
 */
#define           MOTOR_INVALID_CH             (MOTOR_ERROR_state_t)(- 4 )




#endif /* MOTORRETVAL_H_ */
