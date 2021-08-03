/*****************************************************************************
* Module: Server Module
* File Name: server.h
* Description: Header file for Server Module
* Author: Mohamed Hisham Wagdy
* Date: 04/07/2021
******************************************************************************/

#ifndef SERVER_H_
#define SERVER_H_

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include "std_types.h"

/******************************************************************************
 *                              Standard Data Types                           *
 ******************************************************************************/

/* card data struct */
typedef struct ST_cardData_t {
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
} ST_cardData_t;

/* terminal data struct */
typedef struct ST_terminalData_t {
	float transAmount;
	float maxTransAmount;
	uint8_t transactionDate[11];
} ST_terminalData_t;


/* transaction status enum */
typedef enum EN_transStat_t { 
	DECLINED, 
	APPROVED 
} EN_transStat_t;

/* transaction data struct */
typedef struct ST_transaction_t { 
	ST_cardData_t cardHolderData; 
	ST_terminalData_t transData; 
	EN_transStat_t transStat; 
} ST_transaction_t;

/* account balance struct */
typedef struct ST_accountBalance_t { 
	float balance; 
	uint8_t primaryAccountNumber[20]; 
} ST_accountBalance_t;

/* stack node struct */
typedef struct {
	struct node * next;
	struct ST_transaction_t data;
} node;

/******************************************************************************
 *                                 Terminal Macros                               *
 ******************************************************************************/

#define DATABASE_SIZE (uint8_t) 10
#define APPROVED_TRANSACTION (uint8_t) 0
#define INSUFFICIENT_BALANCE (uint8_t) 1
#define PAN_DOES_NOT_EXIST (uint8_t) -1
#define ACCEPTED_TRANSACTION (uint8_t)1
#define DECLINED_TRANSACTION (uint8_t)0

/******************************************************************************
 *                              Functions Prototypes                          *
 ******************************************************************************/

/* Function to get balance from database. */
uint8_t get_balance(uint8_t * pan);

/* Function to decrease transaction amount from balance */
void update_balance(uint8_t pan_index, float amount);

/* Function to recieve transaction from terminal. */
uint8_t transaction(ST_cardData_t card_data, ST_terminalData_t terminal_data);

/* save transaction history */
void save_history(ST_transaction_t transaction_data);

#endif /* SERVER_H_ */