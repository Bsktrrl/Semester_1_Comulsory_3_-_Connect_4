#pragma once
#include "Includes.h"
#include "GameBoard.h"
#include "Termcolor.h"
#include <fstream>

#pragma region Identifiers
void gameBoard(char playerOne, char playerTwo, int playerOneColor, int playerTwoColor, int colorPlayerOne[], int colorPlayerTwo[], string playerOneName, string playerTwoName, int& tie, int& playerOneWin, int& playerOneLoose, int& playerTwoWin, int& playerTwoLoose, bool& aiRunning, bool& trueAIRunning);
void setGameBoard(vector<vector<char>>& board, char empty, int boardX, int boardY);
void printGameBoard(vector<vector<char>> board, int boardX, int boardY, int& select, int& player, char& selectIconTwo, char playerOne, char playerTwo, bool menu, int& playerOneColor, int& playerTwoColor, int colorPlayerOne[], int colorPlayerTwo[], bool dropFromAbove, char empty);
void selectRowtoDrop(int rowSelected, vector<vector<char>>& board, char playerOne, char playerTwo, int boardY, int boardX, int& select, char empty, int& player, char& selectIconTwo, bool& fullColumn, int& boardCheckX, int& boardCheckY, bool menu, int& playerOneColor, int& playerTwoColor, int colorPlayerOne[], int colorPlayerTwo[], bool& dropFromAbove, bool aiRunning, bool trueAIRunning);
void winCondition(vector<vector<char>> board, int boardX, int boardY, char empty, char playerOne, char playerTwo, int& boardCheckX, int& boardCheckY, bool& newGame, int& player, char& selectIconTwo, bool& menu, int& playerOneColor, int& playerTwoColor, int colorPlayerOne[], int colorPlayerTwo[], string playerOneName, string playerTwoName, int& tie, int& playerOneWin, int& playerOneLoose, int& playerTwoWin, int& playerTwoLoose, bool& gameRoundRunning, bool dropFromAbove, bool& trueAIRunning, int& rounds, int& games, string& gamesString);
void playerOneColorSelect(int& playerOneColor, int colorPlayerOne[], string playerOneName, string playerTwoName);
void playerOneColorChosen(int playerOneColor, int colorPlayerOne[]);
void playerTwoColorSelect(int& playerTwoColor, int colorPlayerTwo[], string playerOneName, string playerTwoName);
void playerTwoColorChosen(int playerTwoColor, int colorPlayerTwo[]);
void ai(vector<vector<char>> board, int boardX, int boardY, char empty, char playerOne, char playerTwo, int& boardCheckX, int& boardCheckY, bool& newGame, int& player, char& selectIconTwo, bool& menu, int& playerOneColor, int& playerTwoColor, int colorPlayerOne[], int colorPlayerTwo[], string playerOneName, string playerTwoName, int& tie, int& playerOneWin, int& playerOneLoose, int& playerTwoWin, int& playerTwoLoose, bool& gameRoundRunning, bool dropFromAbove, int& rowSelected, bool& selectColumn);
void rngAIChooseSides(int& chooseSide);
void gameFilesResult(vector<vector<char>> board, int boardX, int boardY, char playerOne, char playerTwo, string playerOneName, string playerTwoName, int games, string gamesString);
void gameFilesReview(vector<vector<char>> board, int boardX, int boardY, char playerOne, char playerTwo, string playerOneName, string playerTwoName, int games, string gamesString);
#pragma endregion

//---------------------------------------------------------------------------------------------------------------------------

void gameBoard(char playerOne, char playerTwo, int playerOneColor, int playerTwoColor, int colorPlayerOne[], int colorPlayerTwo[], string playerOneName, string playerTwoName, int& tie, int& playerOneWin, int& playerOneLoose, int& playerTwoWin, int& playerTwoLoose, bool& aiRunning, bool& trueAIRunning) {
	
	int boardX{7};
	int boardY{6};
	vector<vector<char>> board(boardY, vector<char>(boardX));

	int boardCheckX{};
	int boardCheckY{};

	char selectIconTwo{' '};
	char empty{' '};

	bool gameRoundRunning{true};
	bool newGame{true};
	bool fullColumn{};
	bool menu{};
	bool dropFromAbove{true};
	bool exitPlay{};
	bool firstPlayerToPlay{true};
	bool playerOrAi{true};
	string firstPlayerToPlayIcon{"->"};

	int select{};
	int rowSelected{};
	int player{0};
	int rounds{};
	int games{1};
	string gamesString{};


	while (gameRoundRunning)
	{
		rounds += 1;

		//If the selected column is full, don't change player untill the player select a column that is not full
		if (fullColumn == false) {
			player += 1;
			fullColumn = true;
		}

		//Display player icons on the right player
		if (player > 2)
			player = 1;

		bool selectColumn{true};
		while (selectColumn)
		{
			while (newGame)
			{
				firstPlayerToPlay = true;
				playerOrAi = true;
				setGameBoard(board, empty, boardY, boardX);
				newGame = false;
				select = 0;

				while (playerOrAi)
				{
					//Play against a player or the computer
					cout << "Select mode" << endl;
					cout << "-----------" << endl << endl;
					if (select == 0)
						cout << firstPlayerToPlayIcon << " | Player vs. Player" << endl;
					else
						cout << " | Player vs. Player" << endl;
					if (select == 1)
						cout << firstPlayerToPlayIcon << " | Player vs. Computer" << endl;
					else
						cout << " | Player vs. Computer" << endl;
					if (select == 2)
						cout << firstPlayerToPlayIcon << " | Computer vs. Computer" << endl;
					else
						cout << " | Computer vs. Computer" << endl;

					char firstPlayer = tolower(_getch());
					switch (firstPlayer)
					{
					case 'w':
						select -= 1;
						break;
					case 's':
						select += 1;
						break;
					case 13:
						if (select == 0)
						{
							aiRunning = false;
							trueAIRunning = false;
						}
						if (select == 1)
							aiRunning = true;
						if (select == 2)
						{
							aiRunning = false;
							trueAIRunning = true;
						}
						playerOrAi = false;
						select = 0;
						break;
					case 8:
						playerOrAi = false;
						firstPlayerToPlay = false;
						select = 0;
						selectColumn = false;
						gameRoundRunning = false;
						exitPlay = true;
						break;
					default:
						break;
					}

					if (select < 0)
						select = 2;
					if (select > 2)
						select = 0;

					system("cls");
				}

				while (firstPlayerToPlay)
				{
					//Select first player - Yet to be finished - Need the standard menu with the player names in their colors displayed together with "->"
					cout << "Which player will go first?" << endl;
					cout << "---------------------------" << endl << endl;
					if (select == 0)
					{
						cout << firstPlayerToPlayIcon << " | ";
						playerOneColorChosen(playerOneColor, colorPlayerOne);
						cout << playerOneName << termcolor::reset;
						cout << " (";
						playerOneColorChosen(playerOneColor, colorPlayerOne);
						cout << playerOne << termcolor::reset << ")";
						if (aiRunning == true)
							cout << " (You)";
						else if (trueAIRunning == true)
							cout << " (Computer)";
						else if (trueAIRunning != true && aiRunning != true)
							cout << "";
						cout << endl;
					}
					else
					{
						cout << " | ";
						playerOneColorChosen(playerOneColor, colorPlayerOne);
						cout << playerOneName << termcolor::reset;
						cout << " (";
						playerOneColorChosen(playerOneColor, colorPlayerOne);
						cout << playerOne << termcolor::reset << ")";
						if (aiRunning == true)
							cout << " (You)";
						else if (trueAIRunning == true)
							cout << " (Computer)";
						else if (trueAIRunning != true && aiRunning != true)
							cout << "";
						cout << endl;
					}

					if (select == 1)
					{
						cout << firstPlayerToPlayIcon << " | ";
						playerTwoColorChosen(playerTwoColor, colorPlayerTwo);
						cout << playerTwoName << termcolor::reset;
						cout << " (";
						playerTwoColorChosen(playerTwoColor, colorPlayerTwo);
						cout << playerTwo << termcolor::reset << ")";
						if (aiRunning == true)
							cout << " (Computer)";
						else if (trueAIRunning == true)
							cout << " (Computer)";
						else if (trueAIRunning != true && aiRunning != true)
							cout << "";
						cout << endl;
					}
					else
					{
						cout << " | ";
						playerTwoColorChosen(playerTwoColor, colorPlayerTwo);
						cout << playerTwoName << termcolor::reset;
						cout << " (";
						playerTwoColorChosen(playerTwoColor, colorPlayerTwo);
						cout << playerTwo << termcolor::reset << ")";
						if (aiRunning == true)
							cout << " (Computer)";
						else if (trueAIRunning == true)
							cout << " (Computer)";
						else if (trueAIRunning != true && aiRunning != true)
							cout << "";
						cout << endl;
					}

					char firstPlayer = tolower(_getch());
					switch (firstPlayer)
					{
					case 'w':
						select -= 1;
						break;
					case 's':
						select += 1;
						break;
					case 13:
						if (select == 0)
							player = 1;
						if (select == 1)
							player = 2;
						firstPlayerToPlay = false;
						select = 0;
						break;
					case 8:
						firstPlayerToPlay = false;
						select = 0;
						selectColumn = false;
						gameRoundRunning = false;
						exitPlay = true;
						break;
					default:
						break;
					}

					if (select < 0)
						select = 1;
					if (select > 1)
						select = 0;

					system("cls");
				}

			}

			if (exitPlay == false)
			{
				printGameBoard(board, boardY, boardX, select, player, selectIconTwo, playerOne, playerTwo, menu, playerOneColor, playerTwoColor, colorPlayerOne, colorPlayerTwo, dropFromAbove, empty);

				//This happens when the AI is on
				if (aiRunning == true && player == 2)
				{
					ai(board, boardX, boardY, empty, playerOne, playerTwo, boardCheckX, boardCheckY, newGame, player, selectIconTwo, menu, playerOneColor, playerTwoColor, colorPlayerOne, colorPlayerTwo, playerOneName, playerTwoName, tie, playerOneWin, playerOneLoose, playerTwoWin, playerTwoLoose, gameRoundRunning, dropFromAbove, rowSelected, selectColumn);
				}
				else if (trueAIRunning == true)
				{
					ai(board, boardX, boardY, empty, playerOne, playerTwo, boardCheckX, boardCheckY, newGame, player, selectIconTwo, menu, playerOneColor, playerTwoColor, colorPlayerOne, colorPlayerTwo, playerOneName, playerTwoName, tie, playerOneWin, playerOneLoose, playerTwoWin, playerTwoLoose, gameRoundRunning, dropFromAbove, rowSelected, selectColumn);
				}
				else
				{
					char menuSelect = tolower(_getch());
					switch (menuSelect)
					{
					case 'a':
						select -= 1;
						break;
					case 'd':
						select += 1;
						break;
					case 13:
						for (size_t k = 0; k < boardX; k++)
						{
							if (select == k) {
								rowSelected = k;
								selectColumn = false;
							}
						}
						break;
					case 8:
						system("cls");
						menu = false;
						newGame = true;
						gameRoundRunning = false;
						selectColumn = false;
						exitPlay = true;
						break;
					default:
						break;
					}

					if (select < 0)
						select = boardX - 1;
					if (select > boardX - 1)
						select = 0;
				}
			}
		}

		if (exitPlay == false)
		{
			selectRowtoDrop(rowSelected, board, playerOne, playerTwo, boardY, boardX, select, empty, player, selectIconTwo, fullColumn, boardCheckX, boardCheckY, menu, playerOneColor, playerTwoColor, colorPlayerOne, colorPlayerTwo, dropFromAbove, aiRunning, trueAIRunning);

			winCondition(board, boardX, boardY, empty, playerOne, playerTwo, boardCheckX, boardCheckY, newGame, player, selectIconTwo, menu, playerOneColor, playerTwoColor, colorPlayerOne, colorPlayerTwo, playerOneName, playerTwoName, tie, playerOneWin, playerOneLoose, playerTwoWin, playerTwoLoose, gameRoundRunning, dropFromAbove, trueAIRunning, rounds, games, gamesString);
		}

		exitPlay == false;
	}
}

void setGameBoard(vector<vector<char>>& board, char empty, int boardX, int boardY) {

	for (size_t i = 0; i < boardX; i++)
		for (size_t j = 0; j < boardY; j++)
			board[i][j] = empty;
}

