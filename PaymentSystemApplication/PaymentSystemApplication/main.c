/*****************************************************************************
* Module: Payment System App Logic Module
* File Name: main.c
* Description: Payment System App Logic Module
* Author: Mohamed Hisham Wagdy
* Date: 04/07/2021
******************************************************************************/
#include "terminal.h"

void main()
{
	while (1)
	{
		/* variable to store card data */
		ST_cardData_t card_data;
		/* vairable to store terminala data */
		ST_terminalData_t terminal_data;
		/* initialize maximum allowed transaction amount */
		terminal_data.maxTransAmount = MAXIMUM_ALLOWED_AMOUNT;
		/* variable to store server response */
		uint8_t server_response;
		/* variable to store user response after the transaction (y/n) */
		uint8_t user_response;
		/* a dummy character variable used to clear stdin buffer */
		uint8_t dummy_ch;
		/* variable used while getting strings from stdin buffer */
		uint8_t counter = 0;

		printf("Please Enter Card Data: \n");
		printf("Please Enter the Card Holder Name : \n");
		
		/* store card holder name in card data */
		while ((dummy_ch = getchar()) != '\n')
		{
			card_data.cardHolderName[counter] = dummy_ch;
			counter++;
		}
		card_data.cardHolderName[counter] = '\0';
		/* defualting counter to zero again */
		counter = 0;

		printf("Please Enter the Primary Account Number: \n");
		
		/* store PAN in card data */
		while ((dummy_ch = getchar()) != '\n')
		{
			card_data.primaryAccountNumber[counter] = dummy_ch;
			counter++;
		}
		card_data.primaryAccountNumber[counter] = '\0';
		/* defualting counter to zero again */
		counter = 0;

		printf("Please card Expiry Date: \n");
		
		/* store card expiration date in card data */
		while ((dummy_ch = getchar()) != '\n')
		{
			card_data.cardExpirationDate[counter] = dummy_ch;
			counter++;
		}
		card_data.cardExpirationDate[counter] = '\0';
		/* defualting counter to zero again */
		counter = 0;

		printf("Please Enter Terminal Data: \n");
		printf("Please Enter the transaction Amount: \n");
		
		/* store transaction amount in terminal data */
		scanf_s("%f", &terminal_data.transAmount);
		/* clear stdin buffer */
		while ((dummy_ch = getchar()) != '\n' && dummy_ch != EOF);

		/* check if invalid amount is entered */
		if (check_amount(terminal_data) == INVALID_AMOUNT)
		{
			printf("The Transaction is DECLINED \n");
		}
		else
		{
			printf("Please Enter transaction Date: \n");
			
			/* store transaction in terminal data */
			while ((dummy_ch = getchar()) != '\n')
			{
				terminal_data.transactionDate[counter] = dummy_ch;
				counter++;
			}
			terminal_data.transactionDate[counter] = '\0';
			/* defualting counter to zero again */
			counter = 0;
			
			/* check if card is expired */
			if (check_expired(card_data, terminal_data) == EXPIRED)
			{
				printf("The Transaction is DECLINED \n");
			}
			else
			{
				/* send card and terminal data to server */
				server_response = send(card_data, terminal_data);
				/* check if transaction in successful */
				if (server_response == ACCEPTED_TRANSACTION)
				{
					printf("The Transaction is APPROVED. \n");
				}
				else if (server_response == DECLINED_TRANSACTION)
				{
					printf("The Transaction is DECLINED \n");
				}
				else
				{
					/* do nothing */
				}
			}
		}

		printf("Do you want to continue (y/n)?: \n");
		/* get user response */
		user_response = getchar();
		/* clear stdin buffer */
		while ((dummy_ch = getchar()) != '\n' && dummy_ch != EOF);

		/* check if user wants to make another transaction or not */
		if (user_response == 'y' || user_response == 'Y')
		{
			/* do nothing */
		}
		else if (user_response == 'n' || user_response == 'N')
		{
			break;
		}
		else
		{
			break;
		}
	}
}