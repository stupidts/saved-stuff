#include <iostream>
using namespace std;


void printBoard(char* b)
{
	cout << endl << (b[0] == '.' ? '0' : b[0]) << '|' << (b[1] == '.' ? '1' : b[1]) << '|' << (b[2] == '.' ? '2' : b[2]) << endl;
	cout << "-----" << endl;
	cout << (b[3] == '.' ? '3' : b[3]) << '|' << (b[4] == '.' ? '4' : b[4]) << '|' << (b[5] == '.' ? '5' : b[5]) << endl;
	cout << "-----" << endl;
	cout << (b[6] == '.' ? '6' : b[6]) << '|' << (b[7] == '.' ? '7' : b[7]) << '|' << (b[8] == '.' ? '8' : b[8]) << endl << endl;
}

int main(void)
{
	bool newGame = true, gameOn = true, validInput;
	int boardIndex, playerIndex = 0;
	char choice;
	char pieces[2] = { 'O','X' };
	char board[9];

	while (newGame)
	{
		for (int i = 0; i < 9; i++)
		{
			board[i] = '.';
		}
		while (gameOn)
		{
			validInput = false;
			while (validInput == false)
			{
				printBoard(board);
				cout << pieces[playerIndex] << "s turn. Enter a number to fill that space:";
				cin >> boardIndex;
				if (board[boardIndex] == '.')
				{
					board[boardIndex] = pieces[playerIndex];
					validInput = true;
				}
				else
				{
					cout << "That spot is taken" << endl;
				}
			}
			printBoard(board);
			cout << "press c to continue or press q to quit." << endl;
			cin >> choice;
			if (choice == 'q' || choice == 'Q')
			{
				gameOn = false;
			}
			if (playerIndex == 0)
				playerIndex = 1;
			else
				playerIndex = 0;
		}
		cout << "Do you want to play again? 'y' or 'n':";
		cin >> choice;
		if (choice == 'n' || choice == 'N')
		{
			newGame = false;
		}
		else
		{
			newGame = true;
		}
	}
	system("pause");
	return 0;
}