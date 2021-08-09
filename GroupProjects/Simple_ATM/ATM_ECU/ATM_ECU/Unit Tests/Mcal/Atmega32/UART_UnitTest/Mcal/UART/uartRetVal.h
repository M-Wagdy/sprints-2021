#ifndef _ADC_RETVAL_H_
#define _ADC_RETVAL_H_

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef   int8_t      UART_ERROR_state_t;


//INIT STAT
#define INIT     (uint8_t)1
#define NOT_INIT (uint8_t)0

/*- LOCAL MACROS
------------------------------------------*/
/*
		This Happens when API do what is suppose to do
 */
#define           UART_SUCCESS             (UART_ERROR_state_t)( 0 )

/*
		This Error happens if UART is already initialized before
*/
#define           UART_SEC_INIT             (UART_ERROR_state_t)( -1 )
/*
 *     This Error happens if UART is not  initialized before
 */
#define           UART_NOT_INIT             (UART_ERROR_state_t)(- 2 )

/*
 *     This Error happens if pointer is null
 */
#define           UART_NULL_POINTER         (UART_ERROR_state_t)( -3 )
/*
*      This Error happens if INVALID UART CHANNEL
*/
#define           UART_INVALID_CHANNEL      (UART_ERROR_state_t)( -4 )
/*
*      This Error happens if INVALID UART INTERRUPT CHANNEL
*/
#define           UART_INTERRUPT_CHANNEL     (UART_ERROR_state_t)( -5 )



#endif /*_ADC_RETVAL_H_*/
