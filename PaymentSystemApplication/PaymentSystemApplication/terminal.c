/*****************************************************************************
* Module: Terminal Module
* File Name: terminal.c
* Description: Source file for Terminal Module
* Author: Mohamed Hisham Wagdy
* Date: 04/07/2021
******************************************************************************/

#include "terminal.h"

/************************************************************************************
* Parameters (in): card_data - struct holding card data.
*				   terminal_data - struct holding terminal data
* Parameters (out): None
* Return value: is_expired - holds EXPIRED or NOT_EXPIRED values.
* Description: check if an entered card is expired.
************************************************************************************/
uint8_t check_expired(ST_cardData_t card_data, ST_terminalData_t terminal_data)
{
	/* variable to store if the card date is expired or not */
	uint8_t is_expired;
	
	/* check if year is the same. */
	if (
		card_data.cardExpirationDate[3] == terminal_data.transactionDate[8] &&
		card_data.cardExpirationDate[4] == terminal_data.transactionDate[9]
		)
	{
		/* if the expiry month is bigger than the transaction month */
		if (
			card_data.cardExpirationDate[0] == terminal_data.transactionDate[3] &&
			card_data.cardExpirationDate[1] >= terminal_data.transactionDate[4]
			)
		{
			is_expired = NOT_EXPIRED;
		}
		/* if the expiry month is bigger than the transaction month */
		else if (card_data.cardExpirationDate[0] > terminal_data.transactionDate[3])
		{
			is_expired = NOT_EXPIRED;
		}
		else
		{
			is_expired = EXPIRED;
		}
	}
	/* if the expiry year is bigger than the transaction year */
	else if (
		card_data.cardExpirationDate[3] == terminal_data.transactionDate[8] && 
		card_data.cardExpirationDate[4] > terminal_data.transactionDate[9]
		)
	{
		is_expired = NOT_EXPIRED;
	}
	/* if the expiry year is bigger than the transaction year */
	else if(card_data.cardExpirationDate[3] > terminal_data.transactionDate[8])
	{
		is_expired = NOT_EXPIRED;
	}
	else
	{
		is_expired = EXPIRED;
	}

	/* returns is_expired value */
	return is_expired;
}

/************************************************************************************
* Parameters (in): terminal_data - struct holding terminal data.
* Parameters (out): None
* Return value: is_valid - holds VALID_AMOUNT or INVALID_AMOUNT values.
* Description: check if transaction amount is valid.
************************************************************************************/
uint8_t check_amount(ST_terminalData_t terminal_data)
{
	/* variable to store if the transaction amount is valid or not. */
	uint8_t is_valid;

	/* check if transaction amount is bigger than the maximum amount allowed */
	if (terminal_data.transAmount > terminal_data.maxTransAmount)
	{
		is_valid = INVALID_AMOUNT;
	}
	else
	{
		is_valid = VALID_AMOUNT;
	}

	/* return is_valid value */
	return is_valid;
}

/************************************************************************************
* Parameters (in): card_data - struct holding card data.
*				   terminal_data - struct holding terminal data
* Parameters (out): None
* Return value: transaction_status - holds ACCEPTED_TRANSACTION or DECLINED_TRANSACTION values.
* Description: sends pan number and amount to server and returns the server reposne.
************************************************************************************/
uint8_t send(ST_cardData_t card_data, ST_terminalData_t terminal_data)
{
	uint8_t transaction_status;
	
	/* sends the transaction to the server */
	transaction_status = transaction(card_data.primaryAccountNumber, terminal_data.transAmount);
	
	/* return the transaction status */
	return transaction_status;
}