void printGameBoard(vector<vector<char>> board, int boardY, int boardX, int& select, int& player, char& selectIconTwo, char playerOne, char playerTwo, bool menu, int& playerOneColor, int& playerTwoColor, int colorPlayerOne[], int colorPlayerTwo[], bool dropFromAbove, char empty) {

	system("cls");

	string selectIconOne{ " | " };
	if (player == 1)
		selectIconTwo = playerOne;
	else
		selectIconTwo = playerTwo;
	
	int tempPositionBefore{};
	int tempPositionAfter{};

	tempPositionBefore = select;
	tempPositionAfter = boardX - select - 1;

	if (menu == false)
	{
		//Set row 1
		cout << setw(2) << " ";
		for (size_t i = 0; i < boardX; i++)
		{
			if (select == i) {
				for (size_t i = 0; i < tempPositionBefore; i++)
					cout << setw(2) << "  ";

				if (player == 1)
					cout << selectIconOne << termcolor::reset;
				else
					cout << selectIconOne << termcolor::reset;

				for (size_t i = 0; i < tempPositionAfter; i++)
					cout << setw(2) << "  ";

				cout << " ";
			}
		}
		cout << endl;

		//Set row 2
		if (dropFromAbove == true)
		{
			cout << setw(2) << " ";
			for (size_t i = 0; i < boardX; i++)
			{
				if (select == i) {
					for (size_t i = 0; i < tempPositionBefore; i++)
						cout << setw(2) << "  ";

					if (player == 1)
					{
						playerOneColorChosen(playerOneColor, colorPlayerOne);
						cout << " " << selectIconTwo << " " << termcolor::reset;
					}
					else
					{
						playerOneColorChosen(playerTwoColor, colorPlayerTwo);
						cout << " " << selectIconTwo << " " << termcolor::reset;
					}

					for (size_t i = 0; i < tempPositionAfter; i++)
						cout << setw(2) << "  ";

					cout << " ";
				}
			}
		}
		cout << endl;
	}
	else
		cout << endl << endl;

	//Set row 3
	cout << setw(2) << " ";
	for (size_t j = 0; j < boardX; j++)
		cout << setw(2) << "__";
	cout << setw(2) << "_ " << endl;

	//Set the rest of the board 
	for (size_t i = 0; i < boardY; i++)
	{
		cout << setw(2) << "|";
		for (size_t j = 0; j < boardX; j++)
		{
			if (board[i][j] == playerOne)
			{
				playerOneColorChosen(playerOneColor, colorPlayerOne);
				cout << setw(2) << board[i][j] << termcolor::reset;
			}
			else if (board[i][j] == playerTwo)
			{
				playerOneColorChosen(playerTwoColor, colorPlayerTwo);
				cout << setw(2) << board[i][j] << termcolor::reset;
			}
			else
				cout << setw(2) << board[i][j];
		}
		cout << setw(2) << "|" << endl;
	}

	//Set last row
	cout << setw(2) << "|";
	for (size_t j = 0; j < boardX; j++)
		cout << setw(2) << "--";
	cout << setw(2) << "-|" << endl;
}

void selectRowtoDrop(int rowSelected, vector<vector<char>>& board, char playerOne, char playerTwo, int boardY, int boardX, int& select, char empty, int& player, char& selectIconTwo, bool& fullColumn, int& boardCheckX, int& boardCheckY, bool menu, int& playerOneColor, int& playerTwoColor, int colorPlayerOne[], int colorPlayerTwo[], bool& dropFromAbove, bool aiRunning, bool trueAIRunning) {
	
	int sleepTime{10};
	int aiMoveTime{50};

	//Show animation if AI is active
	if (aiRunning || trueAIRunning)
	{
		//Move AI
		while (rowSelected != select)
		{
			Sleep(aiMoveTime * 2);

			if (select < rowSelected)
			{
				select += 1;
			}
			else if (select > rowSelected)
			{
				select -= 1;
			}

			printGameBoard(board, boardY, boardX, select, player, selectIconTwo, playerOne, playerTwo, menu, playerOneColor, playerTwoColor, colorPlayerOne, colorPlayerTwo, dropFromAbove, empty);
			Sleep(aiMoveTime);
		}

		Sleep(aiMoveTime * 2);
	}

	if (board[0][rowSelected] == empty)
	{
		dropFromAbove = false;
		fullColumn = false;
		board[0][rowSelected] = selectIconTwo;
		printGameBoard(board, boardY, boardX, select, player, selectIconTwo, playerOne, playerTwo, menu, playerOneColor, playerTwoColor, colorPlayerOne, colorPlayerTwo, dropFromAbove, empty);
		Sleep(sleepTime);

		boardCheckX = 0;

		for (size_t i = 1; i < boardX - 1; i++)
		{
			if (board[i][rowSelected] == empty)
			{
				board[i - 1][rowSelected] = empty;
				board[i][rowSelected] = selectIconTwo;
				if (i != boardX - 1)
					printGameBoard(board, boardY, boardX, select, player, selectIconTwo, playerOne, playerTwo, menu, playerOneColor, playerTwoColor, colorPlayerOne, colorPlayerTwo, dropFromAbove, empty);

				Sleep(sleepTime);

				boardCheckX = i;
				boardCheckY = rowSelected;
			}
		}
	}
	else
		fullColumn = true;

	dropFromAbove = true;
}

void winCondition(vector<vector<char>> board, int boardX, int boardY, char empty, char playerOne, char playerTwo, int& boardCheckX, int& boardCheckY, bool& newGame, int& player, char& selectIconTwo, bool& menu, int& playerOneColor, int& playerTwoColor, int colorPlayerOne[], int colorPlayerTwo[], string playerOneName, string playerTwoName, int& tie, int& playerOneWin, int& playerOneLoose, int& playerTwoWin, int& playerTwoLoose, bool& gameRoundRunning, bool dropFromAbove, bool& trueAIRunning, int& rounds, int& games, string& gamesString) {
		
	int emptyBoardCount{};
	int checkWinCount{};
	int selectNewGame{};
	int winConditionCounter{};

	char checkWinner{};
	bool winner{};

	vector<vector<char>> boardTemp = board;
	string selectIcon{ "->" };


	//Focus on the player in turn
	if (player == 1)
		checkWinner = playerOne;
	else
		checkWinner = playerTwo;

	//---------------------------------------------------------------------------------------------------------------------------

	//Win check - Horisontally
	for (size_t y = 0; y < boardY; y++)
	{
		for (size_t x = 0; x < boardX; x++)
		{
			if (boardTemp[y][x] == checkWinner)
			{
				winConditionCounter += 1;
				if (winConditionCounter >= 4)
					winner = true;
			}
			else
				winConditionCounter = 0;
		}
		winConditionCounter = 0;
	}

	//Win check - Vertically
	for (size_t x = 0; x < boardX; x++)
	{
		for (size_t y = 0; y < boardY; y++)
		{
			if (boardTemp[y][x] == checkWinner)
			{
				winConditionCounter += 1;
				if (winConditionCounter >= 4)
					winner = true;
			}
			else
				winConditionCounter = 0;
		}
		winConditionCounter = 0;
	}

	//Win check - Diagonally ->
	for (size_t y = 0; y < boardY; y++)
	{
		for (size_t x = 0; x < boardX; x++)
		{
			if (y < boardY - 3 && x < boardX - 3)
			{
				if (boardTemp[y][x] == checkWinner && boardTemp[y + 1][x + 1] == checkWinner && boardTemp[y + 2][x + 2] == checkWinner && boardTemp[y + 3][x + 3] == checkWinner)
					winner = true;
			}
		}
	}

	//Win check - Diagonally <-
	for (size_t y = 0; y < boardY; y++)
	{
		for (size_t x = 0; x < boardX; x++)
		{
			if (y > 2 && x < boardX - 3)
			{
				if (boardTemp[y][x] == checkWinner && boardTemp[y - 1][x + 1] == checkWinner && boardTemp[y - 2][x + 2] == checkWinner && boardTemp[y - 3][x + 3] == checkWinner)
					winner = true;
			}
		}
	}

	//---------------------------------------------------------------------------------------------------------------------------
	
	gamesString = to_string(games);
	gameFilesReview(board, boardX, boardY, playerOne, playerTwo, playerOneName, playerTwoName, games, gamesString);

	//When we have a winner
	while (winner)
	{
		gameFilesResult(board, boardX, boardY, playerOne, playerTwo, playerOneName, playerTwoName, games, gamesString);

		rounds = 0;
		games += 1;
		
		if (player == 1) {
			playerOneWin++;
			playerTwoLoose++;
		}
		else {
			playerTwoWin++;
			playerOneLoose++;
		}
		menu = true;
		while (menu)
		{
			printGameBoard(board, boardY, boardX, selectNewGame, player, selectIconTwo, playerOne, playerTwo, menu, playerOneColor, playerTwoColor, colorPlayerOne, colorPlayerTwo, dropFromAbove, empty);

			cout << endl;
			cout << "-------------------------------" << endl;
			if (player == 1) {
				playerOneColorChosen(playerOneColor, colorPlayerOne);
				cout << playerOneName << termcolor::reset << " is the winner!!!" << endl << endl;
			}
			else {
				playerTwoColorChosen(playerTwoColor, colorPlayerTwo);
				cout << playerTwoName << termcolor::reset << " is the winner!!!" << endl << endl;
			}
			
			cout << "Do you want to play a new game?" << endl;

			if (selectNewGame == 0)
				cout << selectIcon << " | Yes" << endl;
			else
				cout << " | Yes" << endl;
			if (selectNewGame == 1)
				cout << selectIcon << " | Back to menu" << endl;
			else
				cout << " | Back to menu" << endl;

			char menuSelect = tolower(_getch());
			switch (menuSelect)
			{
			case 'w':
				selectNewGame -= 1;
				break;
			case 's':
				selectNewGame += 1;
				break;
			case 13:
				if (selectNewGame == 0)
				{
					menu = false;
					winner = false;
					newGame = true;
					trueAIRunning = false;
				}
				else
				{
					system("cls");
					menu = false;
					winner = false;
					newGame = true;
					gameRoundRunning = false;
					trueAIRunning = false;
				}
				break;
			case 8:
				system("cls");
				menu = false;
				winner = false;
				newGame = true;
				gameRoundRunning = false;
				trueAIRunning = false;
				break;
			default:
				break;
			}

			if (selectNewGame < 0)
				selectNewGame = 1;
			if (selectNewGame > 1)
				selectNewGame = 0;

			system("cls");
		}
	}

	//Check if the board is full
	emptyBoardCount = 0;
	for (size_t i = 0; i < boardY; i++)
	{
		for (size_t j = 0; j < boardX; j++)
		{
			if (board[i][j] == empty)
				emptyBoardCount++;
		}
	}

	//If the board is full and there is a tie
	if (emptyBoardCount <= 0)
	{
		gameFilesReview(board, boardX, boardY, playerOne, playerTwo, playerOneName, playerTwoName, games, gamesString);
		gameFilesResult(board, boardX, boardY, playerOne, playerTwo, playerOneName, playerTwoName, games, gamesString);

		rounds = 0;
		games += 1;

		tie++;
		menu = true;
		while (menu)
		{
			printGameBoard(board, boardY, boardX, selectNewGame, player, selectIconTwo, playerOne, playerTwo, menu, playerOneColor, playerTwoColor, colorPlayerOne, colorPlayerTwo, dropFromAbove, empty);

			cout << endl;
			cout << "-------------------------------" << endl;
			cout << "It is a tie" << endl << endl;
			cout << "Do you want to play a new game?" << endl;

			if (selectNewGame == 0)
				cout << selectIcon << " | Yes" << endl;
			else
				cout << " | Yes" << endl;
			if (selectNewGame == 1)
				cout << selectIcon << " | Back to menu" << endl;
			else
				cout << " | Back to menu" << endl;

			char menuSelect = tolower(_getch());
			switch (menuSelect)
			{
			case 'w':
				selectNewGame -= 1;
				break;
			case 's':
				selectNewGame += 1;
				break;
			case 13:
				if (selectNewGame == 0)
				{
					menu = false;
					newGame = true;
					trueAIRunning = false;
				}
				else
				{
					system("cls");
					menu = false;
					newGame = true;
					gameRoundRunning = false;
					trueAIRunning = false;
				}
				break;
			case 8:
				system("cls");
				menu = false;
				newGame = true;
				gameRoundRunning = false;
				trueAIRunning = false;
				break;
			default:
				break;
			}

			if (selectNewGame < 0)
				selectNewGame = 1;
			if (selectNewGame > 1)
				selectNewGame = 0;

			system("cls");
		}
	}
}

