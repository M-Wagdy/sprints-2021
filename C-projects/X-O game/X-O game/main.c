/*****************************************************************************
* Module: X-O Game Logic Module
* File Name: main.c
* Description: Main Source file for X-O Game
* Author: Mohamed Hisham Wagdy
* Date: 1/7/2021
******************************************************************************/
#include <stdlib.h>
#include "X_O_Game.h"

void main(void)
{
	/* variable to store the player choice. */
	static uint8_t choice;

	/* keep running for 9 valid turns. */
	while (1)
	{
		/* draw the board. */
		drawGame();

		/* get the player choice if valid. */
		if (scanf_s("%d", &choice) == 0)
		{
			/* clear the input buffer */
			scanf_s("%*[^\n]");
			/* put invalid integer in choice variable */
			choice = 9;
		}
		
		/* clear the previous screen. */
		system("cls");

		/* save the player choice. */
		savePlayerMark(choice);

		/* check if now there is a straight line formed */
		if (checkWin())
		{
			/* print which player won determined from which player is not his turn now. */
			printf("Player %d Wins!!\n", player_turn % 2 == 0 ? 1 : 2);
			/* prints a message to tell the user to close and reopen the game if he/she 
			   want to play a new game */
			printf("Close the console and open the game again for a new game\n");
			/* stuck in infinite loop till the user close the console */
			while (1){};
		}
		/* if turns are 10 and there isn't a straigh line formed then it's a draw. */
		else if (player_turn == 10)
		{
			/* prints draw */
			printf("Draw!\n");
			/* prints a message to tell the user to close and reopen the game if he/she
			   want to play a new game */
			printf("Close the console and open the game again for a new game\n");
			/* stuck in infinite loop till the user close the console */
			while (1) {};
		}
	}
}