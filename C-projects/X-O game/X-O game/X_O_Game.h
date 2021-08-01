/*****************************************************************************
* Module: X-O Game Module
* File Name: X_O_Game.h
* Description: Header file for X-O Game Module
* Author: Mohamed Hisham Wagdy
* Date: 1/7/2021
******************************************************************************/
#ifndef X_O_GAME_H_
#define X_O_GAME_H_

/* Imports */
#include <stdio.h>

/******************************************************************************
 *                              X-O Game Data Types                           *
 ******************************************************************************/
typedef unsigned char bool_t;
typedef unsigned char uint8_t;
typedef unsigned char E_status;

/******************************************************************************
 *                              X-O Game Macros                               *
 ******************************************************************************/

 /* standard return values used for E_status */
#define E_OK (E_status)0
#define E_INVALID_POSITION (E_status)1
#define E_ALREADY_TAKEN_POSITION (E_status)2

/******************************************************************************
 *                              External Variables                            *
 ******************************************************************************/

/* global variable used to store X and O entered by players. */
extern uint8_t player_marks[9];

/* global variable used to determine which player turn is it and also ends the game after 9 turns. */
extern uint8_t player_turn;

/******************************************************************************
 *                              Functions Prototypes                          *
 ******************************************************************************/

/* Function to save the Mark put by player in player_marks array */
E_status savePlayerMark(uint8_t position);

/* Function prints the current player_marks array in a visual way for the players 
   while asking the next player to enter the position for the mark */
extern void drawGame(void);

/* Function checks if there is a straight/diagonal line formed of the same mark */
extern bool_t checkWin(void);

#endif /* X_O_GAME_H_ */