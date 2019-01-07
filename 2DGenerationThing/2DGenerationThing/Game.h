#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "World.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <string>
#define FPS 60

class Game
{
private:
	bool m_bRunning;
	bool m_bGotTick;
	bool m_bUpPressed = false;
	bool m_bDownPressed;
	bool m_bLeftPressed;
	bool m_bRightPressed;
	bool m_bSpeedUp;
	int m_iFPS;
	int m_iTickCtr = 0;
	int m_iTickMax = 8;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Surface* m_sPlayer;
	SDL_Texture* m_tPlayer;
	SDL_Surface* m_sTile;
	SDL_Texture* m_tTile;
public:
	Game() :m_iFPS(FPS), m_bGotTick(false), m_bUpPressed(false),
		m_bDownPressed(false), m_bLeftPressed(false), m_bRightPressed(false) {}
	~Game() {}

	bool init(const char* title, int xpos, int ypos, int width,
		int height, int flags);
	bool running();
	bool tick();
	void update(Player& p);
	void handleEvents(Player& p);
	void render(Player& p);
	void clean();

	SDL_Renderer* GetRenderer()
	{
		return m_pRenderer;
	}
};
