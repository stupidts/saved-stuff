#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Level.h"
#define OTILES 8
#define HTILES 1
#define ROWS 24
#define COLS 32
#define FPS 10

constexpr char g_cOTiles[OTILES] = { 'M', 'm', '#', 'O', '=', 'H', 'B', '%' };
constexpr char g_cHTiles[HTILES] = { 'X' };


class Game
{
private:
	bool m_bRunning;
	// Added for W11
	bool m_bGotTick;
	bool m_bUpPressed;
	bool m_bDownPressed;
	bool m_bLeftPressed;
	bool m_bRightPressed;
	bool m_bShoot;
	int m_iFPS;
	int m_iTickCtr = 0;
	int m_iTickMax = 8;
	// 
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
	void update(Level& l, Player& p, int currLevel);
	void handleEvents();
	void render(Level& l, Player& p);
	void clean();

	SDL_Renderer* GetRenderer()
	{
		return m_pRenderer;
	}
};
