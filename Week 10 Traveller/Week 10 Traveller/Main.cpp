#include <iostream>
#include <fstream>
#include <conio.h> // Sorry non-VS users. 
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

bool BuildMap(char m[][COLS]) // Passing 2D array to function.
{
	ifstream inFile("Level.txt");
	if (inFile.is_open())
	{
		for (int row = 0; row < ROWS; row++)
		{
			for (int col = 0; col < COLS; col++)
			{
				inFile >> m[row][col]; /* This calls the stream extraction one character at a time
										  because map holds single characters. */
										  /*if (m[row][col] == '.') // You can uncomment these lines if you want spaces instead of dots
											  m[row][col] = ' ';*/  // but remember we're going to convert it to png tiles soon enough.

			}
		}
		inFile.close(); // Thanks Jack for the reminder. I put it in the right place this time.
		return 0;
	}
	return 1;
}

void PrintMap(char m[][COLS], const Player& p) // Taking in the array and a reference to player.
{
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			if (row == p.m_y && col == p.m_x)
				cout << '@'; // If map position is the player's position, print the player char.
			else
				cout << m[row][col]; // Print whatever tile at map position.
		}
		cout << endl;
	}
}

int main()
{
	bool quit = false; // Our loop control flag.
	char map[ROWS][COLS]; // 2D array of characters.
	char input;
	Player player(COLS / 2, ROWS / 2); // Creating the Player object.

	if (BuildMap(map) == 1) // Here's where we build the map.
		return 1;
	while (!quit)
	{
		PrintMap(map, player);
		input = _getch(); // Again, sorry non-VS users. You can instead use input = getchar(); and hit Enter each time.
		switch (input)
		{
		case 'w':  // Up.
		case 'W':  // Up.
			/* Each of these checks starts with a boundary check then checks if the tile
			   the player is about to jump to is an obstacle. But only one char right now. */
			if (player.m_y > 0 && map[player.m_y - 1][player.m_x] != '#')
				player.m_y--;
			break;
		case 's': // Down.
		case 'S': // Down.
			if (player.m_y < ROWS - 1 && map[player.m_y + 1][player.m_x] != '#')
				player.m_y++;
			break;
		case 'a': // Left.
		case 'A': // Left. Aww. I broke the Konami Code.
			if (player.m_x > 0 && map[player.m_y][player.m_x - 1] != '#')
				player.m_x--;
			break;
		case 'd': // Right.
		case 'D': // Right.
			if (player.m_x < COLS - 1 && map[player.m_y][player.m_x + 1] != '#')
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