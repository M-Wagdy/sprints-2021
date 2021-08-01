/*****************************************************************************
* Module: Terminal Module Test
* File Name: terminal_TestCases.c
* Description: Source file for Terminal Module Test Cases
* Author: Mohamed Hisham Wagdy
* Date: 04/07/2021
******************************************************************************/
#include <assert.h>
#include "terminal.h"

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: test the check_expired API.
************************************************************************************/
void CheckExpiredTestCases(void)
{
	uint8_t is_expired;
	
	/* same year and month in both card and terminal data */
	ST_cardData_t same_month_and_year_card_data = { "TEST", "123456789","04/21" };
	ST_terminalData_t same_month_and_year_terminal_data = { 0, MAXIMUM_ALLOWED_AMOUNT, "07/04/2021" };
	is_expired = check_expired(same_month_and_year_card_data, same_month_and_year_terminal_data);
	assert(is_expired == NOT_EXPIRED);

	/* same year and different month in card and terminal data */
	ST_cardData_t expired_differnet_month_card_data = { "TEST", "123456789","03/21" };
	ST_terminalData_t expired_differnet_month_terminal_data = { 0, MAXIMUM_ALLOWED_AMOUNT, "07/04/2021" };
	is_expired = check_expired(expired_differnet_month_card_data, expired_differnet_month_terminal_data);
	assert(is_expired == EXPIRED);

	/* same year and different month in card and terminal data */
	ST_cardData_t not_expired_differnet_month_card_data = { "TEST", "123456789","05/21" };
	ST_terminalData_t not_expired_differnet_month_terminal_data = { 0, MAXIMUM_ALLOWED_AMOUNT, "07/04/2021" };
	is_expired = check_expired(not_expired_differnet_month_card_data, not_expired_differnet_month_terminal_data);
	assert(is_expired == NOT_EXPIRED);

	/* different year and same month in card and terminal data */
	ST_cardData_t expired_differnet_year_card_data = { "TEST", "123456789","04/19" };
	ST_terminalData_t expired_differnet_year_terminal_data = { 0, MAXIMUM_ALLOWED_AMOUNT, "07/04/2021" };
	is_expired = check_expired(expired_differnet_year_card_data, expired_differnet_year_terminal_data);
	assert(is_expired == EXPIRED);

	/* different year and same month in card and terminal data */
	ST_cardData_t not_expired_differnet_year_card_data = { "TEST", "123456789","04/22" };
	ST_terminalData_t not_expired_differnet_year_terminal_data = { 0, MAXIMUM_ALLOWED_AMOUNT, "07/04/2021" };
	is_expired = check_expired(not_expired_differnet_year_card_data, not_expired_differnet_year_terminal_data);
	assert(is_expired == NOT_EXPIRED);

	/* different year and different month in card and terminal data */
	ST_cardData_t expired_differnet_month_and_year_card_data = { "TEST", "123456789","12/19" };
	ST_terminalData_t expired_differnet_month_and_year_terminal_data = { 0, MAXIMUM_ALLOWED_AMOUNT, "07/04/2021" };
	is_expired = check_expired(expired_differnet_year_card_data, expired_differnet_year_terminal_data);
	assert(is_expired == EXPIRED);

	/* different year and different month in card and terminal data */
	ST_cardData_t not_expired_differnet_month_and_year_card_data = { "TEST", "123456789","11/22" };
	ST_terminalData_t not_expired_differnet_month_and_year_terminal_data = { 0, MAXIMUM_ALLOWED_AMOUNT, "07/04/2021" };
	is_expired = check_expired(not_expired_differnet_year_card_data, not_expired_differnet_year_terminal_data);
	assert(is_expired == NOT_EXPIRED);

	/* test case 2 */
	ST_cardData_t test_case_2_card_data = { "Yehia Mohammed", "456789123", "10/19" };
	ST_terminalData_t test_case_2_terminal_data = { 20.50, MAXIMUM_ALLOWED_AMOUNT, "27/11/2019" };
	is_expired = check_expired(test_case_2_card_data, test_case_2_terminal_data);
	assert(is_expired == EXPIRED);
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: test the check_amount API.
************************************************************************************/
void CheckAmountTestCases(void)
{
	uint8_t is_valid;

	/* allowed amount */
	ST_terminalData_t allowed_terminal_data = { 3000.166, MAXIMUM_ALLOWED_AMOUNT, "07/04/2021" };
	is_valid = check_amount(allowed_terminal_data);
	assert(is_valid == VALID_AMOUNT);

	/* maximum allowed amount exactly */
	ST_terminalData_t max_allowed_terminal_data = { 5000.00, MAXIMUM_ALLOWED_AMOUNT, "07/04/2021" };
	is_valid = check_amount(max_allowed_terminal_data);
	assert(is_valid == VALID_AMOUNT);

	/* invalid amount  */
	ST_terminalData_t not_allowed_terminal_data = { 7000.0, MAXIMUM_ALLOWED_AMOUNT, "07/04/2021" };
	is_valid = check_amount(not_allowed_terminal_data);
	assert(is_valid == INVALID_AMOUNT);

	/* test case 5 */
	ST_terminalData_t test_case_5_terminal_data = { 6000, MAXIMUM_ALLOWED_AMOUNT, "27/11/2019" };
	is_valid = check_amount(test_case_5_terminal_data);
	assert(is_valid == INVALID_AMOUNT);
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: test the send API.
************************************************************************************/
void SendTestCases(void)
{
	uint8_t server_response;

	/* test case 1 */
	ST_cardData_t test_case_1_card_data = { "Yehia Mohammed", "456789123", "12/19" };
	ST_terminalData_t test_case_1_terminal_data = { 20.50, MAXIMUM_ALLOWED_AMOUNT, "27/11/2019" };
	server_response = send(test_case_1_card_data, test_case_1_terminal_data);
	assert(server_response == ACCEPTED_TRANSACTION);

	/* test case 3 */
	ST_cardData_t test_case_3_card_data = { "Yehia Mohammed", "456789123", "12/19" };
	ST_terminalData_t test_case_3_terminal_data = { 2000.00, MAXIMUM_ALLOWED_AMOUNT, "27/11/2019" };
	server_response = send(test_case_3_card_data, test_case_3_terminal_data);
	assert(server_response == DECLINED_TRANSACTION);

	/* test case 4 */
	ST_cardData_t test_case_4_card_data = { "Yehia Mohammed", "456789124", "12/19" };
	ST_terminalData_t test_case_4_terminal_data = { 20.50, MAXIMUM_ALLOWED_AMOUNT, "27/11/2019" };
	server_response = send(test_case_4_card_data, test_case_4_terminal_data);
	assert(server_response == DECLINED_TRANSACTION);
}

void main(void)
{
	/* run all test cases */
	CheckExpiredTestCases();
	CheckAmountTestCases();
	SendTestCases();

	/* if no assertion error happened, print all tests passed message. */
	printf("All test cases passed successfully! :))\n");
}