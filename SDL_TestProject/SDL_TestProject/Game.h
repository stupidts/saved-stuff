#pragma once
#include "SDL.h"

class Game
{
private:
	bool m_bRunning;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Surface* m_image;
	SDL_Texture* m_texture;

	SDL_Rect m_rSrc;
	SDL_Rect m_rDst;
	double m_dAngle = 0;

public:
	Game() {}
	~Game() {}

	bool init(const char* title, int xpos, int ypos, int width,
			  int height, int flags);
	bool running();
	void update();
	void render();
	void handleEvents();
	void clean();

};