#include <iostream>
#include "Game.h"


int main(int argc, char *args[]) // Main header must be this.
{
	Game game;
	game.init("Game Engine", 100, 100, 1024, 768, 0);
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