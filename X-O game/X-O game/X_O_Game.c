/*****************************************************************************
* Module: X-O Game Module
* File Name: X_O_Game.c
* Description: Source file for X-O Game Module
* Author: Mohamed Hisham Wagdy
* Date: 1/7/2021
******************************************************************************/
#include "X_O_Game.h"

/* global variable used to store X and O entered by players. */
uint8_t player_marks[9] =
{
	'0', '1', '2',
	'3', '4', '5',
	'6', '7', '8'
};

/* global variable used to determine which player turn is it and also ends the game after 9 turns. */
uint8_t player_turn = 1;

/************************************************************************************
* Parameters (in): position - the position to put the mark in.
* Parameters (out): status - error status of the function.
* Return value: E_status
* Description: Function to save the Mark put by player in player_marks array.
************************************************************************************/
E_status savePlayerMark(uint8_t position)
{
	/* variable to store the error status */
	E_status status = E_OK;
	
	/* check if the position given is valid */
	if (position > 8)
	{
		printf("Invalid position please choose another!!!\n");
		status = E_INVALID_POSITION;
	}
	/* check if the position given is not already taken */
	else if (player_marks[position] == 'X' || player_marks[position] == 'O')
	{
		printf("Position already taken please choose another\n");
		status = E_ALREADY_TAKEN_POSITION;
	}
	/* if the position given is valid and not taken */
	else
	{
		/* check if player turn not divisible by 2 then it's the first player else it's the second. */
		player_marks[position] = player_turn % 2 == 1 ? 'X' : 'O';
		/* increase the player turn by one so it's the next player turn */
		player_turn++;
	}

	/* return the error status */
	return status;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Function prints the current player_marks array in a visual way for 
*			   the players while asking the next player to enter the position for 
*			   the mark.
************************************************************************************/
void drawGame(void)
{
	/* print the game headers */
	printf("         X-O Game            \n\n");
	printf("Player 1 (X) - Player 2 (O)            \n\n");

	/* print the board with the available positions and the taken positions */
	printf("    |    |    \n");
	printf("  %c |  %c | %c \n", player_marks[0], player_marks[1], player_marks[2]);
	printf("____|____|____\n");
	printf("    |    |    \n");
	printf("  %c |  %c | %c \n", player_marks[3], player_marks[4], player_marks[5]);
	printf("____|____|____\n");
	printf("    |    |    \n");
	printf("  %c |  %c | %c \n", player_marks[6], player_marks[7], player_marks[8]); 
	printf("    |    |    \n\n");

	/* print the user which is his turn asking him to give the position he wants */
	printf
	(
		"Player %d please enter the position to put the %c mark.\n", 
		player_turn % 2 == 1 ? 1 : 2, 
		player_turn % 2 == 1 ? 'X' : 'O'
	);
}	

/************************************************************************************
* Parameters (in): None
* Parameters (out): is_win - boolean if there is a straight line formed or not yet.
* Return value: bool_t
* Description: Function to save the Mark put by player in player_marks array.
************************************************************************************/
bool_t checkWin(void)
{
	/* variable to store if there is a straight line formed or not yet. */
	bool_t is_win = 0;
	
	/* check if there is a horizontal line formed. */
	if (
			player_marks[0] == player_marks[1] && player_marks[1] == player_marks[2] ||
			player_marks[3] == player_marks[4] && player_marks[4] == player_marks[5] ||
			player_marks[6] == player_marks[7] && player_marks[7] == player_marks[8]
		)
	{
		is_win = 1;
	}
	/* check if there is a vertical line formed. */
	else if (
			player_marks[0] == player_marks[3] && player_marks[3] == player_marks[6] ||
			player_marks[1] == player_marks[4] && player_marks[4] == player_marks[7] ||
			player_marks[2] == player_marks[5] && player_marks[5] == player_marks[8]
		)
	{
		is_win = 1;
	}
	/* check if there is a diagonal line formed. */
	else if (
			player_marks[0] == player_marks[4] && player_marks[4] == player_marks[8] ||
			player_marks[2] == player_marks[4] && player_marks[4] == player_marks[6]
		)
	{
		is_win = 1;
	}
	/* if no straight line is formed. */
	else
	{
		is_win = 0;
	}

	/* return the win status */
	return is_win;
}