void playerOneColorSelect(int& playerOneColor, int colorPlayerOne[], string playerOneName, string playerTwoName) {

	bool colorMenu{true};
	int colorSelect{};
	string colorSelectIcon{"->"};

	while (colorMenu)
	{
		cout << "Choose color for " << playerOneName << ":" << endl;
		cout << "--------------------------" << endl << endl;

		if (colorSelect == 0)
			cout << colorSelectIcon << " | " << termcolor::bright_grey << "Bright Grey" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::bright_grey << "Bright Grey" << termcolor::reset << endl;
		if (colorSelect == 1)
			cout << colorSelectIcon << " | " << termcolor::white << "White" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::white << "White" << termcolor::reset << endl;
		if (colorSelect == 2)
			cout << colorSelectIcon << " | " << termcolor::bright_white << "Bright White" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::bright_white << "Bright White" << termcolor::reset << endl;
		if (colorSelect == 3)
			cout << colorSelectIcon << " | " << termcolor::bright_yellow << "Bright Yellow" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::bright_yellow << "Bright Yellow" << termcolor::reset << endl;
		if (colorSelect == 4)
			cout << colorSelectIcon << " | " << termcolor::yellow << "Yellow" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::yellow << "Yellow" << termcolor::reset << endl;
		if (colorSelect == 5)
			cout << colorSelectIcon << " | " << termcolor::bright_red << "Bright Red" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::bright_red << "Bright Red" << termcolor::reset << endl;
		if (colorSelect == 6)
			cout << colorSelectIcon << " | " << termcolor::red << "Red" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::red << "Red" << termcolor::reset << endl;
		if (colorSelect == 7)
			cout << colorSelectIcon << " | " << termcolor::bright_magenta << "Bright Magenta" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::bright_magenta << "Bright Magenta" << termcolor::reset << endl;
		if (colorSelect == 8)
			cout << colorSelectIcon << " | " << termcolor::magenta << "Magenta" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::magenta << "Magenta" << termcolor::reset << endl;
		if (colorSelect == 9)
			cout << colorSelectIcon << " | " << termcolor::blue << "Blue" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::blue << "Blue" << termcolor::reset << endl;
		if (colorSelect == 10)
			cout << colorSelectIcon << " | " << termcolor::bright_blue << "Bright Blue" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::bright_blue << "Bright Blue" << termcolor::reset << endl;
		if (colorSelect == 11)
			cout << colorSelectIcon << " | " << termcolor::cyan << "Cyan" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::cyan << "Cyan" << termcolor::reset << endl;
		if (colorSelect == 12)
			cout << colorSelectIcon << " | " << termcolor::bright_cyan << "Bright Cyan" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::bright_cyan << "Bright Cyan" << termcolor::reset << endl;
		if (colorSelect == 13)
			cout << colorSelectIcon << " | " << termcolor::bright_green << "Bright Green" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::bright_green << "Bright Green" << termcolor::reset << endl;
		if (colorSelect == 14)
			cout << colorSelectIcon << " | " << termcolor::green << "Green" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::green << "Green" << termcolor::reset << endl;

		char menuSelect = tolower(_getch());
		switch (menuSelect)
		{
		case 'w':
			colorSelect -= 1;
			break;
		case 's':
			colorSelect += 1;
			break;
		case 13:
			for (size_t k = 0; k <= 14; k++) {
				if (colorSelect == k)
				{
					playerOneColor = k;
					colorMenu = false;
				}
			}
			break;
		default:
			break;
		}

		if (colorSelect < 0)
			colorSelect = 14;
		if (colorSelect > 14)
			colorSelect = 0;

		system("cls");
	}
}
void playerOneColorChosen(int playerOneColor, int colorPlayerOne[]) {

	if (colorPlayerOne[playerOneColor] == 0)
		cout << termcolor::bright_grey;
	else if (colorPlayerOne[playerOneColor] == 1)
		cout << termcolor::white;
	else if (colorPlayerOne[playerOneColor] == 2)
		cout << termcolor::bright_white;
	else if (colorPlayerOne[playerOneColor] == 3)
		cout << termcolor::bright_yellow;
	else if (colorPlayerOne[playerOneColor] == 4)
		cout << termcolor::yellow;
	else if (colorPlayerOne[playerOneColor] == 5)
		cout << termcolor::bright_red;
	else if (colorPlayerOne[playerOneColor] == 6)
		cout << termcolor::red;
	else if (colorPlayerOne[playerOneColor] == 7)
		cout << termcolor::bright_magenta;
	else if (colorPlayerOne[playerOneColor] == 8)
		cout << termcolor::magenta;
	else if (colorPlayerOne[playerOneColor] == 9)
		cout << termcolor::blue;
	else if (colorPlayerOne[playerOneColor] == 10)
		cout << termcolor::bright_blue;
	else if (colorPlayerOne[playerOneColor] == 11)
		cout << termcolor::cyan;
	else if (colorPlayerOne[playerOneColor] == 12)
		cout << termcolor::bright_cyan;
	else if (colorPlayerOne[playerOneColor] == 13)
		cout << termcolor::bright_green;
	else if (colorPlayerOne[playerOneColor] == 14)
		cout << termcolor::green;
}

void playerTwoColorSelect(int& playerTwoColor, int colorPlayerTwo[], string playerOneName, string playerTwoName) {

	bool colorMenu{ true };
	int colorSelect{};
	string colorSelectIcon{ "->" };

	while (colorMenu)
	{
		cout << "Choose color for " << playerTwoName << ":" << endl;
		cout << "--------------------------" << endl << endl;

		if (colorSelect == 0)
			cout << colorSelectIcon << " | " << termcolor::bright_grey << "Bright Grey" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::bright_grey << "Bright Grey" << termcolor::reset << endl;
		if (colorSelect == 1)
			cout << colorSelectIcon << " | " << termcolor::white << "White" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::white << "White" << termcolor::reset << endl;
		if (colorSelect == 2)
			cout << colorSelectIcon << " | " << termcolor::bright_white << "Bright White" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::bright_white << "Bright White" << termcolor::reset << endl;
		if (colorSelect == 3)
			cout << colorSelectIcon << " | " << termcolor::bright_yellow << "Bright Yellow" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::bright_yellow << "Bright Yellow" << termcolor::reset << endl;
		if (colorSelect == 4)
			cout << colorSelectIcon << " | " << termcolor::yellow << "Yellow" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::yellow << "Yellow" << termcolor::reset << endl;
		if (colorSelect == 5)
			cout << colorSelectIcon << " | " << termcolor::bright_red << "Bright Red" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::bright_red << "Bright Red" << termcolor::reset << endl;
		if (colorSelect == 6)
			cout << colorSelectIcon << " | " << termcolor::red << "Red" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::red << "Red" << termcolor::reset << endl;
		if (colorSelect == 7)
			cout << colorSelectIcon << " | " << termcolor::bright_magenta << "Bright Magenta" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::bright_magenta << "Bright Magenta" << termcolor::reset << endl;
		if (colorSelect == 8)
			cout << colorSelectIcon << " | " << termcolor::magenta << "Magenta" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::magenta << "Magenta" << termcolor::reset << endl;
		if (colorSelect == 9)
			cout << colorSelectIcon << " | " << termcolor::blue << "Blue" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::blue << "Blue" << termcolor::reset << endl;
		if (colorSelect == 10)
			cout << colorSelectIcon << " | " << termcolor::bright_blue << "Bright Blue" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::bright_blue << "Bright Blue" << termcolor::reset << endl;
		if (colorSelect == 11)
			cout << colorSelectIcon << " | " << termcolor::cyan << "Cyan" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::cyan << "Cyan" << termcolor::reset << endl;
		if (colorSelect == 12)
			cout << colorSelectIcon << " | " << termcolor::bright_cyan << "Bright Cyan" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::bright_cyan << "Bright Cyan" << termcolor::reset << endl;
		if (colorSelect == 13)
			cout << colorSelectIcon << " | " << termcolor::bright_green << "Bright Green" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::bright_green << "Bright Green" << termcolor::reset << endl;
		if (colorSelect == 14)
			cout << colorSelectIcon << " | " << termcolor::green << "Green" << termcolor::reset << endl;
		else
			cout << " | " << termcolor::green << "Green" << termcolor::reset << endl;

		char menuSelect = tolower(_getch());
		switch (menuSelect)
		{
		case 'w':
			colorSelect -= 1;
			break;
		case 's':
			colorSelect += 1;
			break;
		case 13:
			for (size_t k = 0; k <= 14; k++) {
				if (colorSelect == k)
				{
					playerTwoColor = k;
					colorMenu = false;
				}
			}
			break;
		default:
			break;
		}

		if (colorSelect < 0)
			colorSelect = 14;
		if (colorSelect > 14)
			colorSelect = 0;

		system("cls");
	}
}
void playerTwoColorChosen(int playerTwoColor, int colorPlayerTwo[]) {

	if (colorPlayerTwo[playerTwoColor] == 0)
		cout << termcolor::bright_grey;
	else if (colorPlayerTwo[playerTwoColor] == 1)
		cout << termcolor::white;
	else if (colorPlayerTwo[playerTwoColor] == 2)
		cout << termcolor::bright_white;
	else if (colorPlayerTwo[playerTwoColor] == 3)
		cout << termcolor::bright_yellow;
	else if (colorPlayerTwo[playerTwoColor] == 4)
		cout << termcolor::yellow;
	else if (colorPlayerTwo[playerTwoColor] == 5)
		cout << termcolor::bright_red;
	else if (colorPlayerTwo[playerTwoColor] == 6)
		cout << termcolor::red;
	else if (colorPlayerTwo[playerTwoColor] == 7)
		cout << termcolor::bright_magenta;
	else if (colorPlayerTwo[playerTwoColor] == 8)
		cout << termcolor::magenta;
	else if (colorPlayerTwo[playerTwoColor] == 9)
		cout << termcolor::blue;
	else if (colorPlayerTwo[playerTwoColor] == 10)
		cout << termcolor::bright_blue;
	else if (colorPlayerTwo[playerTwoColor] == 11)
		cout << termcolor::cyan;
	else if (colorPlayerTwo[playerTwoColor] == 12)
		cout << termcolor::bright_cyan;
	else if (colorPlayerTwo[playerTwoColor] == 13)
		cout << termcolor::bright_green;
	else if (colorPlayerTwo[playerTwoColor] == 14)
		cout << termcolor::green;
	else
		cout << termcolor::white;
}

