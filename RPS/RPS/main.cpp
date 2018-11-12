#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
using namespace std;

//Made by Sebastian Nienajadlo
//Rock paper scissors with file saving and password login system

int CPUGame(string playerName, string password, int tWins, int tLoses, int tTies);
string Login(string playerName, string password, bool loggedIn);

int main(void)
{
	string playerName;
	string password = ""; // for the login system
	bool loggedIn = false;
	int tWins = 0, tLoses = 0, tTies = 0; //total wins to save to files
	ifstream inFile;

	do
	{
		bool pickName = true;
		while (pickName)    // Loops until the user picks a name that is more than 8 characters
		{
			cout << "Please enter a Username [min 8 characters]: ";
			cin >> playerName;
			if (playerName.length() >= 8) // When the players name is 8 or more characters long
			{
				inFile.open("C:\\Temp\\" + playerName + ".txt"); //Opens a file with the players name
				inFile >> password;
				inFile >> tWins;  //takes in the wins, loses, and ties
				inFile >> tLoses;
				inFile >> tTies;
				inFile.close();

				password = Login(playerName, password, loggedIn); // Runs the login function (for bonus marks I hope)
				if (password != "")
				{
					loggedIn = true;
					ofstream outFile;
					outFile.open("C:\\Temp\\" + playerName + ".txt"); // Updates the user stats and adds them to the file
					outFile << password << endl;
					outFile << tWins << endl;
					outFile << tLoses << endl;
					outFile << tTies << endl;
					outFile.close();
					pickName = false;
				}
			}
			else
			{
				cout << "Username too short: " << playerName.length() << endl;
			}
		}
		cout << "Welcome to the Rock Paper Scissors game " << playerName << "!" << endl;
		cout << "Your current Wins: " << tWins << " Loses: " << tLoses << " and Ties: " << tTies << "\n" << endl;

		bool playAgain = true;
		while (playAgain)
		{
			cout << "What would you like to do? \n1. Play \n2. Change User\n3. Exit" << endl;
			string choice; // This is a string so you can't break the system with a not int input ;) ;) ;)
			cin >> choice;

			if (choice == "1")
			{
				//Player vs CPU
				CPUGame(playerName, password, tWins, tLoses, tTies);
			}
			else if (choice == "2")
			{
				cout << "You are logging out of " << playerName << endl;
				playAgain = false;
			}
			else if (choice == "3")
			{
				// quits game
				cout << "CYA!" << endl;
				playAgain = false;
				loggedIn = false;
			}
			else
			{
				cout << "That is an invalid choice!" << endl;
			}
		}
	} while (loggedIn);

	//This tells the player their score at the end of the game
	inFile.open("C:\\Temp\\" + playerName + ".txt");
	inFile >> password;
	inFile >> tWins;
	inFile >> tLoses;
	inFile >> tTies;
	inFile.close();
	cout << "Your final Wins: " << tWins << " Loses: " << tLoses << " Ties: " << tTies << endl;

	system("pause");
	return 0;
}

