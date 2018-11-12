#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

int* Stats(string name, int stats[]);
int Level(string name, int stats[]);
string Login(string name, string password, int stats[]);
int LoginCheck(string name, int check);
int ChooseClass(string name,  int stats[]);


int main(void)
{
	ofstream outFile;
	ifstream inFile;
	string name, password = "";
	bool loggedIn = false;
	int stats[6] = {0, 0, 0, 0, 0, 0};
	cout << "- Welcome to the Text RPG\n- You can do 'help' for a list of commands\n- You can type any command at any point" << endl;

	bool gameLoop = true;
	while (gameLoop)
	{
		cout << "> ";

		string input;
		cin >> input;
		if (input == "login")
		{
			if (loggedIn)
			{
				LoginCheck(name, 0);
			}
			else
			{
				name = Login(name, password, stats);
				loggedIn = true;
			}
		}
		else if (input == "logout")
		{
			if (!loggedIn)
			{
				LoginCheck(name, 1);
			}
			else
			{
				LoginCheck(name, 2);
				name = "";
				password = "";
				loggedIn = false; 
			}
		}
		else if (input == "stats")
		{
			if (!loggedIn)
				LoginCheck(name, 1);
			else
			{
				system("CLS");
				cout << "\n----------Stats----------\n- Attack:  " << Stats(name, stats)[0] << "\n- Defense: " << Stats(name, stats)[1] << "\n- Health:  " << Stats(name, stats)[2] << "\n- Mana:    " << Stats(name, stats)[3] << "\n- Exp:     " << Stats(name, stats)[4] << "\n- Level:  " << Stats(name, stats)[5] << "\n----------Stats----------\n" << endl;
			}
		}
		else if (input == "class")
		{
			if (!loggedIn)
				LoginCheck(name, 1);
			else
			{
				system("CLS");
				ChooseClass(name, stats);
			}
		}
		else if (input == "level")
		{
			if (!loggedIn)
				LoginCheck(name, 1);
			else
			{
				Level(name, stats);
			}
		}
		else if (input == "shop")
		{
			if (!loggedIn)
				LoginCheck(name, 1);
			else
			{
				system("CLS");
				cout << "----------Shop----------\n\n\n- Shop is under construction\n\n\n----------Shop----------\n" << endl;
			}

		}
		else if (input == "quit")
		{
			gameLoop = false;
			cout << "- See you later!" << endl;
		}
		else if (input == "help")
		{
			system("CLS");
			cout << "\n----------Help----------\n- 'login' to login to an account\n- 'logout' to logout of your current account\n- 'class' to choose your class\n- 'stats' will show your stats\n- 'quit' to quit the game\n----------Help----------\n" << endl;
		}
		else
		{
			cout << "! Invalid command !" << endl;
		}
	}
	system("pause");
	return 0;
}

int* Stats(string name, int stats[]) // Function is used for checking a users stats from file
{
	//DEBUG
	//cout << "|name " << name << "|" << endl;

	ifstream inFile;
	inFile.open("Data\\Stats\\" + name + ".txt");
	for (int i = 0; i < 6; i++)
	{
		inFile >> stats[i];
		if (stats[i] < 0)
		{
			stats[i] = 0;
			//DEBUG this is for testing what the value is inside the user file
			//cout << stats[i] << " is less than 0" << endl;
		}
	}
	inFile.close();
	//DEBUG shows the stats of the player
	//cout << stats[0] << " " << stats[1] << " " << stats[2] << " " << stats[3] << " " << stats[4] << endl;
	
	return stats;
}

int Level(string name, int stats[]) // This will determine the player level based on exp
{
	ifstream inFile;
	ofstream outFile;
	int level = 1;
	int exp = stats[4];
	double temp = 0;
	double control;
	double number = 0;

	//DEBUG
	cout << "----------Level Up----------" << endl;
	//cout << "- Exp: " << exp << endl;

	//Algorithm determines level from exp
	
	//player needs 47 exp to get to level 2
	exp = 100000;
	for (int i = 0; i < level; i++)
	{
		control = (level * 1.3) + 30;
		number = exp;
		exp -= control * level;
		number -= exp;
		cout << "Number: " << number << " Exp: " << exp << " Control: " << control << " Level: " << level << endl;

		if (exp >= number)
		{
			cout << "Level up!" << endl;
			++level;
		}
		else
		{
			cout << "Can't level up any more!" << endl;
			break;
		}
	}

	return level;
}

