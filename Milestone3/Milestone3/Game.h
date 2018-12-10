#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Level.h"
#include <iostream>
#include <fstream>
#include <string>
#define OTILES 8
#define HTILES 1
#define ROWS 24
#define COLS 32
#define FPS 60

constexpr char g_cOTiles[OTILES] = { 'M', 'm', '#', 'O', '=', 'H', 'B', '%' };
constexpr char g_cHTiles[HTILES] = { 'X' };


class Game
{
private:
	bool m_bRunning;
	bool m_bGotTick;
	bool m_bUpPressed;
	bool m_bDownPressed;
	bool m_bLeftPressed;
	bool m_bRightPressed;
	bool m_bShoot;
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
	void update(Level& l, Player& p, int* currLevel, SDL_Texture* t);
	void handleEvents();
	void render(Level& l, Player& p);
	void clean();

	SDL_Renderer* GetRenderer()
	{
		return m_pRenderer;
	}

	/*void PrintMap(Level& l, const Player& p)
	{
		for (int row = 0; row < ROWS; row++)
		{
			for (int col = 0; col < COLS; col++)
			{
				if (row == (p.m_rDst.x / 32) && col == (p.m_rDst.y / 32))
					std::cout << p.m_cOutput;
				else
					std::cout << l.map[row][col].m_cOutput;
			}
			std::cout << std::endl;
		}
	}*/

	bool BuildMap(Level& l, const char* n, SDL_Renderer* g, SDL_Texture* texture) // Passing 2D array to function.
	{
		std::cout << "BuildMap(); " << n << std::endl;
		std::ifstream inFile(n);
		if (inFile.is_open())
		{
			char temp;
			for (int row = 0; row < ROWS; row++)
			{
				for (int col = 0; col < COLS; col++)
				{
					inFile >> temp;
					temp = (temp == '*' ? ' ' : temp);
					l.map[row][col].SetBGTile(temp, texture);
					l.map[row][col].SetImage(g, texture);
					l.map[row][col].m_rDst = { col * 32, row * 32, 32, 32 };
				}
			}
			inFile.close();
			return 0;
		}
		return 1;
	}
	void CheckDoors(int* cl, Player& p, Level& l)
	{
		std::cout << "\n\n\nm_iNumDoors " + std::to_string(l.m_iNumDoors) << std::endl;
		std::cout << "cl: " << *cl << std::endl;
		for (int i = 0; i < l.m_iNumDoors; i++)
		{
			if (l.doors != 0)
			{
				if (p.m_rDst.x / 32 == l.doors[i].m_x && p.m_rDst.y / 32 == l.doors[i].m_y)
				{
					p.m_rDst.x /= 32;
					p.m_rDst.y /= 32;
					l.doors[i].GetDoor(&*cl, &p.m_rDst.x, &p.m_rDst.y);
					std::cout << "cl:" << std::to_string(*cl) << ", p.m_x:" << std::to_string(p.m_x) << ", p.m_y:" << std::to_string(p.m_y) << std::endl;
				}
			}
			else
				std::cout << "\n\n\nSomething went wrong" << std::endl;
		}
	}
};