void ai(vector<vector<char>> board, int boardX, int boardY, char empty, char playerOne, char playerTwo, int& boardCheckX, int& boardCheckY, bool& newGame, int& player, char& selectIconTwo, bool& menu, int& playerOneColor, int& playerTwoColor, int colorPlayerOne[], int colorPlayerTwo[], string playerOneName, string playerTwoName, int& tie, int& playerOneWin, int& playerOneLoose, int& playerTwoWin, int& playerTwoLoose, bool& gameRoundRunning, bool dropFromAbove, int& rowSelected, bool& selectColumn) {

	rowSelected = 0;

	vector<vector<char>> treatCheck = board;

	int checkCount{};
	int chooseSide{};

	bool treatChecking{true};
	bool chooseAIPlacement{true};

	while (treatChecking)
	{
		if (treatChecking)
		{
			#pragma region For 3 in a row - AI
			//Horisontally - check for treat of 4 in a row
			for (int y = 0; y < boardY; y++) //Set Y
			{
				for (int x = 0; x < boardX; x++) //Set X
				{
					if (treatCheck[0][x] == empty)
					{
						//Check Y range ABOVE last row
						if (y < boardY - 1)
						{
							if (x < boardX - 2)
							{
								if (treatCheck[y][x] == playerTwo && treatCheck[y][x + 1] == playerTwo && treatCheck[y][x + 2] == playerTwo)
								{
									if (x == 0)
									{
										if (treatCheck[y][x + 3] == empty && treatCheck[y + 1][x + 3] != empty)
										{
											rowSelected = x + 3;
											selectColumn = false;
											treatChecking = false;
										}
									}
									else if (x == boardX - 3)
									{
										if (treatCheck[y][x - 1] == empty && treatCheck[y + 1][x - 1] != empty)
										{
											rowSelected = x - 1;
											selectColumn = false;
											treatChecking = false;
										}
									}
									else
									{
										if (treatCheck[y][x + 3] == empty && treatCheck[y][x - 1] == empty && treatCheck[y + 1][x + 3] != empty && treatCheck[y + 1][x - 1] != empty)
										{
											rngAIChooseSides(chooseSide);
											if (chooseSide == 0)
											{
												rowSelected = x + 3;
												selectColumn = false;
												treatChecking = false;
											}
											else
											{
												rowSelected = x - 1;
												selectColumn = false;
												treatChecking = false;
											}
										}
										else if (treatCheck[y][x + 3] == empty && treatCheck[y + 1][x + 3] != empty)
										{
											rowSelected = x + 3;
											selectColumn = false;
											treatChecking = false;
										}
										else if (treatCheck[y][x - 1] == empty && treatCheck[y + 1][x - 1] != empty)
										{
											rowSelected = x - 1;
											selectColumn = false;
											treatChecking = false;
										}
									}
								}
							}
						}

						//Check Y range ON last row
						else
						{
							if (x < boardX - 2)
							{
								if (treatCheck[y][x] == playerTwo && treatCheck[y][x + 1] == playerTwo && treatCheck[y][x + 2] == playerTwo)
								{
									if (x == 0)
									{
										if (treatCheck[y][x + 3] == empty)
										{
											rowSelected = x + 3;
											selectColumn = false;
											treatChecking = false;
										}
									}
									else if (x == boardX - 3)
									{
										if (treatCheck[y][x - 1] == empty)
										{
											rowSelected = x - 1;
											selectColumn = false;
											treatChecking = false;
										}
									}
									else
									{
										if (treatCheck[y][x + 3] == empty && treatCheck[y][x - 1] == empty)
										{
											rngAIChooseSides(chooseSide);
											if (chooseSide == 0)
											{
												rowSelected = x + 3;
												selectColumn = false;
												treatChecking = false;
											}
											else
											{
												rowSelected = x - 1;
												selectColumn = false;
												treatChecking = false;
											}
										}
										else if (treatCheck[y][x + 3] == empty)
										{
											rowSelected = x + 3;
											selectColumn = false;
											treatChecking = false;
										}
										else if (treatCheck[y][x - 1] == empty)
										{
											rowSelected = x - 1;
											selectColumn = false;
											treatChecking = false;
										}
									}
								}
							}
						}
					}
					else {}
				}
			}

			//Horisontally - check for treat of 4 in a row with input in between
			for (int y = 0; y < boardY; y++) //Set Y
			{
				for (int x = 0; x < boardX; x++) //Set X
				{
					if (treatCheck[0][x] == empty)
					{
						//Check Y range ABOVE last row
						if (y < boardY - 1)
						{
							if (x < boardX - 3)
							{
								if (treatCheck[y][x] == playerTwo && treatCheck[y][x + 1] == playerTwo && treatCheck[y][x + 2] == empty && treatCheck[y + 1][x + 2] != empty && treatCheck[y][x + 3] == playerTwo)
								{
									rowSelected = x + 2;
									selectColumn = false;
									treatChecking = false;
								}
								if (treatCheck[y][x] == playerTwo && treatCheck[y][x + 1] == empty && treatCheck[y + 1][x + 1] != empty && treatCheck[y][x + 2] == playerTwo && treatCheck[y][x + 3] == playerTwo)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}

						//Check Y range ON last row
						else
						{
							if (x < boardX - 3)
							{
								if (treatCheck[y][x] == playerTwo && treatCheck[y][x + 1] == playerTwo && treatCheck[y][x + 2] == empty && treatCheck[y][x + 3] == playerTwo)
								{
									rowSelected = x + 2;
									selectColumn = false;
									treatChecking = false;
								}
								if (treatCheck[y][x] == playerTwo && treatCheck[y][x + 1] == empty && treatCheck[y][x + 2] == playerTwo && treatCheck[y][x + 3] == playerTwo)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
					}
					else {}
				}
			}

			//Vertically - check for treat of 4 in a column
			for (int y = 0; y < boardY; y++) //Set Y
			{
				for (int x = 0; x < boardX; x++) //Set X
				{
					if (treatCheck[0][x] == empty)
					{
						if (y > 2)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x] == playerTwo && treatCheck[y - 2][x] == playerTwo)
							{
								if (treatCheck[y - 3][x] == empty)
								{
									rowSelected = x;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
					}
					else {}
				}
			}

			//Diagonally -> - check for treat of 4 in a row
			for (int y = 0; y < boardY; y++) //Set Y
			{
				for (int x = 0; x < boardX; x++) //Set X
				{
					if (treatCheck[0][x] == empty)
					{
						//Red horizontally
						if (y == 2 && x > 0 && x < boardX - 3)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x + 1] == playerTwo && treatCheck[y - 2][x + 2] == playerTwo)
							{
								if (treatCheck[y + 1][x - 1] == empty && treatCheck[y + 2][x - 1] != empty)
								{
									rowSelected = x - 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Red vertically
						else if (y > 1 && y < boardY - 1 && x == 4)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x + 1] == playerTwo && treatCheck[y - 2][x + 2] == playerTwo)
							{
								if (treatCheck[y + 1][x - 1] == empty && treatCheck[y + 2][x - 1] != empty)
								{
									rowSelected = x - 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Green horizontally
						else if (y == boardY - 1 && x > 0 && x < boardX - 3)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x + 1] == playerTwo && treatCheck[y - 2][x + 2] == playerTwo)
							{
								if (treatCheck[y - 3][x + 3] == empty && treatCheck[y - 2][x + 3] != empty)
								{
									rowSelected = x + 3;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Green vertically
						else if (y > 2 && y < boardY && x == 0)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x + 1] == playerTwo && treatCheck[y - 2][x + 2] == playerTwo)
							{
								if (treatCheck[y - 3][x + 3] == empty && treatCheck[y - 2][x + 3] != empty)
								{
									rowSelected = x + 3;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Yellow - row 1
						else if (y > 2 && y < boardY - 2 && x > 0 && x < boardX - 3)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x + 1] == playerTwo && treatCheck[y - 2][x + 2] == playerTwo)
							{
								if (treatCheck[y - 3][x + 3] == empty && treatCheck[y - 2][x + 3] != empty && treatCheck[y + 1][x - 1] == empty && treatCheck[y + 2][x + 1] != empty)
								{
									rngAIChooseSides(chooseSide);

									if (chooseSide == 0)
									{
										rowSelected = x + 3;
										selectColumn = false;
										treatChecking = false;
									}
									else
									{
										rowSelected = x - 1;
										selectColumn = false;
										treatChecking = false;
									}

								}
								else if (treatCheck[y - 3][x + 3] == empty && treatCheck[y - 2][x + 3] != empty)
								{
									rowSelected = x + 3;
									selectColumn = false;
									treatChecking = false;
								}
								else if (treatCheck[y + 1][x - 1] == empty && treatCheck[y + 2][x - 1] != empty)
								{
									rowSelected = x - 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Yellow - row 2
						else if (y > 3 && y < boardY - 1 && x > 0 && x < boardX - 3)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x + 1] == playerTwo && treatCheck[y - 2][x + 2] == playerTwo)
							{
								if (treatCheck[y - 3][x + 3] == empty && treatCheck[y - 2][x + 3] != empty && treatCheck[y + 1][x - 1] == empty)
								{
									rngAIChooseSides(chooseSide);

									if (chooseSide == 0)
									{
										rowSelected = x + 3;
										selectColumn = false;
										treatChecking = false;
									}
									else
									{
										rowSelected = x - 1;
										selectColumn = false;
										treatChecking = false;
									}

								}
								else if (treatCheck[y - 3][x + 3] == empty && treatCheck[y - 2][x + 3] != empty)
								{
									rowSelected = x + 3;
									selectColumn = false;
									treatChecking = false;
								}
								else if (treatCheck[y + 1][x - 1] == empty)
								{
									rowSelected = x - 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
					}
					else {}
				}
			}

			//Diagonally -> - check for treat of 4 in a row with input in between
			for (int y = 0; y < boardY; y++) //Set Y
			{
				for (int x = 0; x < boardX; x++) //Set X
				{
					if (treatCheck[0][x] == empty)
					{
						//Green horizontally
						if (y == boardY - 1 && x > 0 && x < boardX - 3)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x + 1] == playerTwo && treatCheck[y - 2][x + 2] == empty && treatCheck[y - 3][x + 3] == playerTwo)
							{
								if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty)
								{
									rowSelected = x + 2;
									selectColumn = false;
									treatChecking = false;
								}
							}
							else if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x + 1] == empty && treatCheck[y - 2][x + 2] == playerTwo && treatCheck[y - 3][x + 3] == playerTwo)
							{
								if (treatCheck[y - 1][x + 1] == empty && treatCheck[y][x + 1] != empty)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Green vertically
						else if (y > 2 && y < boardY && x == 0)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x + 1] == playerTwo && treatCheck[y - 2][x + 2] == empty && treatCheck[y - 3][x + 3] == playerTwo)
							{
								if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty)
								{
									rowSelected = x + 2;
									selectColumn = false;
									treatChecking = false;
								}
							}
							else if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x + 1] == empty && treatCheck[y - 2][x + 2] == playerTwo && treatCheck[y - 3][x + 3] == playerTwo)
							{
								if (treatCheck[y - 1][x + 1] == empty && treatCheck[y][x + 1] != empty)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Yellow
						else if (y > 2 && y < boardY - 1 && x > 0 && x < boardX - 3)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x + 1] == playerTwo && treatCheck[y - 2][x + 2] == empty && treatCheck[y - 3][x + 3] == playerTwo)
							{
								if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty)
								{
									rowSelected = x + 2;
									selectColumn = false;
									treatChecking = false;
								}
							}
							else if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x + 1] == empty && treatCheck[y - 2][x + 2] == playerTwo && treatCheck[y - 3][x + 3] == playerTwo)
							{
								if (treatCheck[y - 1][x + 1] == empty && treatCheck[y][x + 1] != empty)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
					}
					else {}
				}
			}

			//Diagonally <- - check for treat of 4 in a row
			for (int y = 0; y < boardY; y++) //Set Y
			{
				for (int x = 0; x < boardX; x++) //Set X
				{
					if (treatCheck[0][x] == empty)
					{
						//Red horizontally
						if (y == 2 && x > 2 && x < boardX - 1)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x - 1] == playerTwo && treatCheck[y - 2][x - 2] == playerTwo)
							{
								if (treatCheck[y + 1][x + 1] == empty && treatCheck[y + 2][x + 1] != empty)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Red vertically
						else if (y > 1 && y < boardY - 1 && x == 2)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x - 1] == playerTwo && treatCheck[y - 2][x - 2] == playerTwo)
							{
								if (treatCheck[y + 1][x + 1] == empty && treatCheck[y + 2][x + 1] != empty)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Green horizontally
						else if (y == boardY - 1 && x > 2 && x < boardX - 1)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x - 1] == playerTwo && treatCheck[y - 2][x - 2] == playerTwo)
							{
								if (treatCheck[y - 3][x - 3] == empty && treatCheck[y - 2][x - 3] != empty)
								{
									rowSelected = x - 3;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Green vertically
						else if (y > 2 && y < boardY && x == boardX - 1)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x - 1] == playerTwo && treatCheck[y - 2][x - 2] == playerTwo)
							{
								if (treatCheck[y - 3][x - 3] == empty && treatCheck[y - 2][x - 3] != empty)
								{
									rowSelected = x - 3;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Yellow - row 1
						else if (y > 2 && y < boardY - 2 && x > 2 && x < boardX - 1)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x - 1] == playerTwo && treatCheck[y - 2][x - 2] == playerTwo)
							{
								if (treatCheck[y - 3][x - 3] == empty && treatCheck[y - 2][x - 3] != empty && treatCheck[y + 1][x + 1] == empty && treatCheck[y + 2][x + 1] != empty)
								{
									rngAIChooseSides(chooseSide);

									if (chooseSide == 0)
									{
										rowSelected = x - 3;
										selectColumn = false;
										treatChecking = false;
									}
									else
									{
										rowSelected = x + 1;
										selectColumn = false;
										treatChecking = false;
									}

								}
								else if (treatCheck[y - 3][x - 3] == empty && treatCheck[y - 2][x - 3] != empty)
								{
									rowSelected = x - 3;
									selectColumn = false;
									treatChecking = false;
								}
								else if (treatCheck[y + 1][x + 1] == empty && treatCheck[y + 2][x + 1] != empty)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Yellow - row 2
						else if (y > 3 && y < boardY - 1 && x > 2 && x < boardX - 1)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x - 1] == playerTwo && treatCheck[y - 2][x - 2] == playerTwo)
							{
								if (treatCheck[y - 3][x - 3] == empty && treatCheck[y - 2][x - 3] != empty && treatCheck[y + 1][x + 1] == empty)
								{
									rngAIChooseSides(chooseSide);

									if (chooseSide == 0)
									{
										rowSelected = x - 3;
										selectColumn = false;
										treatChecking = false;
									}
									else
									{
										rowSelected = x + 1;
										selectColumn = false;
										treatChecking = false;
									}

								}
								else if (treatCheck[y - 3][x - 3] == empty && treatCheck[y - 2][x - 3] != empty)
								{
									rowSelected = x - 3;
									selectColumn = false;
									treatChecking = false;
								}
								else if (treatCheck[y + 1][x + 1] == empty)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
					}
					else {}
				}
			}

			//Diagonally <- - check for treat of 4 in a row with input in between
			for (int y = 0; y < boardY; y++) //Set Y
			{
				for (int x = 0; x < boardX; x++) //Set X
				{
					if (treatCheck[0][x] == empty)
					{
						//Green horizontally
						if (y == boardY - 1 && x > 2 && x < boardX - 1)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x - 1] == playerTwo && treatCheck[y - 2][x - 2] == empty && treatCheck[y - 3][x - 3] == playerTwo)
							{
								if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty)
								{
									rowSelected = x - 2;
									selectColumn = false;
									treatChecking = false;
								}
							}
							else if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x - 1] == empty && treatCheck[y - 2][x - 2] == playerTwo && treatCheck[y - 3][x - 3] == playerTwo)
							{
								if (treatCheck[y - 1][x - 1] == empty && treatCheck[y][x - 1] != empty)
								{
									rowSelected = x - 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Green vertically
						else if (y > 2 && y < boardY && x == boardX - 1)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x - 1] == playerTwo && treatCheck[y - 2][x - 2] == empty && treatCheck[y - 3][x - 3] == playerTwo)
							{
								if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty)
								{
									rowSelected = x - 2;
									selectColumn = false;
									treatChecking = false;
								}
							}
							else if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x - 1] == empty && treatCheck[y - 2][x - 2] == playerTwo && treatCheck[y - 3][x - 3] == playerTwo)
							{
								if (treatCheck[y - 1][x - 1] == empty && treatCheck[y][x - 1] != empty)
								{
									rowSelected = x - 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Yellow
						else if (y > 2 && y < boardY - 1 && x > 2 && x < boardX - 1)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x - 1] == playerTwo && treatCheck[y - 2][x - 2] == empty && treatCheck[y - 3][x - 3] == playerTwo)
							{
								if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty)
								{
									rowSelected = x - 2;
									selectColumn = false;
									treatChecking = false;
								}
							}
							else if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x - 1] == empty && treatCheck[y - 2][x - 2] == playerTwo && treatCheck[y - 3][x - 3] == playerTwo)
							{
								if (treatCheck[y - 1][x - 1] == empty && treatCheck[y][x - 1] != empty)
								{
									rowSelected = x - 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
					}
					else {}
				}
			}
			#pragma endregion
		}

		if (treatChecking)
		{
			#pragma region For 3 in a row - Opponent
			//Horisontally - check for treat of 4 in a row
			for (int y = 0; y < boardY; y++) //Set Y
			{
				for (int x = 0; x < boardX; x++) //Set X
				{
					if (treatCheck[0][x] == empty)
					{
						//Check Y range ABOVE last row
						if (y < boardY - 1)
						{
							if (x < boardX - 2)
							{
								if (treatCheck[y][x] == playerOne && treatCheck[y][x + 1] == playerOne && treatCheck[y][x + 2] == playerOne)
								{
									if (x == 0)
									{
										if (treatCheck[y][x + 3] == empty && treatCheck[y + 1][x + 3] != empty)
										{
											rowSelected = x + 3;
											selectColumn = false;
											treatChecking = false;
										}
									}
									else if (x == boardX - 3)
									{
										if (treatCheck[y][x - 1] == empty && treatCheck[y + 1][x - 1] != empty)
										{
											rowSelected = x - 1;
											selectColumn = false;
											treatChecking = false;
										}
									}
									else
									{
										if (treatCheck[y][x + 3] == empty && treatCheck[y][x - 1] == empty && treatCheck[y + 1][x + 3] != empty && treatCheck[y + 1][x - 1] != empty)
										{
											rngAIChooseSides(chooseSide);
											if (chooseSide == 0)
											{
												rowSelected = x + 3;
												selectColumn = false;
												treatChecking = false;
											}
											else
											{
												rowSelected = x - 1;
												selectColumn = false;
												treatChecking = false;
											}
										}
										else if (treatCheck[y][x + 3] == empty && treatCheck[y + 1][x + 3] != empty)
										{
											rowSelected = x + 3;
											selectColumn = false;
											treatChecking = false;
										}
										else if (treatCheck[y][x - 1] == empty && treatCheck[y + 1][x - 1] != empty)
										{
											rowSelected = x - 1;
											selectColumn = false;
											treatChecking = false;
										}
									}
								}
							}
						}

						//Check Y range ON last row
						else
						{
							if (x < boardX - 2)
							{
								if (treatCheck[y][x] == playerOne && treatCheck[y][x + 1] == playerOne && treatCheck[y][x + 2] == playerOne)
								{
									if (x == 0)
									{
										if (treatCheck[y][x + 3] == empty)
										{
											rowSelected = x + 3;
											selectColumn = false;
											treatChecking = false;
										}
									}
									else if (x == boardX - 3)
									{
										if (treatCheck[y][x - 1] == empty)
										{
											rowSelected = x - 1;
											selectColumn = false;
											treatChecking = false;
										}
									}
									else
									{
										if (treatCheck[y][x + 3] == empty && treatCheck[y][x - 1] == empty)
										{
											rngAIChooseSides(chooseSide);
											if (chooseSide == 0)
											{
												rowSelected = x + 3;
												selectColumn = false;
												treatChecking = false;
											}
											else
											{
												rowSelected = x - 1;
												selectColumn = false;
												treatChecking = false;
											}
										}
										else if (treatCheck[y][x + 3] == empty)
										{
											rowSelected = x + 3;
											selectColumn = false;
											treatChecking = false;
										}
										else if (treatCheck[y][x - 1] == empty)
										{
											rowSelected = x - 1;
											selectColumn = false;
											treatChecking = false;
										}
									}
								}
							}
						}
					}
					else {}
				}
			}

			//Horisontally - check for treat of 4 in a row with input in between
			for (int y = 0; y < boardY; y++) //Set Y
			{
				for (int x = 0; x < boardX; x++) //Set X
				{
					if (treatCheck[0][x] == empty)
					{
						//Check Y range ABOVE last row
						if (y < boardY - 1)
						{
							if (x < boardX - 3)
							{
								if (treatCheck[y][x] == playerOne && treatCheck[y][x + 1] == playerOne && treatCheck[y][x + 2] == empty && treatCheck[y + 1][x + 2] != empty && treatCheck[y][x + 3] == playerOne)
								{
									rowSelected = x + 2;
									selectColumn = false;
									treatChecking = false;
								}
								if (treatCheck[y][x] == playerOne && treatCheck[y][x + 1] == empty && treatCheck[y + 1][x + 1] != empty && treatCheck[y][x + 2] == playerOne && treatCheck[y][x + 3] == playerOne)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}

						//Check Y range ON last row
						else
						{
							if (x < boardX - 3)
							{
								if (treatCheck[y][x] == playerOne && treatCheck[y][x + 1] == playerOne && treatCheck[y][x + 2] == empty && treatCheck[y][x + 3] == playerOne)
								{
									rowSelected = x + 2;
									selectColumn = false;
									treatChecking = false;
								}
								if (treatCheck[y][x] == playerOne && treatCheck[y][x + 1] == empty && treatCheck[y][x + 2] == playerOne && treatCheck[y][x + 3] == playerOne)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
					}
					else {}
				}
			}

			//Vertically - check for treat of 4 in a column
			for (int y = 0; y < boardY; y++) //Set Y
			{
				for (int x = 0; x < boardX; x++) //Set X
				{
					if (treatCheck[0][x] == empty)
					{
						if (y > 2)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x] == playerOne && treatCheck[y - 2][x] == playerOne)
							{
								if (treatCheck[y - 3][x] == empty)
								{
									rowSelected = x;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
					}
					else {}
				}
			}

			//Diagonally -> - check for treat of 4 in a row
			for (int y = 0; y < boardY; y++) //Set Y
			{
				for (int x = 0; x < boardX; x++) //Set X
				{
					if (treatCheck[0][x] == empty)
					{
						//Red horizontally
						if (y == 2 && x > 0 && x < boardX - 3)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x + 1] == playerOne && treatCheck[y - 2][x + 2] == playerOne)
							{
								if (treatCheck[y + 1][x - 1] == empty && treatCheck[y + 2][x - 1] != empty)
								{
									rowSelected = x - 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Red vertically
						else if (y > 1 && y < boardY - 1 && x == 4)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x + 1] == playerOne && treatCheck[y - 2][x + 2] == playerOne)
							{
								if (treatCheck[y + 1][x - 1] == empty && treatCheck[y + 2][x - 1] != empty)
								{
									rowSelected = x - 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Green horizontally
						else if (y == boardY - 1 && x > 0 && x < boardX - 3)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x + 1] == playerOne && treatCheck[y - 2][x + 2] == playerOne)
							{
								if (treatCheck[y - 3][x + 3] == empty && treatCheck[y - 2][x + 3] != empty)
								{
									rowSelected = x + 3;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Green vertically
						else if (y > 2 && y < boardY && x == 0)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x + 1] == playerOne && treatCheck[y - 2][x + 2] == playerOne)
							{
								if (treatCheck[y - 3][x + 3] == empty && treatCheck[y - 2][x + 3] != empty)
								{
									rowSelected = x + 3;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Yellow - row 1
						else if (y > 2 && y < boardY - 2 && x > 0 && x < boardX - 3)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x + 1] == playerOne && treatCheck[y - 2][x + 2] == playerOne)
							{
								if (treatCheck[y - 3][x + 3] == empty && treatCheck[y - 2][x + 3] != empty && treatCheck[y + 1][x - 1] == empty && treatCheck[y + 2][x + 1] != empty)
								{
									rngAIChooseSides(chooseSide);

									if (chooseSide == 0)
									{
										rowSelected = x + 3;
										selectColumn = false;
										treatChecking = false;
									}
									else
									{
										rowSelected = x - 1;
										selectColumn = false;
										treatChecking = false;
									}

								}
								else if (treatCheck[y - 3][x + 3] == empty && treatCheck[y - 2][x + 3] != empty)
								{
									rowSelected = x + 3;
									selectColumn = false;
									treatChecking = false;
								}
								else if (treatCheck[y + 1][x - 1] == empty && treatCheck[y + 2][x - 1] != empty)
								{
									rowSelected = x - 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Yellow - row 2
						else if (y > 3 && y < boardY - 1 && x > 0 && x < boardX - 3)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x + 1] == playerOne && treatCheck[y - 2][x + 2] == playerOne)
							{
								if (treatCheck[y - 3][x + 3] == empty && treatCheck[y - 2][x + 3] != empty && treatCheck[y + 1][x - 1] == empty)
								{
									rngAIChooseSides(chooseSide);

									if (chooseSide == 0)
									{
										rowSelected = x + 3;
										selectColumn = false;
										treatChecking = false;
									}
									else
									{
										rowSelected = x - 1;
										selectColumn = false;
										treatChecking = false;
									}

								}
								else if (treatCheck[y - 3][x + 3] == empty && treatCheck[y - 2][x + 3] != empty)
								{
									rowSelected = x + 3;
									selectColumn = false;
									treatChecking = false;
								}
								else if (treatCheck[y + 1][x - 1] == empty)
								{
									rowSelected = x - 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
					}
					else {}
				}
			}

			//Diagonally -> - check for treat of 4 in a row with input in between
			for (int y = 0; y < boardY; y++) //Set Y
			{
				for (int x = 0; x < boardX; x++) //Set X
				{
					if (treatCheck[0][x] == empty)
					{
						//Green horizontally
						if (y == boardY - 1 && x > 0 && x < boardX - 3)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x + 1] == playerOne && treatCheck[y - 2][x + 2] == empty && treatCheck[y - 3][x + 3] == playerOne)
							{
								if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty)
								{
									rowSelected = x + 2;
									selectColumn = false;
									treatChecking = false;
								}
							}
							else if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x + 1] == empty && treatCheck[y - 2][x + 2] == playerOne && treatCheck[y - 3][x + 3] == playerOne)
							{
								if (treatCheck[y - 1][x + 1] == empty && treatCheck[y][x + 1] != empty)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Green vertically
						else if (y > 2 && y < boardY && x == 0)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x + 1] == playerOne && treatCheck[y - 2][x + 2] == empty && treatCheck[y - 3][x + 3] == playerOne)
							{
								if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty)
								{
									rowSelected = x + 2;
									selectColumn = false;
									treatChecking = false;
								}
							}
							else if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x + 1] == empty && treatCheck[y - 2][x + 2] == playerOne && treatCheck[y - 3][x + 3] == playerOne)
							{
								if (treatCheck[y - 1][x + 1] == empty && treatCheck[y][x + 1] != empty)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Yellow
						else if (y > 2 && y < boardY - 1 && x > 0 && x < boardX - 3)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x + 1] == playerOne && treatCheck[y - 2][x + 2] == empty && treatCheck[y - 3][x + 3] == playerOne)
							{
								if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty)
								{
									rowSelected = x + 2;
									selectColumn = false;
									treatChecking = false;
								}
							}
							else if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x + 1] == empty && treatCheck[y - 2][x + 2] == playerOne && treatCheck[y - 3][x + 3] == playerOne)
							{
								if (treatCheck[y - 1][x + 1] == empty && treatCheck[y][x + 1] != empty)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
					}
					else {}
				}
			}

			//Diagonally <- - check for treat of 4 in a row
			for (int y = 0; y < boardY; y++) //Set Y
			{
				for (int x = 0; x < boardX; x++) //Set X
				{
					if (treatCheck[0][x] == empty)
					{
						//Red horizontally
						if (y == 2 && x > 2 && x < boardX - 1)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x - 1] == playerOne && treatCheck[y - 2][x - 2] == playerOne)
							{
								if (treatCheck[y + 1][x + 1] == empty && treatCheck[y + 2][x + 1] != empty)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Red vertically
						else if (y > 1 && y < boardY - 1 && x == 2)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x - 1] == playerOne && treatCheck[y - 2][x - 2] == playerOne)
							{
								if (treatCheck[y + 1][x + 1] == empty && treatCheck[y + 2][x + 1] != empty)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Green horizontally
						else if (y == boardY - 1 && x > 2 && x < boardX - 1)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x - 1] == playerOne && treatCheck[y - 2][x - 2] == playerOne)
							{
								if (treatCheck[y - 3][x - 3] == empty && treatCheck[y - 2][x - 3] != empty)
								{
									rowSelected = x - 3;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Green vertically
						else if (y > 2 && y < boardY && x == boardX - 1)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x - 1] == playerOne && treatCheck[y - 2][x - 2] == playerOne)
							{
								if (treatCheck[y - 3][x - 3] == empty && treatCheck[y - 2][x - 3] != empty)
								{
									rowSelected = x - 3;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Yellow - row 2
						else if (y > 2 && y < boardY - 2 && x > 2 && x < boardX - 1)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x - 1] == playerOne && treatCheck[y - 2][x - 2] == playerOne)
							{
								if (treatCheck[y - 3][x - 3] == empty && treatCheck[y - 2][x - 3] != empty && treatCheck[y + 1][x + 1] == empty && treatCheck[y + 2][x + 1] != empty)
								{
									rngAIChooseSides(chooseSide);

									if (chooseSide == 0)
									{
										rowSelected = x - 3;
										selectColumn = false;
										treatChecking = false;
									}
									else
									{
										rowSelected = x + 1;
										selectColumn = false;
										treatChecking = false;
									}

								}
								else if (treatCheck[y - 3][x - 3] == empty && treatCheck[y - 2][x - 3] != empty)
								{
									rowSelected = x - 3;
									selectColumn = false;
									treatChecking = false;
								}
								else if (treatCheck[y + 1][x + 1] == empty && treatCheck[y + 2][x + 1] != empty)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Yellow - row 1
						else if (y > 3 && y < boardY - 1 && x > 2 && x < boardX - 1)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x - 1] == playerOne && treatCheck[y - 2][x - 2] == playerOne)
							{
								if (treatCheck[y - 3][x - 3] == empty && treatCheck[y - 2][x - 3] != empty && treatCheck[y + 1][x + 1] == empty)
								{
									rngAIChooseSides(chooseSide);

									if (chooseSide == 0)
									{
										rowSelected = x - 3;
										selectColumn = false;
										treatChecking = false;
									}
									else
									{
										rowSelected = x + 1;
										selectColumn = false;
										treatChecking = false;
									}

								}
								else if (treatCheck[y - 3][x - 3] == empty && treatCheck[y - 2][x - 3] != empty)
								{
									rowSelected = x - 3;
									selectColumn = false;
									treatChecking = false;
								}
								else if (treatCheck[y + 1][x + 1] == empty)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
					}
					else {}
				}
			}

			//Diagonally <- - check for treat of 4 in a row with input in between
			for (int y = 0; y < boardY; y++) //Set Y
			{
				for (int x = 0; x < boardX; x++) //Set X
				{
					if (treatCheck[0][x] == empty)
					{
						//Green horizontally
						if (y == boardY - 1 && x > 2 && x < boardX - 1)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x - 1] == playerOne && treatCheck[y - 2][x - 2] == empty && treatCheck[y - 3][x - 3] == playerOne)
							{
								if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty)
								{
									rowSelected = x - 2;
									selectColumn = false;
									treatChecking = false;
								}
							}
							else if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x - 1] == empty && treatCheck[y - 2][x - 2] == playerOne && treatCheck[y - 3][x - 3] == playerOne)
							{
								if (treatCheck[y - 1][x - 1] == empty && treatCheck[y][x - 1] != empty)
								{
									rowSelected = x - 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Green vertically
						else if (y > 2 && y < boardY && x == boardX - 1)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x - 1] == playerOne && treatCheck[y - 2][x - 2] == empty && treatCheck[y - 3][x - 3] == playerOne)
							{
								if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty)
								{
									rowSelected = x - 2;
									selectColumn = false;
									treatChecking = false;
								}
							}
							else if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x - 1] == empty && treatCheck[y - 2][x - 2] == playerOne && treatCheck[y - 3][x - 3] == playerOne)
							{
								if (treatCheck[y - 1][x - 1] == empty && treatCheck[y][x - 1] != empty)
								{
									rowSelected = x - 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Yellow
						else if (y > 2 && y < boardY - 1 && x > 2 && x < boardX - 1)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x - 1] == playerOne && treatCheck[y - 2][x - 2] == empty && treatCheck[y - 3][x - 3] == playerOne)
							{
								if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty)
								{
									rowSelected = x - 2;
									selectColumn = false;
									treatChecking = false;
								}
							}
							else if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x - 1] == empty && treatCheck[y - 2][x - 2] == playerOne && treatCheck[y - 3][x - 3] == playerOne)
							{
								if (treatCheck[y - 1][x - 1] == empty && treatCheck[y][x - 1] != empty)
								{
									rowSelected = x - 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
					}
					else {}
				}
			}
			#pragma endregion
		}
		
		if (treatChecking)
		{
			#pragma region 2 in a row (alone)- Horizontally - AI
			//Horisontally - check for treat of only 2 in a row
			for (int y = 0; y < boardY; y++) //Set Y
			{
				for (int x = 0; x < boardX; x++) //Set X
				{
					if (treatCheck[0][x] == empty)
					{
						//Check Y range ABOVE last row
						if (y < boardY - 1)
						{
							if (x < boardX - 2)
							{
								if (treatCheck[y][x] == playerTwo && treatCheck[y][x + 1] == playerTwo)
								{
									if (x == 0) {}
									else if (x == boardX - 2) {}
									else
									{
										if (treatCheck[y][x + 2] == empty && treatCheck[y][x - 1] == empty && treatCheck[y + 1][x + 2] != empty && treatCheck[y + 1][x - 1] != empty)
										{
											rngAIChooseSides(chooseSide);
											if (chooseSide == 0)
											{
												rowSelected = x + 2;
												selectColumn = false;
												treatChecking = false;
											}
											else
											{
												rowSelected = x - 1;
												selectColumn = false;
												treatChecking = false;
											}
										}
									}
								}
							}
						}

						//Check Y range ON last row
						else
						{
							if (x < boardX - 1)
							{
								if (treatCheck[y][x] == playerTwo && treatCheck[y][x + 1] == playerTwo)
								{
									if (x == 0) {}
									else if (x == boardX - 2) {}
									else
									{
										if (treatCheck[y][x + 2] == empty && treatCheck[y][x - 1] == empty)
										{
											rngAIChooseSides(chooseSide);
											if (chooseSide == 0)
											{
												rowSelected = x + 2;
												selectColumn = false;
												treatChecking = false;
											}
											else
											{
												rowSelected = x - 1;
												selectColumn = false;
												treatChecking = false;
											}
										}
									}
								}
							}
						}
					}
					else {}
				}
			}
			#pragma endregion
		}
		
		if (treatChecking)
		{
			#pragma region 2 in a row (alone) - Horizontally - AI
			//Horisontally - check for treat of only 2 in a row
			for (int y = 0; y < boardY; y++) //Set Y
			{
				for (int x = 0; x < boardX; x++) //Set X
				{
					if (treatCheck[0][x] == empty)
					{
						//Check Y range ABOVE last row
						if (y < boardY - 1)
						{
							if (x < boardX - 2)
							{
								if (treatCheck[y][x] == playerOne && treatCheck[y][x + 1] == playerOne)
								{
									if (x == 0) {}
									else if (x == boardX - 2) {}
									else
									{
										if (treatCheck[y][x + 2] == empty && treatCheck[y][x - 1] == empty && treatCheck[y + 1][x + 2] != empty && treatCheck[y + 1][x - 1] != empty)
										{
											rngAIChooseSides(chooseSide);
											if (chooseSide == 0)
											{
												rowSelected = x + 2;
												selectColumn = false;
												treatChecking = false;
											}
											else
											{
												rowSelected = x - 1;
												selectColumn = false;
												treatChecking = false;
											}
										}
									}
								}
							}
						}

						//Check Y range ON last row
						else
						{
							if (x < boardX - 1)
							{
								if (treatCheck[y][x] == playerOne && treatCheck[y][x + 1] == playerOne)
								{
									if (x == 0) {}
									else if (x == boardX - 2) {}
									else
									{
										if (treatCheck[y][x + 2] == empty && treatCheck[y][x - 1] == empty)
										{
											rngAIChooseSides(chooseSide);
											if (chooseSide == 0)
											{
												rowSelected = x + 2;
												selectColumn = false;
												treatChecking = false;
											}
											else
											{
												rowSelected = x - 1;
												selectColumn = false;
												treatChecking = false;
											}
										}
									}
								}
							}
						}
					}
					else {}
				}
			}
			#pragma endregion
		}

		if (treatChecking)
		{
			#pragma region For 2 in a row - Opponent
			//Horisontally - check for treat of 3 in a row
			for (int y = 0; y < boardY; y++) //Set Y
			{
				for (int x = 0; x < boardX; x++) //Set X
				{
					if (treatCheck[0][x] == empty)
					{
						//Check Y range ABOVE last row
						if (y < boardY - 1)
						{
							if (x < boardX - 1)
							{
								if (treatCheck[y][x] == playerOne && treatCheck[y][x + 1] == playerOne)
								{
									if (x == 0)
									{
										if (treatCheck[y][x + 2] == empty && treatCheck[y + 1][x + 2] != empty)
										{
											rowSelected = x + 2;
											selectColumn = false;
											treatChecking = false;
										}
									}
									else if (x == boardX - 2)
									{
										if (treatCheck[y][x - 1] == empty && treatCheck[y + 1][x - 1] != empty)
										{
											rowSelected = x - 1;
											selectColumn = false;
											treatChecking = false;
										}
									}
									else
									{
										if (treatCheck[y][x + 2] == empty && treatCheck[y][x - 1] == empty && treatCheck[y + 1][x + 2] != empty && treatCheck[y + 1][x - 1] != empty)
										{
											rngAIChooseSides(chooseSide);
											if (chooseSide == 0)
											{
												rowSelected = x + 2;
												selectColumn = false;
												treatChecking = false;
											}
											else
											{
												rowSelected = x - 1;
												selectColumn = false;
												treatChecking = false;
											}
										}
										else if (treatCheck[y][x + 2] == empty && treatCheck[y + 1][x + 2] != empty)
										{
											rowSelected = x + 2;
											selectColumn = false;
											treatChecking = false;
										}
										else if (treatCheck[y][x - 1] == empty && treatCheck[y + 1][x - 1] != empty)
										{
											rowSelected = x - 1;
											selectColumn = false;
											treatChecking = false;
										}
									}
								}
							}
						}

						//Check Y range ON last row
						else
						{
							if (x < boardX - 1)
							{
								if (treatCheck[y][x] == playerOne && treatCheck[y][x + 1] == playerOne)
								{
									if (x == 0)
									{
										if (treatCheck[y][x + 2] == empty)
										{
											rowSelected = x + 2;
											selectColumn = false;
											treatChecking = false;
										}
									}
									else if (x == boardX - 2)
									{
										if (treatCheck[y][x - 1] == empty)
										{
											rowSelected = x - 1;
											selectColumn = false;
											treatChecking = false;
										}
									}
									else
									{
										if (treatCheck[y][x + 2] == empty && treatCheck[y][x - 1] == empty)
										{
											rngAIChooseSides(chooseSide);
											if (chooseSide == 0)
											{
												rowSelected = x + 2;
												selectColumn = false;
												treatChecking = false;
											}
											else
											{
												rowSelected = x - 1;
												selectColumn = false;
												treatChecking = false;
											}
										}
										else if (treatCheck[y][x + 2] == empty)
										{
											rowSelected = x + 2;
											selectColumn = false;
											treatChecking = false;
										}
										else if (treatCheck[y][x - 1] == empty)
										{
											rowSelected = x - 1;
											selectColumn = false;
											treatChecking = false;
										}
									}
								}
							}
						}
					}
					else {}
				}
			}

			//Vertically - check for treat of 3 in a column
			for (int y = 0; y < boardY; y++) //Set Y
			{
				for (int x = 0; x < boardX; x++) //Set X
				{
					if (treatCheck[0][x] == empty)
					{
						if (y > 1)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x] == playerOne)
							{
								if (treatCheck[y - 2][x] == empty)
								{
									rowSelected = x;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
					}
					else {}
				}
			}

			//Diagonally -> - check for treat of 3 in a row
			for (int y = 0; y < boardY; y++) //Set Y
			{
				for (int x = 0; x < boardX; x++) //Set X
				{
					if (treatCheck[0][x] == empty)
					{
						//Red horizontally
						if (y == 2 && x > 0 && x < boardX - 3)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x + 1] == playerOne)
							{
								if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty && treatCheck[y + 1][x - 1] == empty && treatCheck[y + 2][x - 1] != empty)
								{
									rngAIChooseSides(chooseSide);

									if (chooseSide == 0)
									{
										rowSelected = x + 2;
										selectColumn = false;
										treatChecking = false;
									}
									else
									{
										rowSelected = x - 1;
										selectColumn = false;
										treatChecking = false;
									}
								}
								else if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty)
								{
									rowSelected = x + 2;
									selectColumn = false;
									treatChecking = false;
								}
								else if (treatCheck[y + 1][x - 1] == empty && treatCheck[y + 2][x - 1] != empty)
								{
									rowSelected = x - 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Red vertically
						else if (y > 1 && y < boardY - 1 && x == 4)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x + 1] == playerOne)
							{
								if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty && treatCheck[y + 1][x - 1] == empty && treatCheck[y + 2][x - 1] != empty)
								{
									rngAIChooseSides(chooseSide);

									if (chooseSide == 0)
									{
										rowSelected = x + 2;
										selectColumn = false;
										treatChecking = false;
									}
									else
									{
										rowSelected = x - 1;
										selectColumn = false;
										treatChecking = false;
									}
								}
								else if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty)
								{
									rowSelected = x + 2;
									selectColumn = false;
									treatChecking = false;
								}
								else if (treatCheck[y + 1][x - 1] == empty && treatCheck[y + 2][x - 1] != empty)
								{
									rowSelected = x - 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Green horizontally
						else if (y == boardY - 1 && x > 0 && x < boardX - 3)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x + 1] == playerOne)
							{
								if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty)
								{
									rowSelected = x + 2;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Green vertically
						else if (y > 2 && y < boardY && x == 0)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x + 1] == playerOne)
							{
								if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty)
								{
									rowSelected = x + 2;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Yellow - row 1
						else if (y > 2 && y < boardY - 2 && x > 0 && x < boardX - 3)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x + 1] == playerOne)
							{
								if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty && treatCheck[y + 1][x - 1] == empty && treatCheck[y + 2][x + 1] != empty)
								{
									rngAIChooseSides(chooseSide);

									if (chooseSide == 0)
									{
										rowSelected = x + 2;
										selectColumn = false;
										treatChecking = false;
									}
									else
									{
										rowSelected = x - 1;
										selectColumn = false;
										treatChecking = false;
									}

								}
								else if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty)
								{
									rowSelected = x + 2;
									selectColumn = false;
									treatChecking = false;
								}
								else if (treatCheck[y + 1][x - 1] == empty && treatCheck[y + 2][x - 1] != empty)
								{
									rowSelected = x - 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Yellow - row 2
						else if (y > 3 && y < boardY - 1 && x > 0 && x < boardX - 3)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x + 1] == playerOne)
							{
								if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty && treatCheck[y + 1][x - 1] == empty)
								{
									rngAIChooseSides(chooseSide);

									if (chooseSide == 0)
									{
										rowSelected = x + 2;
										selectColumn = false;
										treatChecking = false;
									}
									else
									{
										rowSelected = x - 1;
										selectColumn = false;
										treatChecking = false;
									}

								}
								else if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty)
								{
									rowSelected = x + 2;
									selectColumn = false;
									treatChecking = false;
								}
								else if (treatCheck[y + 1][x - 1] == empty)
								{
									rowSelected = x - 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
					}
					else {}
				}
			}

			//Diagonally <- - check for treat of 4 in a row
			for (int y = 0; y < boardY; y++) //Set Y
			{
				for (int x = 0; x < boardX; x++) //Set X
				{
					if (treatCheck[0][x] == empty)
					{
						//Red horizontally
						if (y == 2 && x > 2 && x < boardX - 1)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x - 1] == playerOne)
							{
								if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty && treatCheck[y + 1][x + 1] == empty && treatCheck[y + 2][x + 1] != empty)
								{
									rngAIChooseSides(chooseSide);

									if (chooseSide == 0)
									{
										rowSelected = x - 2;
										selectColumn = false;
										treatChecking = false;
									}
									else
									{
										rowSelected = x + 1;
										selectColumn = false;
										treatChecking = false;
									}
								}
								else if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty)
								{
									rowSelected = x - 2;
									selectColumn = false;
									treatChecking = false;
								}
								else if (treatCheck[y + 1][x + 1] == empty && treatCheck[y + 2][x + 1] != empty)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Red vertically
						else if (y > 1 && y < boardY - 1 && x == 2)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x - 1] == playerOne)
							{
								if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty && treatCheck[y + 1][x + 1] == empty && treatCheck[y + 2][x + 1] != empty)
								{
									rngAIChooseSides(chooseSide);

									if (chooseSide == 0)
									{
										rowSelected = x - 2;
										selectColumn = false;
										treatChecking = false;
									}
									else
									{
										rowSelected = x + 1;
										selectColumn = false;
										treatChecking = false;
									}
								}
								else if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty)
								{
									rowSelected = x - 2;
									selectColumn = false;
									treatChecking = false;
								}
								else if (treatCheck[y + 1][x + 1] == empty && treatCheck[y + 2][x + 1] != empty)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Green horizontally
						else if (y == boardY - 1 && x > 2 && x < boardX - 1)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x - 1] == playerOne)
							{
								if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty)
								{
									rowSelected = x - 2;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Green vertically
						else if (y > 2 && y < boardY && x == boardX - 1)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x - 1] == playerOne)
							{
								if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty)
								{
									rowSelected = x - 2;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Yellow - row 1
						else if (y > 2 && y < boardY - 2 && x > 2 && x < boardX - 1)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x - 1] == playerOne)
							{
								if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty && treatCheck[y + 1][x + 1] == empty && treatCheck[y + 2][x + 1] != empty)
								{
									rngAIChooseSides(chooseSide);

									if (chooseSide == 0)
									{
										rowSelected = x - 2;
										selectColumn = false;
										treatChecking = false;
									}
									else
									{
										rowSelected = x + 1;
										selectColumn = false;
										treatChecking = false;
									}
								}
								else if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty)
								{
									rowSelected = x - 2;
									selectColumn = false;
									treatChecking = false;
								}
								else if (treatCheck[y + 1][x + 1] == empty && treatCheck[y + 2][x + 1] != empty)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Yellow - row 2
						else if (y > 3 && y < boardY - 1 && x > 2 && x < boardX - 1)
						{
							if (treatCheck[y][x] == playerOne && treatCheck[y - 1][x - 1] == playerOne)
							{
								if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty && treatCheck[y + 1][x + 1] == empty)
								{
									rngAIChooseSides(chooseSide);

									if (chooseSide == 0)
									{
										rowSelected = x - 2;
										selectColumn = false;
										treatChecking = false;
									}
									else
									{
										rowSelected = x + 1;
										selectColumn = false;
										treatChecking = false;
									}

								}
								else if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty)
								{
									rowSelected = x - 2;
									selectColumn = false;
									treatChecking = false;
								}
								else if (treatCheck[y + 1][x + 1] == empty)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
					}
					else {}
				}
			}
			#pragma endregion
		}

		if (treatChecking)
		{
			#pragma region For 2 in a row - AI
			//Horisontally - check for treat of 3 in a row
			for (int y = 0; y < boardY; y++) //Set Y
			{
				for (int x = 0; x < boardX; x++) //Set X
				{
					if (treatCheck[0][x] == empty)
					{
						//Check Y range ABOVE last row
						if (y < boardY - 1)
						{
							if (x < boardX - 1)
							{
								if (treatCheck[y][x] == playerTwo && treatCheck[y][x + 1] == playerTwo)
								{
									if (x == 0)
									{
										if (treatCheck[y][x + 2] == empty && treatCheck[y + 1][x + 2] != empty)
										{
											rowSelected = x + 2;
											selectColumn = false;
											treatChecking = false;
										}
									}
									else if (x == boardX - 2)
									{
										if (treatCheck[y][x - 1] == empty && treatCheck[y + 1][x - 1] != empty)
										{
											rowSelected = x - 1;
											selectColumn = false;
											treatChecking = false;
										}
									}
									else
									{
										if (treatCheck[y][x + 2] == empty && treatCheck[y][x - 1] == empty && treatCheck[y + 1][x + 2] != empty && treatCheck[y + 1][x - 1] != empty)
										{
											rngAIChooseSides(chooseSide);
											if (chooseSide == 0)
											{
												rowSelected = x + 2;
												selectColumn = false;
												treatChecking = false;
											}
											else
											{
												rowSelected = x - 1;
												selectColumn = false;
												treatChecking = false;
											}
										}
										else if (treatCheck[y][x + 2] == empty && treatCheck[y + 1][x + 2] != empty)
										{
											rowSelected = x + 2;
											selectColumn = false;
											treatChecking = false;
										}
										else if (treatCheck[y][x - 1] == empty && treatCheck[y + 1][x - 1] != empty)
										{
											rowSelected = x - 1;
											selectColumn = false;
											treatChecking = false;
										}
									}
								}
							}
						}

						//Check Y range ON last row
						else
						{
							if (x < boardX - 1)
							{
								if (treatCheck[y][x] == playerTwo && treatCheck[y][x + 1] == playerTwo)
								{
									if (x == 0)
									{
										if (treatCheck[y][x + 2] == empty)
										{
											rowSelected = x + 2;
											selectColumn = false;
											treatChecking = false;
										}
									}
									else if (x == boardX - 2)
									{
										if (treatCheck[y][x - 1] == empty)
										{
											rowSelected = x - 1;
											selectColumn = false;
											treatChecking = false;
										}
									}
									else
									{
										if (treatCheck[y][x + 2] == empty && treatCheck[y][x - 1] == empty)
										{
											rngAIChooseSides(chooseSide);
											if (chooseSide == 0)
											{
												rowSelected = x + 2;
												selectColumn = false;
												treatChecking = false;
											}
											else
											{
												rowSelected = x - 1;
												selectColumn = false;
												treatChecking = false;
											}
										}
										else if (treatCheck[y][x + 2] == empty)
										{
											rowSelected = x + 2;
											selectColumn = false;
											treatChecking = false;
										}
										else if (treatCheck[y][x - 1] == empty)
										{
											rowSelected = x - 1;
											selectColumn = false;
											treatChecking = false;
										}
									}
								}
							}
						}
					}
					else {}
				}
			}

			//Vertically - check for treat of 3 in a column
			for (int y = 0; y < boardY; y++) //Set Y
			{
				for (int x = 0; x < boardX; x++) //Set X
				{
					if (treatCheck[0][x] == empty)
					{
						if (y > 1)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x] == playerTwo)
							{
								if (treatCheck[y - 2][x] == empty)
								{
									rowSelected = x;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
					}
					else {}
				}
			}

			//Diagonally -> - check for treat of 3 in a row
			for (int y = 0; y < boardY; y++) //Set Y
			{
				for (int x = 0; x < boardX; x++) //Set X
				{
					if (treatCheck[0][x] == empty)
					{
						//Red horizontally
						if (y == 2 && x > 0 && x < boardX - 3)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x + 1] == playerTwo)
							{
								if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty && treatCheck[y + 1][x - 1] == empty && treatCheck[y + 2][x - 1] != empty)
								{
									rngAIChooseSides(chooseSide);

									if (chooseSide == 0)
									{
										rowSelected = x + 2;
										selectColumn = false;
										treatChecking = false;
									}
									else
									{
										rowSelected = x - 1;
										selectColumn = false;
										treatChecking = false;
									}
								}
								else if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty)
								{
									rowSelected = x + 2;
									selectColumn = false;
									treatChecking = false;
								}
								else if (treatCheck[y + 1][x - 1] == empty && treatCheck[y + 2][x - 1] != empty)
								{
									rowSelected = x - 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Red vertically
						else if (y > 1 && y < boardY - 1 && x == 4)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x + 1] == playerTwo)
							{
								if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty && treatCheck[y + 1][x - 1] == empty && treatCheck[y + 2][x - 1] != empty)
								{
									rngAIChooseSides(chooseSide);

									if (chooseSide == 0)
									{
										rowSelected = x + 2;
										selectColumn = false;
										treatChecking = false;
									}
									else
									{
										rowSelected = x - 1;
										selectColumn = false;
										treatChecking = false;
									}
								}
								else if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty)
								{
									rowSelected = x + 2;
									selectColumn = false;
									treatChecking = false;
								}
								else if (treatCheck[y + 1][x - 1] == empty && treatCheck[y + 2][x - 1] != empty)
								{
									rowSelected = x - 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Green horizontally
						else if (y == boardY - 1 && x > 0 && x < boardX - 3)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x + 1] == playerTwo)
							{
								if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty)
								{
									rowSelected = x + 2;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Green vertically
						else if (y > 2 && y < boardY && x == 0)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x + 1] == playerTwo)
							{
								if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty)
								{
									rowSelected = x + 2;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Yellow - row 1
						else if (y > 2 && y < boardY - 2 && x > 0 && x < boardX - 3)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x + 1] == playerTwo)
							{
								if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty && treatCheck[y + 1][x - 1] == empty && treatCheck[y + 2][x + 1] != empty)
								{
									rngAIChooseSides(chooseSide);

									if (chooseSide == 0)
									{
										rowSelected = x + 2;
										selectColumn = false;
										treatChecking = false;
									}
									else
									{
										rowSelected = x - 1;
										selectColumn = false;
										treatChecking = false;
									}

								}
								else if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty)
								{
									rowSelected = x + 2;
									selectColumn = false;
									treatChecking = false;
								}
								else if (treatCheck[y + 1][x - 1] == empty && treatCheck[y + 2][x - 1] != empty)
								{
									rowSelected = x - 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Yellow - row 2
						else if (y > 3 && y < boardY - 1 && x > 0 && x < boardX - 3)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x + 1] == playerTwo)
							{
								if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty && treatCheck[y + 1][x - 1] == empty)
								{
									rngAIChooseSides(chooseSide);

									if (chooseSide == 0)
									{
										rowSelected = x + 2;
										selectColumn = false;
										treatChecking = false;
									}
									else
									{
										rowSelected = x - 1;
										selectColumn = false;
										treatChecking = false;
									}

								}
								else if (treatCheck[y - 2][x + 2] == empty && treatCheck[y - 1][x + 2] != empty)
								{
									rowSelected = x + 2;
									selectColumn = false;
									treatChecking = false;
								}
								else if (treatCheck[y + 1][x - 1] == empty)
								{
									rowSelected = x - 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
					}
					else {}
				}
			}

			//Diagonally <- - check for treat of 4 in a row
			for (int y = 0; y < boardY; y++) //Set Y
			{
				for (int x = 0; x < boardX; x++) //Set X
				{
					if (treatCheck[0][x] == empty)
					{
						//Red horizontally
						if (y == 2 && x > 2 && x < boardX - 1)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x - 1] == playerTwo)
							{
								if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty && treatCheck[y + 1][x + 1] == empty && treatCheck[y + 2][x + 1] != empty)
								{
									rngAIChooseSides(chooseSide);

									if (chooseSide == 0)
									{
										rowSelected = x - 2;
										selectColumn = false;
										treatChecking = false;
									}
									else
									{
										rowSelected = x + 1;
										selectColumn = false;
										treatChecking = false;
									}
								}
								else if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty)
								{
									rowSelected = x - 2;
									selectColumn = false;
									treatChecking = false;
								}
								else if (treatCheck[y + 1][x + 1] == empty && treatCheck[y + 2][x + 1] != empty)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Red vertically
						else if (y > 1 && y < boardY - 1 && x == 2)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x - 1] == playerTwo)
							{
								if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty && treatCheck[y + 1][x + 1] == empty && treatCheck[y + 2][x + 1] != empty)
								{
									rngAIChooseSides(chooseSide);

									if (chooseSide == 0)
									{
										rowSelected = x - 2;
										selectColumn = false;
										treatChecking = false;
									}
									else
									{
										rowSelected = x + 1;
										selectColumn = false;
										treatChecking = false;
									}
								}
								else if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty)
								{
									rowSelected = x - 2;
									selectColumn = false;
									treatChecking = false;
								}
								else if (treatCheck[y + 1][x + 1] == empty && treatCheck[y + 2][x + 1] != empty)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Green horizontally
						else if (y == boardY - 1 && x > 2 && x < boardX - 1)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x - 1] == playerTwo)
							{
								if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty)
								{
									rowSelected = x - 2;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Green vertically
						else if (y > 2 && y < boardY && x == boardX - 1)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x - 1] == playerTwo)
							{
								if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty)
								{
									rowSelected = x - 2;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Yellow - row 1
						else if (y > 2 && y < boardY - 2 && x > 2 && x < boardX - 1)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x - 1] == playerTwo)
							{
								if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty && treatCheck[y + 1][x + 1] == empty && treatCheck[y + 2][x + 1] != empty)
								{
									rngAIChooseSides(chooseSide);

									if (chooseSide == 0)
									{
										rowSelected = x - 2;
										selectColumn = false;
										treatChecking = false;
									}
									else
									{
										rowSelected = x + 1;
										selectColumn = false;
										treatChecking = false;
									}
								}
								else if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty)
								{
									rowSelected = x - 2;
									selectColumn = false;
									treatChecking = false;
								}
								else if (treatCheck[y + 1][x + 1] == empty && treatCheck[y + 2][x + 1] != empty)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
						//Yellow - row 2
						else if (y > 3 && y < boardY - 1 && x > 2 && x < boardX - 1)
						{
							if (treatCheck[y][x] == playerTwo && treatCheck[y - 1][x - 1] == playerTwo)
							{
								if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty && treatCheck[y + 1][x + 1] == empty)
								{
									rngAIChooseSides(chooseSide);

									if (chooseSide == 0)
									{
										rowSelected = x - 2;
										selectColumn = false;
										treatChecking = false;
									}
									else
									{
										rowSelected = x + 1;
										selectColumn = false;
										treatChecking = false;
									}

								}
								else if (treatCheck[y - 2][x - 2] == empty && treatCheck[y - 1][x - 2] != empty)
								{
									rowSelected = x - 2;
									selectColumn = false;
									treatChecking = false;
								}
								else if (treatCheck[y + 1][x + 1] == empty)
								{
									rowSelected = x + 1;
									selectColumn = false;
									treatChecking = false;
								}
							}
						}
					}
					else {}
				}
			}
			#pragma endregion
		}

		if (treatChecking)
		{
			if (board[5][3] == empty) //If available, place in the middle
			{
				rowSelected = 3;
				selectColumn = false;
				treatChecking = false;
			}
			else //If no of the above triggers, place at random
			{
				int numberMin = 0;
				int numberMax = 6;

				bool run{ true };
				while (run)
				{
					random_device rd;
					mt19937_64 gen(rd());
					uniform_int_distribution<int> RNG(numberMin, numberMax);
					rowSelected = RNG(gen);

					if (board[0][rowSelected] == empty)
					{
						selectColumn = false;
						run = false;
						treatChecking = false;
					}
				}
			}
		}
	}
}

