#pragma once
#include "Includes.h"

void stats(string playerOneName, string playerTwoName, char playerOne, char playerTwo, int playerOneColor, int playerTwoColor, int colorPlayerOne[], int colorPlayerTwo[], int tie, int& playerOneWin, int playerOneLoose, int playerTwoWin, int playerTwoLoose) {

	playerOneColorChosen(playerOneColor, colorPlayerOne);
	cout << playerOneName << termcolor::reset;
	cout << " (";
	playerOneColorChosen(playerOneColor, colorPlayerOne);
	cout << playerOne << termcolor::reset << ")" << endl;
	cout << "----------------" << endl;
	cout << "Wins: " << playerOneWin << endl;
	cout << "Loss: " << playerOneLoose << endl << endl;


	playerTwoColorChosen(playerTwoColor, colorPlayerTwo);
	cout << playerTwoName << termcolor::reset;
	cout << " (";
	playerTwoColorChosen(playerTwoColor, colorPlayerTwo); 
	cout << playerTwo << termcolor::reset << ")" << endl;
	cout << "----------------" << endl;
	cout << "Wins: " << playerTwoWin << endl;
	cout << "Loss: " << playerTwoLoose << endl << endl;


	cout << "----------------" << endl;
	cout << "Ties: " << tie << endl;

	system("pause > 0");
}
