#pragma once
#include "SDL.h"

class Game
{
private:
	bool m_bRunning; // Control variable
	SDL_Window* m_pWindow; // Pointer to an SDL window object
	SDL_Renderer* m_pRenderer; // Pointer to an SDL renderer

public:
	Game() {} // Constructor. Get's called on object creation
	~Game() {} // Destructor Get's called on de-allocation

	bool init() {} // Initializes stuff
	bool running() {} // Is the game still running
	void update() {} // The entire game updating 
	void handleEvents() {} // User input and event handling
	void render() {} // Renders stuff on screen
	void clean() {} // Final call to cleanup
};