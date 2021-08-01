/*****************************************************************************
* Module: Terminal Module
* File Name: terminal.h
* Description: Header file for Terminal Module
* Author: Mohamed Hisham Wagdy
* Date: 04/07/2021
******************************************************************************/

#ifndef TERMINAL_H_
#define TERMINAL_H_

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include "std_types.h"
#include "server.h"

/******************************************************************************
 *                                 Terminal Macros                               *
 ******************************************************************************/

#define NOT_EXPIRED (uint8_t)1
#define EXPIRED (uint8_t)0
#define VALID_AMOUNT (uint8_t)1
#define INVALID_AMOUNT (uint8_t)0
#define MAXIMUM_ALLOWED_AMOUNT (float)5000.0

/******************************************************************************
 *                              Functions Prototypes                          *
 ******************************************************************************/

/* Function to check if card is expired. */
uint8_t check_expired(ST_cardData_t card_data, ST_terminalData_t terminal_data);

/* Function to check if transaction amount is valid */
uint8_t check_amount(ST_terminalData_t terminal_data);

/* Function to send transaction data to server. */
uint8_t send(ST_cardData_t card_data, ST_terminalData_t terminal_data);

#endif /* TERMINAL_H_ */