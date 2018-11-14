#include <iostream>
#include <fstream>
#include <conio.h> // Sorry non-Windows users. 
#include "Classes.h"
using namespace std;
#define ROWS 24
#define COLS 32



bool BuildMap(BGTile m[][COLS]) // Passing 2D array to function.
{
	ifstream inFile("Level1.txt");
	char temp;
	if (inFile.is_open())
	{
		for (int row = 0; row < ROWS; row++)
		{
			for (int col = 0; col < COLS; col++)
			{
				inFile >> temp;
				m[row][col].m_cOutput = temp;
				if (temp == 'M' || temp == 'm' || temp == '#')
				{
					m[row][col].m_bIsObstacle = true;
				}
				else if (temp == 'X')
				{
					m[row][col].m_bIsHazard = true;
				}

				if (m[row][col].m_cOutput == '*')
					m[row][col].m_cOutput = ' ';
			}
		}
		return 0;
	}
	return 1;
}

void PrintMap(BGTile m[][COLS], Player& p)
{
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			if (row == p.m_y && col == p.m_x)
				cout << "@";
			else
				cout << m[row][col].m_cOutput;
		}
		cout << endl;
	}
}

int main()
{
	bool quit = false;
	BGTile map[ROWS][COLS]; // 2D array of characters.
	char input;
	Player player(COLS / 2, ROWS / 2);

	if (BuildMap(map) == 1)
		return 1;
	while (!quit)
	{
		PrintMap(map, player);
		input = _getch();
		switch (input)
		{
		case 'w':  // Up.
		case 'W':
			if (player.m_y > 0 && !map[player.m_y - 1][player.m_x].m_bIsObstacle) // How can we add to these checks to account for the '#' obstacles?
				player.m_y--;
			else if (map[player.m_y - 1][player.m_x].m_bIsHazard)
				quit = true;
			break;
		case 's': // Down.
		case 'S':
			if (player.m_y < ROWS - 1 && !map[player.m_y + 1][player.m_x].m_bIsObstacle)
				player.m_y++;
			else if (map[player.m_y - 1][player.m_x].m_bIsHazard)
				quit = true;
			break;
		case 'a': // Left.
		case 'A':
			if (player.m_x > 0 && !map[player.m_y][player.m_x - 1].m_bIsObstacle)
				player.m_x--;
			else if (map[player.m_y - 1][player.m_x].m_bIsHazard)
				quit = true;
			break;
		case 'd': // Right.
		case 'D':
			if (player.m_x < COLS - 1 && !map[player.m_y][player.m_x + 1].m_bIsObstacle)
				player.m_x++;
			else if (map[player.m_y - 1][player.m_x].m_bIsHazard)
				quit = true;
			break;
		case 'q':
		case 'Q':
			quit = true;
			break;
		}
		system("cls");
	}
	system("pause");
	return 0;
}