string Login(string name, string password, int stats[])
{
	ifstream inFile;
	ofstream outFile;
	//Separator
	system("CLS");
	cout << "\n----------Login----------\n";
	password = ""; // Resets password because of some weird bugs
	
	bool validName = false;
	while (!validName)
	{
		cout << "= Enter your username: ";
		cin >> name;
		if (name.length() >= 8)
		{
			validName = true;
		}
		else
		{
			cout << "! Username must be at least 8 characters long !" << endl;
		}
	}

	inFile.open("Data\\Passwords\\" + name + ".txt");
	inFile >> password;
	inFile.close();

	if (password == "")
	{
		bool passRight = false;
		while (!passRight)
		{
			cout << "- This account doesn't exist\n- Would you like to make a password for it?\n= 'Y' | 'N'" << endl;
			string choice;
			cin >> choice;
			if (!(choice == "Y" || choice == "y"))
			{
				passRight = true;
			}
			else
			{
				cout << "= Please make a password: ";
				cin >> password;
				outFile.open("Data\\Passwords\\" + name + ".txt");
				outFile << password;
				outFile.close();

				if (password.length() >= 8)
				{
					passRight = true;
					cout << "+ You logged in succesfully +" << endl;
				}
				else
				{
					cout << "! Passwords must 8 characters or more !" << endl;
				}
			}
		}
	}
	else
	{
		bool passRight = false;
		while (!passRight)
		{
			cout << "= Enter your password: ";
			cin >> password;
			string tempPass;
			inFile.open("Data\\Passwords\\" + name + ".txt");
			inFile >> tempPass;
			inFile.close();
			if (tempPass == password)
			{
				passRight = true;
				cout << "+ You logged in succesfully +" << endl;
			}
			else
			{
				cout << "! Password incorrect! Please try again !" << endl;
			}
		}
	}

	outFile.open("Data\\Stats\\" + name + ".txt");
	outFile << Stats(name, stats)[0] << endl << Stats(name, stats)[1] << endl << Stats(name, stats)[2] << endl << Stats(name, stats)[3] << endl << Stats(name, stats)[4] << endl;
	outFile.close();
	//DEBUG shows the stats of the player
	//cout << stats[0] << " " << stats[1] << " " << stats[2] << " " << stats[3] << " " << stats[4] << " " << stats[5] << endl;

	//End Separator
	cout << "----------Login----------\n\n";

	return name;
}

int LoginCheck(string name, int check)
{
	// 0 Already logged in, 1 You need to login, 2 You logged out
	switch (check)
	{
	case (0):
		cout << "! You are already logged in as [" << name << "] !" << endl;
		break;
	case (1):
		cout << "! You must login to use this command !" << endl;
		break;
	case (2):
		cout << "! You have logged out !" << endl;
		break;
	}
	return true;
}

int ChooseClass(string name, int stats[])
{
	ifstream inFile;
	ofstream outFile;
	string playerClass = "";

	inFile.open("Data\\Class\\" + name + ".txt");
	inFile >> playerClass;
	inFile.close();

	if (playerClass != "")
	{
		cout << "! Class already chosen [" << playerClass << "] !" << endl;
	}
	else
	{
		bool secureChoice = true;
		while (secureChoice)
		{
			bool validClass = false;
			while (!validClass)
			{
				cout << "- Choose your class!\n= 1 Mage\n= 2 Warrior\n= 3 Rogue" << endl;
				cin >> playerClass;

				if (playerClass == "1")
				{
					validClass = true;
					playerClass = "Mage";
				}
				else if (playerClass == "2")
				{
					validClass = true;
					playerClass = "Warrior";
				}
				else if (playerClass == "3")
				{
					validClass = true;
					playerClass = "Rogue";
				}
				else
				{
					cout << "! That is not a valid class !" << endl;
				}
			}

			cout << "= Are you certain of your choice 'Y' | 'N': ";
			string choice;
			cin >> choice;

			if (choice == "y" || choice == "Y")
			{
				secureChoice = false;
			}
			else
			{
				cout << "- Pick another class then" << endl;
			}
		}

		cout << "+ You have chosen " << playerClass << " as your class +" << endl;

		if (playerClass == "Mage")
		{
			stats[0] = 15;
			stats[1] = 10;
			stats[2] = 13;
			stats[3] = 20;
			stats[4] = 0;
			stats[5] = 1;
		}
		if (playerClass == "Warrior")
		{
			stats[0] = 12;
			stats[1] = 15;
			stats[2] = 20;
			stats[3] = 8;
			stats[4] = 0;
			stats[5] = 1;
		}
		if (playerClass == "Rogue")
		{
			stats[0] = 18;
			stats[1] = 8;
			stats[2] = 15;
			stats[3] = 12;
			stats[4] = 0;
			stats[5] = 1;
		}

		outFile.open("Data\\Class\\" + name + ".txt");
		outFile << playerClass;
		outFile.close();

		outFile.open("Data\\Stats\\" + name + ".txt");
		outFile << stats[0] << endl << stats[1] << endl << stats[2] << endl << stats[3] << endl << stats[4] << endl;
		outFile.close();
	}

	//resets stats to 0 so the stats command doesn't read previous use stats
	stats[0] = 0;
	stats[1] = 0;
	stats[2] = 0;
	stats[3] = 0;
	stats[4] = 0;
	stats[5] = 1; // This is the level and everyone starts at level 1 not level 0

	return 0;
}