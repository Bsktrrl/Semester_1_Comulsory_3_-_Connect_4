#pragma once
#include "Includes.h"
#include <fstream>

void resetsave(char& playerOne, char& playerTwo, int& playerOneColor, int& playerTwoColor, string& playerOneName, string& playerTwoName, int& tie, int& playerOneWin, int& playerOneLoose, int& playerTwoWin, int& playerTwoLoose) {

	tie = 0;
	playerOneWin = 0;
	playerOneLoose = 0;
	playerTwoWin = 0;
	playerTwoLoose = 0;

	playerOne = 'x';
	playerTwo = 'o';

	playerOneColor = 12;
	playerTwoColor = 3;

	playerOneName = "Player 1";
	playerTwoName = "Player 2";

	cout << "player: " << playerOneName << endl;
	
	//Overwrite the saveFile info to be set to default
	ofstream saveFile ("saveFile.txt", ios::in | ios::trunc | ios::out);
	
	saveFile << "Save info: " << endl;
	saveFile << "---------------------" << endl << endl;

	saveFile << "Player 1 Name: " << endl;
	saveFile << playerOneName << endl;
	saveFile << "Player 1 Icon: " << endl;
	saveFile << playerOne << endl;
	saveFile << "player 1 Color: " << endl;
	saveFile << playerOneColor << endl;
	saveFile << "Player 1 Wins: " << endl;
	saveFile << playerOneWin << endl;
	saveFile << "Player 1 Lose: " << endl;
	saveFile << playerOneLoose << endl;
	saveFile << "---------------------" << endl << endl;

	saveFile << "Player 2 Name: " << endl;
	saveFile << playerTwoName << endl;
	saveFile << "Player 2 Icon: " << endl;
	saveFile << playerTwo << endl;
	saveFile << "player 2 Color: " << endl;
	saveFile << playerTwoColor << endl;
	saveFile << "Player 2 Wins: " << endl;
	saveFile << playerTwoWin << endl;
	saveFile << "Player 2 Lose: " << endl;
	saveFile << playerTwoLoose << endl;
	saveFile << "---------------------" << endl << endl;

	saveFile << "Ties: " << endl;
	saveFile << tie << endl;
	saveFile << "---------------------" << endl << endl;

	saveFile.close();
}

