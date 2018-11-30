#include <chrono>
#include <iostream>
#include "Game.h"
#include "Projectile.h"
using namespace std;
using namespace chrono;

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
		m_image = IMG_Load("walk-right.png");
		if (m_image == 0)
		{
			cout << "image load fail" << endl;
			return false;
		}
		m_texture = SDL_CreateTextureFromSurface(m_pRenderer, m_image);
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
			cout << "Tick " << tick << " @ " << count << endl;
			return true;
		}
		return false;
	}
	else m_bGotTick = false;
	return false;
}

void Game::update(Player& p, Projectile* proj)
{
	if (m_bShoot && p.m_iCurrProj <= 50)
	{
		//proj = new Projectile[p.m_iCurrProj];
		m_bShoot = false;
		p.m_iCurrProj++;
		for (int i = 0; i < p.m_iCurrProj; i++)
		{
			proj[i].SpawnProjectile(p.m_x, p.m_y, 0);
			//proj[i].m_image = IMG_Load("spaghetti.png");
			proj[i].m_texture = SDL_CreateTextureFromSurface(m_pRenderer, m_image);
		}
	}/*
	for (int i = 0; i < p.m_iCurrProj; i++)
	{
		proj[i].MoveX(p.m_iSpeed*-1); // will only move diagonally 1 way for now
		proj[i].MoveY(p.m_iSpeed*-1);
	}*/
	if (m_bUpPressed)
		p.MoveY(-1);
	if (m_bDownPressed)
		p.MoveY(1);
	if (m_bLeftPressed)
	{
		p.MoveX(-1);
		p.m_bRight = false;
	}
	if (m_bRightPressed)
	{
		p.MoveX(1);
		p.m_bRight = true;

	}
	if (m_bUpPressed || m_bDownPressed || m_bLeftPressed || m_bRightPressed)//Player is moving
	{
		if (m_iTickCtr == m_iTickMax)
		{
			m_iTickCtr = 0;
			p.AdvanceAnim();
		}
		m_iTickCtr++;
	}
	else
	{
		m_iTickCtr = 0;
		p.SetIdle();
	}
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
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case 'w':
					case 'W':
						if (!m_bUpPressed)
							m_bUpPressed = true;	
						break;
					case 's':
					case 'S':
						if (!m_bDownPressed)
							m_bDownPressed = true;
						break;
					case 'a':
					case 'A':
						if (!m_bLeftPressed)
							m_bLeftPressed = true;
						break;
					case 'd':
					case 'D':
						if (!m_bRightPressed)
							m_bRightPressed = true;
						break;
					case 'e':
					case 'E':
						cout << "\n\n\nShoot I think :/\n\n\n";
						m_bShoot = true;
						break;
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
					case 'w':
					case 'W':
						m_bUpPressed = false;
						break;
					case 's':
					case 'S':
						m_bDownPressed = false;
						break;
					case 'a':
					case 'A':
						m_bLeftPressed = false;
						break;
					case 'd':
					case 'D':
						m_bRightPressed = false;
						break;
				}
				break;
		}
	}
}

void Game::render(Player& p, Projectile* proj)
{
	SDL_RenderClear(m_pRenderer); // Clear the screen to the draw color.
	for (int i = 0; i < p.m_iCurrProj; i++)
	{
		SDL_RenderCopyEx(m_pRenderer, proj[i].m_texture, proj[i].GetSrc(), proj[i].GetDst(), 0, 0, SDL_FLIP_NONE);
	}
	SDL_RenderCopyEx(m_pRenderer, m_texture, p.GetSrc(), p.GetDst(), 0, 0, (p.m_bRight?SDL_FLIP_NONE:SDL_FLIP_HORIZONTAL));
	SDL_RenderPresent(m_pRenderer); // Draw anew.
}

void Game::clean()
{
	cout << "cleaning game" << endl;
	SDL_DestroyTexture(m_texture);
	SDL_FreeSurface(m_image);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	IMG_Quit();
	SDL_Quit();
}