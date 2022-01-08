#pragma once
#include "Includes.h"
#include "Stats.h"
#include "Settings.h"
#include "Save.h"
#include "ResetSave.h"
#include "PlayerStatsInfo.h"
#include <fstream>

void menu() {
	#pragma region Inportant variables
	bool aiRunning{};
	bool trueAIRunning{};
	bool save{};
	bool gameRunning{true};
	int mainMenuSelect{};
	string mainMenuSelectIcon{"->"};

	int tie{}; //Stats over ties
	int playerOneWin{}; //Stats over player 1 wins
	int playerOneLoose{}; //Stats over player 1 loss
	int playerTwoWin{}; //Stats over player 2 wins
	int playerTwoLoose{}; //Stats over player 2 loss

	char playerOne{'x'}; //Player 1 icon
	char playerTwo{'o'}; //Player 2 icon

	int playerOneColor{12}; //Player 1 color
	int playerTwoColor{3}; //Player 2 color

	string playerOneName{"Player 1"}; //Name of player 1
	string playerTwoName{"Player 2"}; //Name of player 2

	int colorPlayerOne[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 }; //Range of colors
	int colorPlayerTwo[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 }; //Range of colors
	#pragma endregion
	
	#pragma region Implement saveFile
	ifstream saveFile;
	saveFile.open("saveFile.txt", ios::in);

	vector<string> playerStatsString{};

	if (saveFile.is_open())
	{
		string buff{};

		playerStatsString.clear();
		while ((getline(saveFile, buff)))
			playerStatsString.push_back(buff);
		
		//Retreave player 1 info from .txt
		playerOneName = playerStatsString[4];
		playerOne = playerStatsString[6][0];
		playerOneColor = stoi(playerStatsString[8]);
		playerOneWin = stoi(playerStatsString[10]);
		playerOneLoose = stoi(playerStatsString[12]);

		//Retreave player 2 info from .txt
		playerTwoName = playerStatsString[16];
		playerTwo = playerStatsString[18][0];
		playerTwoColor = stoi(playerStatsString[20]);
		playerTwoWin = stoi(playerStatsString[22]);
		playerTwoLoose = stoi(playerStatsString[24]);

		//Retreave other info from .txt
		tie = stoi(playerStatsString[28]);

		saveFile.close();
	}
	#pragma endregion
	
	//---------------------------------------------------------------------------------------------------------------------------

	while (gameRunning)
	{
		cout << "Connect 4!!!" << endl;
		cout << "------------" << endl << endl;
		if (mainMenuSelect == 0)
			cout << mainMenuSelectIcon << " | " << "Play" << endl;
		else
			cout << " | " << "Play" << endl;
		if (mainMenuSelect == 1)
			cout << mainMenuSelectIcon << " | " << "Stats" << endl;
		else
			cout << " | " << "Stats" << endl;
		if (mainMenuSelect == 2)
			cout << mainMenuSelectIcon << " | " << "Settings" << endl;
		else
			cout << " | " << "Settings" << endl;
		if (mainMenuSelect == 3)
			cout << mainMenuSelectIcon << " | " << "Save" << endl;
		else
			cout << " | " << "Save" << endl;
		if (mainMenuSelect == 4)
			cout << mainMenuSelectIcon << " | " << "Default Reset" << endl;
		else
			cout << " | " << "Default Reset" << endl;

		if (mainMenuSelect == 5)
			cout << mainMenuSelectIcon << " | " << "Quit" << endl;
		else
			cout << " | " << "Quit" << endl;

		char menuSelect = tolower(_getch());
		switch (menuSelect)
		{
		case 'w':
			mainMenuSelect -= 1;
			break;
		case 's':
			mainMenuSelect += 1;
			break;
		case 13:
			if (mainMenuSelect == 0) //Play
			{
				system("cls");
				gameBoard(playerOne, playerTwo, playerOneColor, playerTwoColor, colorPlayerOne, colorPlayerTwo, playerOneName, playerTwoName, tie, playerOneWin, playerOneLoose, playerTwoWin, playerTwoLoose, aiRunning, trueAIRunning);
				mainMenuSelect = 0;
			}
			else if (mainMenuSelect == 1) //Stats
			{
				system("cls");
				stats(playerOneName, playerTwoName, playerOne, playerTwo, playerOneColor, playerTwoColor, colorPlayerOne, colorPlayerTwo, tie, playerOneWin, playerOneLoose, playerTwoWin, playerTwoLoose);
				mainMenuSelect = 0;
			}
			else if (mainMenuSelect == 2) //Settings
			{
				system("cls");
				settings(playerOne, playerTwo, playerOneColor, playerTwoColor, playerOneName, playerTwoName, colorPlayerOne, colorPlayerTwo);
				mainMenuSelect = 0;
			}
			else if (mainMenuSelect == 3) //Save
			{
				system("cls");
				saving(playerOne, playerTwo, playerOneColor, playerTwoColor, playerOneName, playerTwoName, tie, playerOneWin, playerOneLoose, playerTwoWin, playerTwoLoose);
				mainMenuSelect = 0;
			} 
			else if (mainMenuSelect == 4) //Reset Save
			{
				system("cls");
				resetsave(playerOne, playerTwo, playerOneColor, playerTwoColor, playerOneName, playerTwoName, tie, playerOneWin, playerOneLoose, playerTwoWin, playerTwoLoose);
				mainMenuSelect = 0;
			}
			else if (mainMenuSelect == 5) //Quit
			{
				system("cls");
				exit(0);
			}
			break;
		default:
			break;
		}

		if (mainMenuSelect < 0)
			mainMenuSelect = 5;
		if (mainMenuSelect > 5)
			mainMenuSelect = 0;

		system("cls");
	}
}