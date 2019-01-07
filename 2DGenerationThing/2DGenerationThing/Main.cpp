#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "SDL.h"
#include "Game.h"
#include <vector>
using namespace std;

int main(int argc, char* args[])
{
	bool quit = false;
	Game game;
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

	Player player(540, 360, game.GetRenderer(), playerText);
	cout << "player init" << endl;
	while (game.running())
	{
		game.handleEvents(player);
		if (game.tick())
		{
			game.update(player);
			game.render(player);
		}
	}
	SDL_DestroyTexture(tileText);
	SDL_DestroyTexture(playerText);
	game.clean();
	system("pause");

	return 0;
}