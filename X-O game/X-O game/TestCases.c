/*****************************************************************************
* Module: X-O Game Module Test
* File Name: TestCases.c
* Description: Source file for X-O Game Module Test Cases
* Author: Mohamed Hisham Wagdy
* Date: 1/7/2021
******************************************************************************/
#include <assert.h>
#include "X_O_Game.h"

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Returns the player_marks array to it's first state.
************************************************************************************/
void ReintializePlayerMarks(void)
{
	player_marks[0] = '0';
	player_marks[1] = '1';
	player_marks[2] = '2';
	player_marks[3] = '3';
	player_marks[4] = '4';
	player_marks[5] = '5';
	player_marks[6] = '6';
	player_marks[7] = '7';
	player_marks[8] = '8';
}

/***********************************************************************************
 *                             savePlayerMark API test cases                       *
 ***********************************************************************************/

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Checks the API returns success status and the player mark is changed 
*	           to X in case of first player turn.
************************************************************************************/
void SuccessfullMarkX(void)
{
	player_turn = 1;
	ReintializePlayerMarks();
	assert(savePlayerMark(0) == E_OK);
	assert(player_marks[0] == 'X');
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Checks the API returns success status and the player mark is changed
*	           to O in case of second player turn.
************************************************************************************/
void SuccessfullMarkO(void)
{
	player_turn = 2;
	ReintializePlayerMarks();
	assert(savePlayerMark(4) == E_OK);
	assert(player_marks[4] == 'O');
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Checks that the API returns E_INVALID_POSITION in case a number more
*			   than 8 is given to it.
************************************************************************************/
void InvalidPosition(void)
{
	assert(savePlayerMark(0) == E_OK);
	assert(savePlayerMark(8) == E_OK);
	assert(savePlayerMark(9) == E_INVALID_POSITION);
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Checks that the API returns E_ALREADY_TAKEN_POSITION in case a 
*			   position is already taken and it doesn't overwrite it in case of 
*			   first player turn.
************************************************************************************/
void TakenPositionX(void)
{
	player_turn = 1;
	ReintializePlayerMarks();
	player_marks[1] = 'O';
	assert(savePlayerMark(1) == E_ALREADY_TAKEN_POSITION);
	assert(player_marks[1] == 'O');
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Checks that the API returns E_ALREADY_TAKEN_POSITION in case a
*			   position is already taken and it doesn't overwrite it in case of
*			   second player turn.
************************************************************************************/
void TakenPositionO(void)
{
	player_turn = 2;
	ReintializePlayerMarks();
	player_marks[6] = 'X';
	assert(savePlayerMark(6) == E_ALREADY_TAKEN_POSITION);
	assert(player_marks[6] == 'X');
}

/***********************************************************************************
 *                                checkWin API test cases                          *
 ***********************************************************************************/

/************************************************************************************
 * Parameters (in): None
 * Parameters (out): None
 * Return value: None
 * Description: Checks that the API returns finished game in case there is a vertical 
 *			    X line formed.
 ************************************************************************************/
void TestWinVerticalX(void)
{
	ReintializePlayerMarks();
	player_marks[0] = 'X';
	player_marks[3] = 'X';
	player_marks[6] = 'X';
	assert(checkWin() == 1);
}

/************************************************************************************
 * Parameters (in): None
 * Parameters (out): None
 * Return value: None
 * Description: Checks that the API returns finished game in case there is a horizontal
 *			    X line formed.
 ************************************************************************************/
void TestWinHorizontalX(void)
{
	ReintializePlayerMarks();
	player_marks[0] = 'X';
	player_marks[1] = 'X';
	player_marks[2] = 'X';
	assert(checkWin() == 1);
}

/************************************************************************************
 * Parameters (in): None
 * Parameters (out): None
 * Return value: None
 * Description: Checks that the API returns finished game in case there is a diagonal
 *			    X line formed.
 ************************************************************************************/
void TestWinDiagonalX(void)
{
	ReintializePlayerMarks();
	player_marks[0] = 'X';
	player_marks[4] = 'X';
	player_marks[8] = 'X';
	assert(checkWin() == 1);
}

/************************************************************************************
 * Parameters (in): None
 * Parameters (out): None
 * Return value: None
 * Description: Checks that the API returns finished game in case there is a vertical
 *			    O line formed.
 ************************************************************************************/
void TestWinVerticalO(void)
{
	ReintializePlayerMarks();
	player_marks[1] = 'O';
	player_marks[4] = 'O';
	player_marks[7] = 'O';
	assert(checkWin() == 1);
}

/************************************************************************************
 * Parameters (in): None
 * Parameters (out): None
 * Return value: None
 * Description: Checks that the API returns finished game in case there is a horizontal
 *			    O line formed.
 ************************************************************************************/
void TestWinHorizontalO(void)
{
	ReintializePlayerMarks();
	player_marks[6] = 'O';
	player_marks[7] = 'O';
	player_marks[8] = 'O';
	assert(checkWin() == 1);
}

/************************************************************************************
 * Parameters (in): None
 * Parameters (out): None
 * Return value: None
 * Description: Checks that the API returns finished game in case there is a diagonal
 *			    O line formed.
 ************************************************************************************/
void TestWinDiagonalO(void)
{
	ReintializePlayerMarks();
	player_marks[2] = 'O';
	player_marks[4] = 'O';
	player_marks[6] = 'O';
	assert(checkWin() == 1);
}

/************************************************************************************
 * Parameters (in): None
 * Parameters (out): None
 * Return value: None
 * Description: Checks that the API returns false if no line is formed.
 ************************************************************************************/
void TestWinNoLine(void)
{
	ReintializePlayerMarks();
	player_marks[0] = 'X';
	player_marks[1] = 'O';
	player_marks[2] = 'O';
	player_marks[3] = 'O';
	player_marks[4] = 'X';
	player_marks[5] = 'X';
	player_marks[6] = 'X';
	player_marks[7] = 'X';
	player_marks[8] = 'O';
	assert(checkWin() == 0);
}

void main(void)
{
	/* savePlayerMark API test cases */
	SuccessfullMarkX();
	SuccessfullMarkO();
	InvalidPosition();
	TakenPositionX();
	TakenPositionO();

	/* checkWin API test cases */
	TestWinVerticalX();
	TestWinHorizontalX();
	TestWinDiagonalX();
	TestWinVerticalO();
	TestWinHorizontalO();
	TestWinDiagonalO();
	TestWinNoLine();

	/* if no assertion error happened, print all tests passed message. */
	printf("All test cases passed successfully! :))\n");
}