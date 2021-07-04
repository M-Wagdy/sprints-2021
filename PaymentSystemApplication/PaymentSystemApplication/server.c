/*****************************************************************************
* Module: Server Module
* File Name: server.c
* Description: Source file for Server Module
* Author: Mohamed Hisham Wagdy
* Date: 04/07/2021
******************************************************************************/
#include "server.h"

/* server database */
ST_accountBalance_t database[DATABASE_SIZE] = {
	{100.00 , "123456789"},
	{6000.00 , "234567891"},
	{3250.25 , "567891234"},
	{1500.12 , "456789123"},
	{500.00 , "258649173"},
	{2100.00 , "654823719"},
	{0.00 , "971362485"},
	{1.00 , "793148625"},
	{10.12 , "123123456"},
	{0.55 , "456789321"}
};

/************************************************************************************
* Parameters (in): pan - string containing the PAN.
* Parameters (out): None
* Return value: index - index of the PAN in the database.
* Description: get the balance index from the database.
************************************************************************************/
uint8_t get_balance(uint8_t * pan)
{
	uint8_t index = PAN_DOES_NOT_EXIST;
	/* loops the database */
	for (int i = 0; i < DATABASE_SIZE; i++)
	{
		/* check if this index contains the requested PAN */
		if (strcmp(pan, database[i].primaryAccountNumber) == 0)
		{
			index = i;
			break;
		}
	}
	return index;
}

/************************************************************************************
* Parameters (in): pan_index - index of the PAN in the database.
*				   amount - amount of the transaction.
* Parameters (out): None
* Return value: None
* Description: update user balance in the database.
************************************************************************************/
void update_balance(uint8_t pan_index, float amount)
{
	/* decrease the value of balance by the amount of the transaction */
	database[pan_index].balance -= amount;
}

/************************************************************************************
* Parameters (in): pan - string containing the PAN.
*				   amount - amount of the transaction.
* Parameters (out): None
* Return value: transaction_status - holds ACCEPTED_TRANSACTION or DECLINED_TRANSACTION values.
* Description: check if transaction is valid or not and return the transaction status
************************************************************************************/
uint8_t transaction(uint8_t * pan, float amount)
{
	uint8_t transaction_status;

	/* get the PAN index in the database */
	uint8_t pan_index = get_balance(pan);

	/* check if PAN is not found in the database */
	if (pan_index == PAN_DOES_NOT_EXIST)
	{
		transaction_status = DECLINED_TRANSACTION;
	}
	else
	{
		/* check if there is enough money in the balance for the transaction */
		if (database[pan_index].balance >= amount)
		{
			/* update the balance */
			update_balance(pan_index, amount);
			transaction_status = ACCEPTED_TRANSACTION;
		}
		else
		{
			transaction_status = DECLINED_TRANSACTION;
		}
	}

	/* return the transaction status */
	return transaction_status;
}

