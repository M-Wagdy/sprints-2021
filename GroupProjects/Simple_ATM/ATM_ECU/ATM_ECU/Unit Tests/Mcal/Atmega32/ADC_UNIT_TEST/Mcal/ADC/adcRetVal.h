#ifndef _ADC_RETVAL_H_
#define _ADC_RETVAL_H_

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef   int8_t      ADC_ERROR_state_t;
/*
		This Happens when API do what is suppose to do
 */

//INIT STAT
#define INIT     (uint8_t)1
#define NOT_INIT (uint8_t)0

/*- LOCAL MACROS
------------------------------------------*/
#define           ADC_SUCCESS             (ADC_ERROR_state_t)( 0 )

/*
		This Error happens if ADC is already initialized before
*/
#define           ADC_SEC_INIT        (ADC_ERROR_state_t)( -1 )
/*
 *     This Error happens if ADC is not  initialized before
 */
#define           ADC_NOT_INIT        (ADC_ERROR_state_t)(- 2 )

/*
 *     This Error if pointer is null
 */
#define           ADC_NULL_POINTER        (ADC_ERROR_state_t)( -3 )





#endif /*_ADC_RETVAL_H_*/
