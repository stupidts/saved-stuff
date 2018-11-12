#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctime>
#include "Classes.h"
#define ABIL_MAX 6
#define ABIL_PLR 4
using namespace std;

/* User-defined function definitions. */
bool BuildAbilities(Ability* a) /* Passing in array by address/pointer. */
{
	ifstream inFile;
	inFile.open("Abilities.txt");
	if (inFile.is_open())
	{
		int numLines;
		inFile >> numLines; /* Here is a clue to how we're going to make the array dynamic later. */
		for (int i = 0; i < numLines; i++)
		{
			inFile >> a[i].name >> a[i].damage >> a[i].critChance >> a[i].autohit >> a[i].cooldown
				>> a[i].currEff[0] >> a[i].currEff[1] >> a[i].currEff[2] >> a[i].currEff[3]
				>> a[i].nextEff[0] >> a[i].nextEff[1] >> a[i].nextEff[2] >> a[i].nextEff[3];
		}
		inFile.close();
		a[0].selected = true; /* Set 'Punch' as selected for default printing. */
		return 0; /* We're okay. I'm maintaining a return of 0 to mean good. */
	}			  /* We're going to change the return type to a pointer later for the dynamic conversion. */
	else
		return 1; /* We couldn't open the file. */
}

void PrintAbilities(Ability* a, int sz) /* I'm using the same print function for pre-game and during game. */
{
	cout << endl << setw(79) << "Curr Round Effect    Next Round Effect" << endl;
	cout << "##  Ability Name  Dmg  Crit%  Auto  CD  Atk  Def  Dmg  Hlth  Atk  Def  Dmg  Hlth" << endl;
	for (int i = 0; i < sz; i++)
	{
		cout << setw(2) << i << setw(14) << a[i].name << (a[i].selected ? '*' : ' ') << setw(4) << a[i].damage << setw(7)
			<< a[i].critChance << setw(6) << (a[i].autohit == 0 ? "No" : "Yes") << setw(4) << a[i].cooldown << setw(5)
			<< a[i].currEff[0] << setw(5) << a[i].currEff[1] << setw(5) << a[i].currEff[2] << setw(6) << a[i].currEff[3]
			<< setw(5) << a[i].nextEff[0] << setw(5) << a[i].nextEff[1] << setw(5) << a[i].nextEff[2] << setw(6)
			<< a[i].nextEff[3] << endl;
	}
}

void BuildPlayer(Player& p, Ability* a) /* Takes a reference to the player to be built and a pointer the array.
										holding all six abilities that can be chosen from. */
{
	char name[24];
	short ctr, opt;
	char optC;

	while (true)
	{
		cout << p.GetName() << ", enter your name: ";
		cin.getline(name, 24); /* Essentially limits the character's name to 24 chars including spaces. */
		if (cin.fail()) /* Stream can fail if the number of characters exceeds 24. */
		{
			cin.clear(); /* In that case, we clear the error state. */
			cin.ignore(INT_MAX, '\n'); /* And ignore what's left in the buffer. */
		}
		cout << "Okay, you are " << name << '.' << endl;
		for (int i = 1; i < ABIL_MAX; i++) /* Resets the displayed selected abilities. */
			a[i].selected = false;
		ctr = 0;
		while (ctr < 3) /* I wanted to show you a rare counter-controlled while loop. */
		{
			PrintAbilities(a, ABIL_MAX);
			cout << "(* - Indicates ability owned)\n" << endl;
			cout << "Enter ability number to take " << "(" << 3 - ctr << " choice" << (ctr < 2 ? "s " : " ") << "left): ";
			cin >> optC;
			cin.ignore(INT_MAX, '\n');
			opt = optC - 48;
			if (opt >= 0 && opt < ABIL_MAX)
			{
				if (a[opt].selected)
					cout << "You already have that ability, try again..." << endl;
				else
				{
					cout << "Okay, " << a[opt].name << " selected!" << endl;
					a[opt].selected = true;
					ctr++; /* We're good, so increment counter of loop. */
				}
			}
			else
				cout << "Invalid ability number, try again..." << endl;
			/* Note we didn't increment counter. How can we rewrite this loop as a for loop? */
		}
		PrintAbilities(a, ABIL_MAX);
		while (true)
		{
			cout << "\nOkay " << name << ", are you happy with your character? [y/n]: ";
			cin >> optC;
			cin.ignore(INT_MAX, '\n');
			if (optC == 'y' || optC == 'Y')
			{
				p.SetName(name); /* Passing the C-String name to the string type name member. */
				ctr = 0;
				for (int i = 0; i < ABIL_MAX; i++)
					if (a[i].selected)
						p.SetAbility(a[i], ctr++);
				return;
			}
			else if (optC == 'n' || optC == 'N')
			{
				cout << "\nAlright, let's start over then!" << endl;
				break;
			}
			else
				cout << "Invalid input, try again..." << endl;
		}
	}
}

/* Start of main function. */
int main()
{
	Ability abilityArray[ABIL_MAX]; /* The fixed-size array that will store all six abilities. Fixed-size arrays are not
									ideal. I made this intentionally bad for a future dynamic conversion exercise. */
	Player players[2]; /* Player object array. Again done in a non-dynamic way. */
	bool gameOver = false;
	short currPlayer; /* Keeps track of current player and is also used as a simple index for the players array. */

	srand((unsigned)time(NULL));
	if (BuildAbilities(abilityArray) == 1)
		return 1;
	players[0].SetName("Player 1"); /* I left this for you to show how we call a member function of an object. */
	BuildPlayer(players[0], abilityArray);
	players[1].SetName("Player 2");
	BuildPlayer(players[1], abilityArray);
	currPlayer = rand() % 2;
	cout << '\n' << players[currPlayer].GetName() << " wins the coin toss and goes first!" << endl;
	while (!gameOver)
	{
		cout << "It is " << players[currPlayer].GetName() << "'s turn!" << endl;
		PrintAbilities(players[currPlayer].GetAbilities(), ABIL_PLR);
		cout << "(* - Indicates ability not on cooldown)\n" << endl;
		gameOver = players[currPlayer].DoAttack(currPlayer == 0 ? players[1] : players[0]); /* Calling attack function of current player. Can you figure this out? */
		if (gameOver == false)
			currentPlayer = (currentPlayer == 1 ? 0 : 1);
	}
	cout << "The game is over! " << players[currPlayer].GetName() << " wins!" << endl;
	system("pause");
	return 0;
}