void rngAIChooseSides(int& chooseSide) {

	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<int> RNG(0, 1);
	chooseSide = RNG(gen);
}

void gameFilesReview(vector<vector<char>> board, int boardX, int boardY, char playerOne, char playerTwo, string playerOneName, string playerTwoName, int games, string gamesString) {

	ofstream gameRounds("GameRounds\\Review - " + playerOneName + " vs. " + playerTwoName + " (" + gamesString + ")" + ".txt", ios::in | ios::app | ios::out);

	gameRounds << setw(2) << " ";
	for (size_t j = 0; j < boardX; j++)
		gameRounds << setw(2) << "__";
	gameRounds << setw(2) << "_ " << endl;

	//Set the rest of the board 
	for (size_t i = 0; i < boardY; i++)
	{
		gameRounds << setw(2) << "|";
		for (size_t j = 0; j < boardX; j++)
		{
			if (board[i][j] == playerOne)
				gameRounds << setw(2) << board[i][j] << termcolor::reset;
			else if (board[i][j] == playerTwo)
				gameRounds << setw(2) << board[i][j] << termcolor::reset;
			else
				gameRounds << setw(2) << board[i][j];
		}
		gameRounds << setw(2) << "|" << endl;
	}

	//Set last row
	gameRounds << setw(2) << "|";
	for (size_t j = 0; j < boardX; j++)
		gameRounds << setw(2) << "--";
	gameRounds << setw(2) << "-|" << endl << endl;

	gameRounds << "-------------------" << endl << endl;
	gameRounds.close();
}

