/*****************************************************************************
* Module: Terminal Module Test
* File Name: terminal_TestCases.c
* Description: Source file for Terminal Module Test Cases
* Author: Mohamed Hisham Wagdy
* Date: 04/07/2021
******************************************************************************/
#include <assert.h>
#include "server.h"

extern ST_accountBalance_t database[DATABASE_SIZE];

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: test the get_balance API.
************************************************************************************/
void GetBalanceTestCases(void)
{
	uint8_t pan_index;

	/* not existing balance */
	pan_index = get_balance("012345");
	assert(pan_index == PAN_DOES_NOT_EXIST);

	/* existing balance of index 0 */
	pan_index = get_balance("123456789");
	assert(pan_index == 0);

	/* existing balance of index 5 */
	pan_index = get_balance("654823719");
	assert(pan_index == 5);
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: test the transaction API.
************************************************************************************/
void TransactionTestCases(void)
{
	uint8_t pan_index;
	uint8_t transaction_status;

	pan_index = get_balance("456789123");

	/* test case 1 */
	ST_cardData_t test_case_1_card_data = { "Yehia Mohammed", "456789123","12/19" };
	ST_terminalData_t test_case_1_terminal_data = { 20.50, 5000, "27/11/2019" };
	transaction_status = transaction(test_case_1_card_data, test_case_1_terminal_data);
	/* check that the balance is updated after an accepted transaction */
	assert(abs(database[pan_index].balance- 1479.62) < 0.1);
	assert(transaction_status == ACCEPTED_TRANSACTION);

	/* test case 3 */
	ST_cardData_t test_case_3_card_data = { "Yehia Mohammed", "456789123","12/19" };
	ST_terminalData_t test_case_3_terminal_data = { 2000.00, 5000, "27/11/2019" };
	transaction_status = transaction(test_case_3_card_data, test_case_3_terminal_data);
	/* check that the balance didn't change after a declined transaction */
	assert(abs(database[pan_index].balance - 1479.62) < 0.1);
	assert(transaction_status == DECLINED_TRANSACTION);

	/* test case 4 */
	ST_cardData_t test_case_4_card_data = { "Yehia Mohammed", "456789124","12/19" };
	ST_terminalData_t test_case_4_terminal_data = { 20.50, 5000, "27/11/2019" };
	transaction_status = transaction(test_case_4_card_data, test_case_4_terminal_data);
	assert(transaction_status == DECLINED_TRANSACTION);
}

void main(void)
{
	/* run all test cases */
	GetBalanceTestCases();
	TransactionTestCases();

	/* if no assertion error happened, print all tests passed message. */
	printf("All test cases passed successfully! :))\n");
}