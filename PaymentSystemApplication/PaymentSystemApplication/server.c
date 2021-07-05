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

/* initialize head pointer */
node * head = 0;

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
uint8_t transaction(ST_cardData_t card_data, ST_terminalData_t terminal_data)
{
	uint8_t transaction_status;

	/* get the PAN index in the database */
	uint8_t pan_index = get_balance(card_data.primaryAccountNumber);

	/* check if PAN is not found in the database */
	if (pan_index == PAN_DOES_NOT_EXIST)
	{
		transaction_status = DECLINED_TRANSACTION;
	}
	else
	{
		/* check if there is enough money in the balance for the transaction */
		if (database[pan_index].balance >= terminal_data.transAmount)
		{
			/* update the balance */
			update_balance(pan_index, terminal_data.transAmount);
			transaction_status = ACCEPTED_TRANSACTION;

		}
		else
		{
			transaction_status = DECLINED_TRANSACTION;
		}
	}

	/* save transaction in server */
	ST_transaction_t transaction_data;
	transaction_data.cardHolderData = card_data;
	transaction_data.transData = terminal_data;
	transaction_data.transStat = transaction_status == DECLINED_TRANSACTION? DECLINED:APPROVED;
	save_history(transaction_data);

	/* return the transaction status */
	return transaction_status;
}

/************************************************************************************
* Parameters (in): transaction_data - struct holding all transaction data.
* Parameters (out): None
* Return value: None.
* Description: insert the transaction data in it's ordered place.
************************************************************************************/
void save_history(ST_transaction_t transaction_data)
{
	/* append new node on the top of stack */
	node * new_node = (node *)malloc(sizeof(node));
	new_node->next = 0;
	new_node->data = transaction_data;

	/* if first transaction to be saved. */
	if (head == 0)
	{
		new_node->next = head;
		head = new_node;
		return;
	}

	node * temp_node = head;
	node * prev_node = 0;
	
	/* loops on transaction history */
	while (temp_node != 0)
	{
		/* compares pan number. */
		for (int i = 0; i < 20; i++)
		{
			/* if the new node PAN is smaller than the temp node */
			if (new_node->data.cardHolderData.primaryAccountNumber[i] < temp_node->data.cardHolderData.primaryAccountNumber[i])
			{
				/* if temp node is the first node. */
				if (temp_node == head)
				{
					new_node->next = temp_node;
					head = new_node;
					return;
				}
				else
				{
					new_node->next = temp_node;
					prev_node->next = new_node;
					return;
				}
			}
			/* if the new node PAN is bigger than the temp node. */
			else if (new_node->data.cardHolderData.primaryAccountNumber[i] > temp_node->data.cardHolderData.primaryAccountNumber[i])
			{
				/* if that's the last node in history */
				if (temp_node->next == 0)
				{
					temp_node->next = new_node;
					new_node->next = 0;
					return;
				}
				else
				{
					break;
				}
			}
		}
		prev_node = temp_node;
		temp_node = temp_node->next;
	}

	/* that only happens when the new node has the same PAN as the last node in history. */
	if (new_node->next == 0 && prev_node->next == 0)
	{
		prev_node->next = new_node;
	}
}