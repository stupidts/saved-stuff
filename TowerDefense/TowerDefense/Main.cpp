#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "SDL.h"
#include "Game.h"
using namespace std;
#define ROWS 24
#define COLS 32

int main(int argc, char* args[])
{
	bool quit = false;
	Level levels[5];
	Game game;
	game.init("SDL Engine Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, 0);

	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* tileSurf = IMG_Load("Tiles.png");
	SDL_Texture* tileText = SDL_CreateTextureFromSurface(game.GetRenderer(), tileSurf);
	SDL_FreeSurface(tileSurf);
	cout << "Tile ts init" << endl;
	SDL_Surface* enemySurf = IMG_Load("Player.png");
	SDL_Texture* enemyText = SDL_CreateTextureFromSurface(game.GetRenderer(), enemySurf);
	SDL_FreeSurface(enemySurf);
	cout << "Enemy ts init" << endl;

	int currLevel(0);
	int playerLevelChoice;//not in use until game works well

	if (game.BuildMap(levels[0], "Level1.txt", game.GetRenderer(), tileText) == 1)
		return 1;
	if (game.BuildPath(levels[0], "Level1Path.txt") == 1);
		return 1;
	if (game.BuildMap(levels[1], "Level2.txt", game.GetRenderer(), tileText) == 1)
		return 1;
	if (game.BuildMap(levels[2], "Level3.txt", game.GetRenderer(), tileText) == 1)
		return 1;
	if (game.BuildMap(levels[3], "Level4.txt", game.GetRenderer(), tileText) == 1)
		return 1;
	if (game.BuildMap(levels[4], "Level5.txt", game.GetRenderer(), tileText) == 1)
		return 1;

	Enemy enemy(COLS * 32 / 2, ROWS * 32 / 2, game.GetRenderer(), enemyText);
	cout << "player init" << endl;
	cout << currLevel << endl;

	while (game.running())
	{
		game.handleEvents();
		if (game.tick())
		{
			game.update(levels[currLevel], enemy, &currLevel, tileText);
			game.render(levels[currLevel], enemy);
		}
	}
	SDL_DestroyTexture(tileText);
	SDL_DestroyTexture(enemyText);
	game.clean();
	system("pause");
	
	return 0;
}