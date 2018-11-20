#include <iostream>
#include <fstream>
#include <string>
#include <conio.h> // Sorry non-Windows users. 
#include "Classes.h"
using namespace std;
#define ROWS 24
#define COLS 32

/* Important note: x coordinate is player's COLUMN position and
   y coordinate is player's ROW position. Don't mix these up! */

bool BuildMap(Level& l, const char* n) // Passing 2D array to function.
{
	cout << "BuildMap(); " << n << endl;
	ifstream inFile(n);
	if (inFile.is_open())
	{
		char temp;
		for (int row = 0; row < ROWS; row++)
		{
			for (int col = 0; col < COLS; col++)
			{
				inFile >> temp;
				l.map[row][col].SetBGTile(temp);
			}
		}
		inFile.close();
		return 0;
	}
	return 1;
}

void PrintMap(Level& l, const Player& p)
{
	bool isDoor = false;

	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			for (int i = 0; i < l.m_iNumDoors; i++)
			{
				if (row == l.doors[i].m_y && col == l.doors[i].m_x)
				{
					isDoor = true;
				}
			}
			if (isDoor)
				cout << 'D';
			else if (row == p.m_y && col == p.m_x)
				cout << p.m_cOutput;
			else
				cout << l.map[row][col].m_cOutput;
		}
		cout << endl;
	}
}

void CheckDoors(int cl, Player& p, Level& l)
{
	cout << "\n\n\nm_iNumDoors " + to_string(l.m_iNumDoors) << endl;
	for (int i = 0; i < l.m_iNumDoors; i++)
	{
		if (l.doors != 0)
		{
			l.doors[i].GetDoor(cl, p.m_x, p.m_y);
			cout << "cl:" << to_string(cl) << ", p.m_x:" << to_string(p.m_x) << ", p.m_y:" << to_string(p.m_y) << endl;
		}
		else
			cout << "\n\n\nSomething went wrong" << endl;
	}
}

int main()
{
	bool quit = false;
	Level levels[5];
	char input;
	Player player(COLS / 2, ROWS / 2);
	int currLevel(0);

	if (BuildMap(levels[0], "Level1.txt") == 1)
	{
		return 1;
	}

	while (!quit)
	{
		PrintMap(levels[currLevel], player);
		input = _getch();
		switch (input)
		{
		case 'w':  // Up.
		case 'W':
			if (player.m_y > 0 && !levels[currLevel].map[player.m_y - 1][player.m_x].m_bIsObstacle)
				player.m_y--;
			break;
		case 's': // Down.
		case 'S':
			if (player.m_y < ROWS - 1 && !levels[currLevel].map[player.m_y + 1][player.m_x].m_bIsObstacle)
				player.m_y++;
			break;
		case 'a': // Left.
		case 'A':
			if (player.m_x > 0 && !levels[currLevel].map[player.m_y][player.m_x - 1].m_bIsObstacle)
				player.m_x--;
			break;
		case 'd': // Right.
		case 'D':
			if (player.m_x < COLS - 1 && !levels[currLevel].map[player.m_y][player.m_x + 1].m_bIsObstacle)
				player.m_x++;
			break;
		case 'q':
		case 'Q':
			quit = true;
			break;
		}
		system("cls");
		if (levels[currLevel].map[player.m_y][player.m_x].m_bIsHazard)
		{
			quit = true;
			system("cls");
			cout << "\n\n\n\n\n\n\n\nYou died!\n\n\n\n\n\n\n\n" << endl;
		}
		if (levels[currLevel].map[player.m_y][player.m_x].m_cOutput == 'D')
		{
			cout << "\n\n\non a door!" << endl;
			CheckDoors(currLevel, player, *levels);
			cout << "\n\n\ncurr: " << currLevel << ", px: " << player.m_x << ", py:" << player.m_y << endl;
			if (currLevel == 0)
			{
				cout << "cl 0" << endl;
				levels[0].AddDoor(14, 20, 2, 17, 14);
				BuildMap(*levels, "Level1.txt");
			}
			if (currLevel == 1)
			{
				cout << "cl 1" << endl;
				levels[1].AddDoor(17, 14, 1, 14, 20);
				levels[1].AddDoor(27, 15, 3, 17, 14);
				levels[1].AddDoor(10, 6, 4, 27, 11);
				BuildMap(*levels, "Level2.txt");
			}
			if (currLevel == 2)
			{
				cout << "cl 2" << endl;
				levels[2].AddDoor(17, 14, 2, 27, 15);
				BuildMap(*levels, "Level3.txt");
			}
			if (currLevel == 3)
			{
				cout << "cl 3" << endl;
				levels[3].AddDoor(27, 11, 2, 10, 6);
				BuildMap(*levels, "Level4.txt");
			}
		}
	}
	system("pause");
	return 0;
}