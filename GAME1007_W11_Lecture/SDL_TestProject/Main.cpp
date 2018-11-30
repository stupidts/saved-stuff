#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Projectile.h"
using namespace std;

int main(int argc, char* args[])
{
	Game game; // Defining game object.
	Player p;
	Projectile proj[50];
	game.init("SDL Engine Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, 0);
	while (game.running())
	{
		game.handleEvents();
		if (game.tick())
		{
			game.update(p, proj);
			game.render(p, proj);
		}
	}
	game.clean();
	system("pause");
	return 0;
}