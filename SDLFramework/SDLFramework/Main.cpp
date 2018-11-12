#include <iostream>
#include "Game.h"
using namespace std;

Game* g_game = nullptr; // Pointer to a game object, initialized to 'null'

int main(int argc, char* args[])
{
	g_game = new Game(); // Creating the game object dynamically.
	g_game->init(); // Calling init through the g_game pointer. -> is the . operator for pointers


	while (true)
	{

	}

	system("pause");
	return 0;
}