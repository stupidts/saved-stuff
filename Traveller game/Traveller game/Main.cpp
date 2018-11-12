#include <iostream>
#include <fstream>
#include <conio.h> // Sorry non-Windows users. 
using namespace std;
#define ROWS 24
#define COLS 32

/* Important note: x coordinate is player's COLUMN position and
   y coordinate is player's ROW position. Don't mix these up! */

class Player
{
public:
	int m_x;
	int m_y;
	Player(int x, int y) : m_x(x), m_y(y) // Note the initializers for the properties and empty {}.
	{
		// Nothing needed in here.
	}
};

class Tile
{
public: 
	bool m_obstacle;
	bool m_hazard;
	bool m_water;

private:
	void CheckObstacle(char m[ROWS][COLS])
	{

	}
};

bool BuildMap(char m[][COLS]) // Passing 2D array to function.
{
	ifstream inFile("Level.txt");
	if (inFile.is_open())
	{
		for (int row = 0; row < ROWS; row++)
		{
			for (int col = 0; col < COLS; col++)
			{
				inFile >> m[row][col];	
				if (m[row][col] == '.')
					m[row][col] = ' ';
			}
		}
		return 0;
	}
	return 1;
}

void PrintMap(char m[][COLS], Player& p)
{
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			if (row == p.m_y && col == p.m_x)
				cout << "@";
			else
				cout << m[row][col];
		}
		cout << endl;
	}
}

int main()
{
	bool quit = false;
	char map[ROWS][COLS]; // 2D array of characters.
	char input;
	Player player(COLS / 2, ROWS / 2);
	Tile tile;

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
			if (player.m_y > 0 && map[player.m_y - 1][player.m_x] != '#' && 
				                  map[player.m_y - 1][player.m_x] != '~') // How can we add to these checks to account for the '#' obstacles?
				player.m_y--;
			break;
		case 's': // Down.
		case 'S':
			if (player.m_y < ROWS - 1 && map[player.m_y + 1][player.m_x] != '#' &&
				                         map[player.m_y + 1][player.m_x] != '~')
				player.m_y++;
			break;
		case 'a': // Left.
		case 'A':
			if (player.m_x > 0 && map[player.m_y][player.m_x - 1] != '#' &&
				                  map[player.m_y][player.m_x - 1] != '~')
				player.m_x--;
			break;
		case 'd': // Right.
		case 'D':
			if (player.m_x < COLS - 1 && map[player.m_y][player.m_x + 1] != '#' &&
				                         map[player.m_y][player.m_x + 1] != '~')
				player.m_x++;
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