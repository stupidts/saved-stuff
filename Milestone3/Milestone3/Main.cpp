#include <iostream>
#include <fstream>
#include <string>
#include <conio.h> // Sorry non-Windows users. 
#include "SDL.h"
#include "Game.h"
using namespace std;
#define ROWS 24
#define COLS 32

/* Important note: x coordinate is player's COLUMN position and
   y coordinate is player's ROW position. Don't mix these up! */

bool BuildMap(Level& l, const char* n, SDL_Renderer* g, SDL_Texture* texture) // Passing 2D array to function.
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
				temp = (temp == '*' ? ' ' : temp);
				l.map[row][col].SetImage(g, texture);
				l.map[row][col].SetBGTile(temp, texture);
				l.map[row][col].m_rDst = { col * 32, row * 32, 32, 32 };
			}
		}
		inFile.close();
		return 0;
	}
	return 1;
}

void CheckDoors(int& cl, Player& p, Level& l)
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

int main(int argc, char* args[])
{
	bool quit = false;
	Level levels[5];
	Game game; // Defining game object.
	
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* tileSurf = IMG_Load("Tiles.png");
	SDL_Texture* tileText = SDL_CreateTextureFromSurface(game.GetRenderer(), tileSurf);
	SDL_FreeSurface(tileSurf);
	SDL_Surface* playerSurf = IMG_Load("Player.png");
	SDL_Texture* playerText = SDL_CreateTextureFromSurface(game.GetRenderer(), playerSurf);
	SDL_FreeSurface(playerSurf);
	Player p(COLS / 2, ROWS / 2, game.GetRenderer(), playerText);

	char input;
	//Player player(COLS / 2, ROWS / 2);
	int currLevel(0);

	/*if (BuildMap(levels[0], "Level1.txt", game.GetRenderer(), tileText) == 1)
		return 1;
	levels[0].AddDoor(14, 20, 1, 17, 14);
	if (BuildMap(levels[1], "Level2.txt", game.GetRenderer(), tileText) == 1)
		return 1;
	levels[1].AddDoor(17, 14, 0, 14, 20);
	levels[1].AddDoor(27, 15, 2, 17, 14);
	levels[1].AddDoor(10, 6, 3, 27, 11);
	if (BuildMap(levels[2], "Level3.txt", game.GetRenderer(), tileText) == 1)
		return 1;
	levels[2].AddDoor(17, 14, 1, 27, 15);
	if (BuildMap(levels[3], "Level4.txt", game.GetRenderer(), tileText) == 1)
		return 1;
	levels[3].AddDoor(27, 11, 1, 10, 6);*/

	game.init("SDL Engine Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, 0);
	Player player(COLS / 2, ROWS / 2, game.GetRenderer(), playerText);
	while (game.running())
	{
		game.handleEvents();
		if (game.tick())
		{
			game.update(levels[currLevel], p, currLevel);
			game.render(levels[currLevel], p);
		}
	}
	SDL_DestroyTexture(tileText);
	SDL_DestroyTexture(playerText);
	game.clean();
	system("pause");
	/*while (!quit)
	{
		PrintMap(levels[currLevel], player);
		 = _getch();
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
				levels[0].AddDoor(14, 20, 1, 17, 14);
				BuildMap(levels[0], "Level2.txt");
			}
			if (currLevel == 1)
			{
				cout << "cl 1" << endl;
				levels[1].AddDoor(17, 14, 0, 14, 20);
				levels[1].AddDoor(27, 15, 2, 17, 14);
				levels[1].AddDoor(10, 6 , 3, 27, 11);
				BuildMap(levels[1], "Level2.txt");
			}
			if (currLevel == 2)
			{
				cout << "cl 2" << endl;
				levels[2].AddDoor(17, 14, 1, 27, 15);
				BuildMap(levels[2], "Level3.txt");
			}
			if (currLevel == 3)
			{
				cout << "cl 3" << endl;
				levels[3].AddDoor(27, 11, 1, 10, 6 );
				BuildMap(levels[3], "Level4.txt");
			}
		}
	}*/
	//system("pause");
	return 0;
}