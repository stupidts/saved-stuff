#include <chrono>
#include <iostream>
#include "Game.h"
#include "Level.h"
using namespace std;
using namespace chrono;
#define ROWS 24
#define COLS 32

bool Game::init(const char* title, int xpos, int ypos, int width,
	int height, int flags)
{
	// Attempt to initialize SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "SDL init success" << endl;
		// Init the window.
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != 0) // Window init success.
		{
			cout << "Window creation successful" << endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0) // Renderer init success.
			{
				cout << "renderer creation success" << endl;
				SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
			}
			else
			{
				cout << "renderer init fail" << endl;
				return false; // Renderer init fail.
			}
		}
		else
		{
			cout << "window init fail" << endl;
			return false; // Window init fail.
		}
		IMG_Init(IMG_INIT_PNG); // Initializing image system.
		m_sEnemy = IMG_Load("Player.png");
		if (m_sEnemy == 0)
		{
			cout << "enemy load fail" << endl;
			return false;
		}
		m_tEnemy = SDL_CreateTextureFromSurface(m_pRenderer, m_sEnemy);
		m_sTile = IMG_Load("Tiles.png");
		if (m_sTile == 0)
		{
			cout << "tile load fail" << endl;
			return false;
		}
		m_tTile = SDL_CreateTextureFromSurface(m_pRenderer, m_sTile);
	}
	else
	{
		cout << "SDL init fail" << endl;
		return false; // SDL init fail.
	}
	cout << "init success" << endl;
	m_bRunning = true; // Everything is okay, start the engine.
	return true;
}

bool Game::running()
{
	return m_bRunning;
}

bool Game::tick()
{
	auto duration = steady_clock::now().time_since_epoch();

	// Millisecond interval.
	/*auto count = duration_cast<milliseconds>(duration).count();
	int tick = 1000 / m_iFPS;*/

	// Microsecond interval.
	auto count = duration_cast<microseconds>(duration).count();
	int tick = 1000000 / m_iFPS;

	/*if (count % tick == 0) // May catch duplicate frames at slower intervals.
	{
		cout << "Tick " << tick << " @ " << count << endl;
		return true;
	}
	return false;*/
	if (count % tick == 0) // Drops potential duplicate frames.
	{
		if (m_bGotTick == false)
		{
			m_bGotTick = true;
			//cout << "Tick " << tick << " @ " << count << endl;
			return true;
		}
		return false;
	}
	else m_bGotTick = false;
	return false;
}

void Game::update(Level& l, Enemy& p, int* currLevel, SDL_Texture* t)
{

}

void Game::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case 'w':
			case 'W':
				m_bUpPressed = true;
				break;
			case 's':
			case 'S':
				m_bDownPressed = true;
				break;
			case 'a':
			case 'A':
				m_bLeftPressed = true;
				break;
			case 'd':
			case 'D':
				m_bRightPressed = true;
				break;
			}
			break;
		}
	}
}

void Game::render(Level& l, Enemy& p)
{
	//cout << "Game::render" << endl;
	SDL_RenderClear(m_pRenderer);
	
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			if (l.map[row][col].m_cOutput != ' ')
				SDL_RenderCopy(m_pRenderer, l.map[row][col].m_pTexture, &l.map[row][col].m_rSrc, &l.map[row][col].m_rDst);
			//cout << "Tile Render: " << row << " " << col << " " << l.map[row][col].m_cOutput << endl;
		}
	}
	SDL_RenderCopyEx(m_pRenderer, m_tEnemy, p.GetSrc(), p.GetDst(), 0, 0, (p.m_bRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL));
	SDL_RenderPresent(m_pRenderer);
}

void Game::clean()
{
	cout << "cleaning game" << endl;
	SDL_DestroyTexture(m_tEnemy);
	SDL_FreeSurface(m_sEnemy);
	SDL_DestroyTexture(m_tTile);
	SDL_FreeSurface(m_sTile);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	IMG_Quit();
	SDL_Quit();
}