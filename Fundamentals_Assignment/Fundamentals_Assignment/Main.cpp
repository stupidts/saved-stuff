#include <iostream>
#include "SDL.h"
#include "Game.h"
using namespace std;
// hi :)

int main(int argc, char* args[])
{
	Game game;
	game.init("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, 0);
	while (game.running())
	{
		game.handleEvents();
		game.update();
		game.render();
	}
	game.clean();

	system("pause");
	return 0;
}