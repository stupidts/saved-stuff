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



int main(int argc, char* args[])
{
	bool quit = false;
	Level levels[5];
	Game game; // Defining game object.
	game.init("SDL Engine Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, 0);

	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* tileSurf = IMG_Load("Tiles.png");
	SDL_Texture* tileText = SDL_CreateTextureFromSurface(game.GetRenderer(), tileSurf);
	SDL_FreeSurface(tileSurf);
	cout << "Tile ts init" << endl;
	SDL_Surface* playerSurf = IMG_Load("Player.png");
	SDL_Texture* playerText = SDL_CreateTextureFromSurface(game.GetRenderer(), playerSurf);
	SDL_FreeSurface(playerSurf);
	cout << "Player ts init" << endl;

	//Player player(COLS / 2, ROWS / 2);
	int currLevel(0);

	if (game.BuildMap(levels[0], "Level1.txt", game.GetRenderer(), tileText) == 1)
		return 1;
	levels[0].AddDoor(14, 20, 1, 17, 13);
	if (game.BuildMap(levels[1], "Level2.txt", game.GetRenderer(), tileText) == 1)
		return 1;
	levels[1].AddDoor(17, 14, 0, 15, 20);
	levels[1].AddDoor(27, 15, 2, 17, 13);
	levels[1].AddDoor(10, 6, 3, 26, 11);
	if (game.BuildMap(levels[2], "Level3.txt", game.GetRenderer(), tileText) == 1)
		return 1;
	levels[2].AddDoor(17, 14, 1, 27, 16);
	if (game.BuildMap(levels[3], "Level4.txt", game.GetRenderer(), tileText) == 1)
		return 1;
	levels[3].AddDoor(27, 11, 1, 11, 6);
	levels[3].AddDoor(16, 14, 4, 16, 13);
	levels[3].AddDoor(9, 6, 4, 9, 7);
	if (game.BuildMap(levels[4], "Level5.txt", game.GetRenderer(), tileText) == 1)
		return 1;
	levels[4].AddDoor(9, 6, 3, 9, 7);
	levels[4].AddDoor(16, 14, 3, 16, 13);

	Player player(COLS * 32 / 2, ROWS * 32 / 2, game.GetRenderer(), playerText);
	cout << "player init" << endl;
	cout << currLevel << endl;
	//game.PrintMap(levels[currLevel], player);
	while (game.running())
	{
		game.handleEvents();
		if (game.tick())
		{
			game.update(levels[currLevel], player, &currLevel, tileText);
			game.render(levels[currLevel], player);
		}
	}
	SDL_DestroyTexture(tileText);
	SDL_DestroyTexture(playerText);
	game.clean();
	system("pause");
	
	return 0;
}