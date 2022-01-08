#pragma once
#include "Includes.h"

class PlayerStats
{
public:

	string playerOneName{}; //Name of player 1
	char playerOne{}; //Player 1 icon
	int playerOneColor{}; //Player 1 color
	int playerOneWin{}; //Stats over player 1 wins
	int playerOneLoose{}; //Stats over player 1 loss

	//Retreave player 2 info from .txt
	string playerTwoName{}; //Name of player 2
	char playerTwo{}; //Player 2 icon
	int playerTwoColor{}; //Player 2 color
	int playerTwoWin{}; //Stats over player 2 wins
	int playerTwoLoose{}; //Stats over player 2 loss

	//Retreave other info from .txt
	int tie{}; //Stats over ties
};

PlayerStats playerStats{};