#pragma once
#include "Includes.h"
#include "GameBoard.h"

#pragma region Identifier
void settings(char& playerOne, char& playerTwo, int& playerOneColor, int& playerTwoColor, string& playerOneName, string& playerTwoName, int colorPlayerOne[], int colorPlayerTwo[]);
void playerNames(string& playerOneName, string& playerTwoName);
void playerIcon(char& playerOne, char& playerTwo, string playerOneName, string playerTwoName);
void playerColor(int& playerOneColor, int& playerTwoColor, int colorPlayerOne[], int colorPlayerTwo[], string playerOneName, string playerTwoName);
#pragma endregion


void settings(char& playerOne, char& playerTwo, int& playerOneColor, int& playerTwoColor, string& playerOneName, string& playerTwoName, int colorPlayerOne[], int colorPlayerTwo[]) {

	bool settingsRunning{true};
	int mainMenuSelect{};
	string mainMenuSelectIcon{ "->" };

	while (settingsRunning)
	{
		cout << "Settings" << endl;
		cout << "------------" << endl << endl;
		if (mainMenuSelect == 0)
			cout << mainMenuSelectIcon << " | " << "Player names" << endl;
		else
			cout << " | " << "Player names" << endl;
		if (mainMenuSelect == 1)
			cout << mainMenuSelectIcon << " | " << "Player symbol" << endl;
		else
			cout << " | " << "Player symbol" << endl;
		if (mainMenuSelect == 2)
			cout << mainMenuSelectIcon << " | " << "Player color" << endl;
		else
			cout << " | " << "Player color" << endl;
		if (mainMenuSelect == 3)
			cout << mainMenuSelectIcon << " | " << "Back" << endl;
		else
			cout << " | " << "Back" << endl;

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
			if (mainMenuSelect == 0)
			{
				system("cls");
				playerNames(playerOneName, playerTwoName);
			}
			else if (mainMenuSelect == 1)
			{
				system("cls");
				playerIcon(playerOne, playerTwo, playerOneName, playerTwoName);
			}
			else if (mainMenuSelect == 2)
			{
				system("cls");
				playerColor(playerOneColor, playerTwoColor, colorPlayerOne, colorPlayerTwo, playerOneName, playerTwoName);
			}
			else if (mainMenuSelect == 3)
				settingsRunning = false;
			break;
		case 8:
			settingsRunning = false;
			break;
		default:
			break;
		}

		if (mainMenuSelect < 0)
			mainMenuSelect = 3;
		if (mainMenuSelect > 3)
			mainMenuSelect = 0;

		system("cls");
	}
}

void playerNames(string& playerOneName, string& playerTwoName) {

	cout << "Enter name of " << playerOneName << ": ";
	cin >> playerOneName;
	cout << "Enter name of " << playerTwoName << ": ";
	cin >> playerTwoName;
}

void playerIcon(char& playerOne, char& playerTwo, string playerOneName, string playerTwoName) {

	cout << "Enter icon for " << playerOneName << ": ";
	playerOne = _getch();
	cout << playerOne << endl;
	cout << "Enter icon for " << playerTwoName << ": ";
	playerTwo = _getch();
	Sleep(50);
}

void playerColor(int& playerOneColor, int& playerTwoColor, int colorPlayerOne[], int colorPlayerTwo[], string playerOneName, string playerTwoName) {

	playerOneColorSelect(playerOneColor, colorPlayerOne, playerOneName, playerTwoName);
	playerTwoColorSelect(playerTwoColor, colorPlayerTwo, playerOneName, playerTwoName);
}