void gameFilesResult(vector<vector<char>> board, int boardX, int boardY, char playerOne, char playerTwo, string playerOneName, string playerTwoName, int games, string gamesString) {
	
	ofstream gameResults("GameResults\\Results.txt", ios::in | ios::app | ios::out);

	gameResults << playerOneName << " (" << playerOne << ")" << endl;
	gameResults << playerTwoName << " (" << playerTwo << ")" << endl;

	gameResults << setw(2) << " ";
	for (size_t j = 0; j < boardX; j++)
		gameResults << setw(2) << "__";
	gameResults << setw(2) << "_ " << endl;

	//Set the rest of the board 
	for (size_t i = 0; i < boardY; i++)
	{
		gameResults << setw(2) << "|";
		for (size_t j = 0; j < boardX; j++)
		{
			if (board[i][j] == playerOne)
				gameResults << setw(2) << board[i][j] << termcolor::reset;
			else if (board[i][j] == playerTwo)
				gameResults << setw(2) << board[i][j] << termcolor::reset;
			else
				gameResults << setw(2) << board[i][j];
		}
		gameResults << setw(2) << "|" << endl;
	}

	//Set last row
	gameResults << setw(2) << "|";
	for (size_t j = 0; j < boardX; j++)
		gameResults << setw(2) << "--";
	gameResults << setw(2) << "-|" << endl << endl;

	gameResults << "-------------------" << endl << endl;
	gameResults.close();
}
