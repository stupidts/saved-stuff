#include <chrono>
#include <iostream>
#include "Game.h"
#include "World.h"
#include "Player.h"
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
		m_sPlayer = IMG_Load("Player.png");
		if (m_sPlayer == 0)
		{
			cout << "player load fail" << endl;
			return false;
		}
		m_tPlayer = SDL_CreateTextureFromSurface(m_pRenderer, m_sPlayer);
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

	auto count = duration_cast<microseconds>(duration).count();
	int tick = 1000000 / m_iFPS;

	if (count % tick == 0)
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

void Game::update(Player& p)
{
	if (p.m_iSpeed > 10) p.m_iSpeed = 0;
	if (p.m_x > 1000) p.m_x = 1000;
	if (p.m_x < 0) p.m_x = 0;
	if (p.m_y > 650) p.m_y = 650; p.m_bjumping = false;
	if (p.m_y < 0) p.m_y = 0;


	//--------!!!GravityZone!!!--------

	p.MoveY(p.m_fGravity);
	
	//--------!!!GravityZone!!!--------

	//Jump stuff

	if (m_bUpPressed && p.m_y >= 650)
	{
		p.m_bjumping = true;
		p.m_fCurrJumpSpeed = p.m_fJumpSpeed;
	}

	if (p.m_bjumping)
	{
		p.m_y -= p.m_fCurrJumpSpeed * 10;

		if (p.m_fCurrJumpSpeed > p.m_fFallSpeed) {
			p.m_fJumpSpeed -= p.m_fGravity;
		}
		else {
			p.m_fCurrJumpSpeed = p.m_fFallSpeed;
		}
	}

	//Jump Stuff End




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

	if (m_bSpeedUp)
	{
		p.m_iSpeed++;
		m_bSpeedUp = false;
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

void Game::handleEvents(Player& p)
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
			case 'e':
			case 'E':
				cout << p.m_x << " " << p.m_y << endl << p.m_rDst.x << " " << p.m_rDst.y << endl << p.m_iSpeed << endl << endl;
				break;
			case '=':
				m_bSpeedUp = true;
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

void Game::render(Player& p)
{
	SDL_RenderClear(m_pRenderer);
	SDL_RenderCopyEx(m_pRenderer, m_tPlayer, p.GetSrc(), p.GetDst(), 0, 0, (p.m_bRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL));
	SDL_RenderPresent(m_pRenderer);
}

void Game::clean()
{
	SDL_DestroyTexture(m_tPlayer);
	SDL_DestroyTexture(m_tTile);
	SDL_FreeSurface(m_sPlayer);
	SDL_FreeSurface(m_sTile);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	IMG_Quit();
	SDL_Quit();
}