int CPUGame(string playerName, string password, int tWins, int tLoses, int tTies)
{
	ifstream inFile;
	string playerChoiceString;
	bool keepPlaying = true;
	int playerChoice;
	int cpuChoice;
	int rounds = 0, wins = 0, loses = 0, ties = 0;
	int roundCount;


	inFile.open("C:\\Temp\\" + playerName + ".txt"); //Opens a file with the players name
	inFile >> password;
	inFile >> tWins;  //takes in the wins, loses, and ties
	inFile >> tLoses;
	inFile >> tTies;
	inFile.close();

	// This lets the player choose how many rounds to fight against the CPU
	cout << "Choose your rounds player!\n1. 5 rounds\n2. 10 rounds\n3. 15 rounds" << endl;
	cin >> playerChoiceString;

	if (playerChoiceString == "1")      roundCount = 5;
	else if (playerChoiceString == "2") roundCount = 10;
	else if (playerChoiceString == "3") roundCount = 15;
	else roundCount = 5;
	cout << "You will play for " << roundCount << " rounds!" << endl;

	while (keepPlaying)
	{
		cout << "Choose your fighter " << playerName << "! \n1. Rock \n2. Paper \n3. Scissors\n";
		cin >> playerChoiceString; // Using a string instead of an int so the loop doesn't break ;) ;) ;)

		// Sets the playerChoice according to the string so that the comparisons don't break either ;) ;) ;)
		if (playerChoiceString == "1")      playerChoice = 1;
		else if (playerChoiceString == "2") playerChoice = 2;
		else if (playerChoiceString == "3") playerChoice = 3;
		else playerChoice = 0; // This sets it to 0 so that the randomize a few lines under won't break ;)

		srand((unsigned)time(0));
		if (playerChoice == 0) //If the user picks something other than 1, 2 or 3 it will choose for them
		{
			playerChoice = rand() % 3 + 1;
			cout << "Choice invalid! Randomizing pick!" << endl;
		}

		cpuChoice = rand() % 3 + 1; // cpu randomizer
		cpuChoice = rand() % 3 + 1; // I do it twice because sometimes it just takes the same number 5 times in a row

		string cpuChoiceString;
		//says what the cpu chose in string form rather than int form
		if (cpuChoice == 1) cpuChoiceString = "Rock";
		if (cpuChoice == 2) cpuChoiceString = "Paper";
		if (cpuChoice == 3) cpuChoiceString = "Scissors";
		cout << "The CPU chose " << cpuChoiceString << "!" << endl;

		//says what the player chose in string form
		if (playerChoice == 1) playerChoiceString = "Rock";
		if (playerChoice == 2) playerChoiceString = "Paper";
		if (playerChoice == 3) playerChoiceString = "Scissors";
		cout << "The Player chose " << playerChoiceString << "!" << endl; //reusing playerChoiceString because I can

		// 1 Rock, 2 Paper, 3 Scissors
		int winner; // 0 tie, 1 player, 2 CPU
		if (playerChoice == 1 && cpuChoice == 2) winner = 2; // rock vs paper = lose
		if (playerChoice == 1 && cpuChoice == 3) winner = 1; // rock vs scissors = win
		if (playerChoice == 2 && cpuChoice == 1) winner = 1; // etc.
		if (playerChoice == 2 && cpuChoice == 3) winner = 2; //
		if (playerChoice == 3 && cpuChoice == 1) winner = 2; //
		if (playerChoice == 3 && cpuChoice == 2) winner = 1; //
		if (playerChoice == cpuChoice)           winner = 0; // rock vs rock = tie, etc.

		switch (winner) // outputs the winner of that round
		{
		case (0):
			cout << "It was a tie!!!\n" << endl;
			ties++;
			break;
		case(1):
			cout << playerName << " has won a round against the CPU!\n" << endl;
			wins++;
			break;
		case(2):
			cout << "CPU has won a round against " << playerName << "!\n" << endl;
			loses++;
			break;
		}

		++rounds; // Keeps counting rounds until the user chosen rounds have been played
		if (roundCount == rounds)
		{
			keepPlaying = false;
		}
	}//end of while

	cout << "\nWins: " << wins << " \nLoses: " << loses << " \nTies: " << ties << endl;
	if (wins > loses)
	{
		cout << playerName << " beat the CPU in " << rounds << " rounds!\nCongratulations!\n\n" << endl;
		++tWins;
	}
	if (wins < loses)
	{
		cout << "The CPU beat " << playerName << " in " << rounds << " rounds!\nThat's Unfortunate!\n\n" << endl;
		++tLoses;
	}
	if (wins == loses)
	{
		cout << playerName << " tied with the CPU in " << rounds << " rounds!\nWow that was close!\n\n" << endl;
		++tTies;
	}

	ofstream outFile;
	outFile.open("C:\\Temp\\" + playerName + ".txt"); // Updates the user stats and adds them to the file
	outFile << password << endl;
	outFile << tWins << endl;
	outFile << tLoses << endl;
	outFile << tTies << endl;
	outFile.close();

	return 0;
}

string Login(string playerName, string password, bool loggedIn)
{
	string checkPassword; // This one is player entered that compares the file one

	bool validPassword = false;
	while (!validPassword)
	{
		if (password == "") // When making a new user the file will have blank spots that this checks for at the start.
		{
			cout << "Please make a password [min 8 characters]: ";
			cin >> password;

			if (password.length() >= 8)
			{
				cout << "You have logged into " << playerName << "!\n" << endl;
				validPassword = true;
				loggedIn = true;
			}
			else
			{
				cout << "That password is too short!\n" << endl;
			}
		}
		else // This runs if the file isn't new and already contains a password
		{
			cout << "Please enter your password: ";
			cin >> checkPassword;

			if (checkPassword == password)
			{
				cout << "You have logged into " << playerName << "!\n" << endl;
				validPassword = true;
				loggedIn = true;
			}
			else
			{
				cout << "That is the wrong password!\n" << endl;
			}
		}
	}

	return password;
}