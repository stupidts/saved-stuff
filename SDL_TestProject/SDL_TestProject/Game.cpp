#include <iostream>
#include "Game.h"
using namespace std;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	// Attempt to initialize SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "SDL init success\n";
		// Init the window.
		m_pWindow = SDL_CreateWindow(title, xpos, ypos,	width, height, flags);
		if (m_pWindow != 0) // Window init success.
		{
			cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0) // Renderer init success.
			{
				cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(m_pRenderer,
					0, 0, 0, 255);
			}
			else
			{
				cout << "renderer init fail\n";
				return false; // Renderer init fail.
			}
		}
		else
		{
			cout << "window init fail\n";
			return false; // Window init fail.
		}
		IMG_Init(IMG_INIT_PNG);
		m_image = IMG_Load("Tiles.png");
		if (m_image == 0)
		{
			cout << "image load fail" << endl;
			return false;
		}
		m_texture = SDL_CreateTextureFromSurface(m_pRenderer, m_image);

		m_rSrc.x = 96;
		m_rSrc.y = 32;
		m_rSrc.w = 32;
		m_rSrc.h = 32;

		m_rDst.x = 1024/2;
		m_rDst.y = 768/2;
		m_rDst.w = 64;
		m_rDst.h = 64;
	}
	else
	{
		cout << "SDL init fail\n";
		return false; // SDL init fail.
	}
	cout << "init success\n";
	m_bRunning = true; // Everything inited successfully, start the main loop.
		return true;
}
bool Game::running()
{

}

void Game::update()
{

}

void Game::render()
{
	SDL_RenderClear(m_pRenderer); // Clear the renderer to the draw color.
	SDL_RenderCopy(m_pRenderer, m_texture, &m_rSrc, &m_rDst);
	SDL_RenderPresent(m_pRenderer); // Draw to the screen.
}

void Game::clean()
{
	cout << "cleaning game\n";
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
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
				break;
		}
	}
}