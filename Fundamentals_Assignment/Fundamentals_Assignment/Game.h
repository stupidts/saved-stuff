#pragma once
#include "SDL.h"

class Game
{
private:
	bool m_bRunning;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

public:
	Game() {}
	~Game() {}

	bool init(const char* title, int xpos, int ypos, int width, 
	          int height, int flags);
	bool running();
	void update();
	void handleEvents();
	void render();
	void clean();
};