//Made by: Sebastian Nienajadlo
#include <iostream>
#include <ctime>
#include <string>
using namespace std;

bool guessing = true; // This is true because we want the while loop to 
int player;       // This is defining the number used on line 22
int numberToGuess, guess, player1Count = 0, player2Count = 0; //sets variables for all the numbers needed
string player1Name = " ", player2Name = " "; // Player names stored in strings


int main(void)
{
	cout << "Welcome players to the guessing game!\nPlease enter your names(No spaces)" << endl;
	cout << "[Player 1], please enter your name: "; // Player enters name
	cin >> player1Name;                             // Name gets stored
	cout << "[Player 2], please enter your name: "; // Player enters name
	cin >> player2Name;                             // Name gets stored

	srand((unsigned)time(NULL)); // Initiates the random function (I think)
	player = rand() % 2 + 1;     // Chooses who goes first
	
	numberToGuess = rand() % 100 + 1; // Chooses the number to guess
	while (guessing) // Loop runs the guessing game until someone gets a right answer
	{
		cout << (player == 1 ? player1Name : player2Name) << ", please enter a guess: ";
		cin >> guess;
		(player == 1 ? player1Count : player2Count)++;
		if (guess == numberToGuess)
		{
			cout << (player == 1 ? player1Name : player2Name) << " has guessed the number " << numberToGuess << " correctly in " << (player == 1 ? player1Count : player2Count) << " guesses!";
			break;
		}
		if (guess > numberToGuess) cout << "Your number is too high." << endl;
		else if (guess < numberToGuess) cout << "Your number is too low." << endl;
		player = (player == 1 ? 2 : 1);

	}
	system("pause"); // Exits the code
	return 0;
}