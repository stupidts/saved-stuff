#include <iostream>
#include "Game.h"
using namespace std;

bool Game::init(const char* title, int xpos, int ypos, int width,
		  int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "SDL init success" << endl;

		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != 0)
		{
			cout << "window creation successul" << endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0)
			{
				cout << "renderer creation success" << endl;
				SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);

			}
			else
			{
				cout << "renderer init fail" << endl;
				return false;
			}
		}
		else
		{
			cout << "window init fail" << endl;
			return false;
		}
	}
	else
	{
		cout << "SDL init fail" << endl;
		return false;
	}
	cout << "init success" << endl;
	m_bRunning = true;
	return true;
}

bool Game::running()
{
	return m_bRunning;
}

void Game::update()
{

}

void Game::handleEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
		}
	}
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);
	SDL_RenderPresent(m_pRenderer);
}

void Game::clean()
{
	cout << "cleaning game" << endl;
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}