#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#define ROWS 24
#define COLS 32

struct Sprite
{
	char m_cOutput;
	SDL_Rect m_rSrc;
	SDL_Rect m_rDst;
	SDL_Texture* m_pTexture;
	SDL_Renderer* m_pRenderer;
	Sprite() {}
	~Sprite() {}

	void SetX(int x)
	{
		m_rDst.x = x * 32;
	}
	void SetY(int y)
	{
		m_rDst.y = y * 32;
	}
	void SetImage(SDL_Renderer* r, SDL_Texture* t)
	{
		m_pTexture = t;
		m_pRenderer = r;
	}
};

class Path : public Sprite
{
public:
	int startX, startY;
	int endX, endY;
	int pathX, pathY;
};

class BGTile : public Path
{
public:
	bool m_bIsObstacle;
	bool m_bIsPath;

	BGTile()
	{
		m_bIsObstacle = false;
		m_bIsPath = false;
		pathX = 0;
		pathY = 0;
	}

	void SetBGTile(const char c, SDL_Texture* texture)
	{
		m_rSrc.w = m_rDst.w = 32;
		m_rSrc.h = m_rDst.h = 32;
		m_cOutput = c;
		if (m_cOutput == 'M' || m_cOutput == 'm' || m_cOutput == '=' || m_cOutput == 'H' || m_cOutput == 'O' || m_cOutput == '#' || m_cOutput == 'B' || m_cOutput == '~')
			m_bIsObstacle = true;
		else
		{
			m_bIsObstacle = false;
		}

		SetRect();
	}

	void SetPath(const char c, int x, int y)
	{
		if (c == 'S')
		{
			m_bIsObstacle = true;
			m_bIsPath = true;
			pathX = x;
			pathY = y;
			startX = x;
			startY = y;
		}
		else if (c == 'E')
		{
			m_bIsObstacle = true;
			m_bIsPath = true;
			pathX = x;
			pathY = y;
			endX = x;
			endY = y;
		}
		else if (c == '#')
		{
			m_bIsObstacle = true;
			m_bIsPath = true;
			pathX = x;
			pathY = y;
		}
	}

	void SetRect()
	{
		switch (m_cOutput)
		{
		case ',':
			m_rSrc = { 0, 0, 32, 32 };
			break;
		case ';':
			m_rSrc = { 32, 0, 32, 32 };
			break;
		case 'M':
			m_rSrc = { 64, 0, 32, 32 };
			break;
		case 'm':
			m_rSrc = { 96, 0, 32, 32 };
			break;
		case '.':
			m_rSrc = { 128, 0, 32, 32 };
			break;
		case '-':
			m_rSrc = { 160, 0, 32, 32 };
			break;
		case '~':
			m_rSrc = { 192, 0, 32, 32 };
			break;
		case 'X':
			m_rSrc = { 224, 0, 32, 32 };
			break;
		case '#':
			m_rSrc = { 0, 32, 32, 32 };
			break;
		case 'O':
			m_rSrc = { 32, 32, 32, 32 };
			break;
		case '=':
			m_rSrc = { 64, 32, 32, 32 };
			break;
		case 'H':
			m_rSrc = { 96, 32, 32, 32 };
			break;
		case 'B':
			m_rSrc = { 128, 32, 32, 32 };
			break;
		case '_':
			m_rSrc = { 160, 32, 32, 32 };
			break;
		case 'Q':
			m_rSrc = { 192, 32, 32, 32 };
			break;
		case '%':
			m_rSrc = { 224, 32, 32, 32 };
			break;
		}
		
	}

	
};

class LOTile : public Sprite
{
public:
	int m_x;
	int m_y;
	LOTile() {}
	LOTile(const int x, const int y)
	{
		SetX(x);
		SetY(y);
	}
};

class Enemy : public LOTile
{
private:
	void UpdateDst()
	{
		m_rDst.x = m_x;
		m_rDst.y = m_y;
	}
public:
	int m_x;
	int m_y;
	int m_iSpeed;
	int m_iFrameCtr = 0;
	int m_iFrameMax = 1;
	bool m_bRight = true;
	SDL_Rect m_rSrc;
	SDL_Rect m_rDst;
	SDL_Texture* m_pTexture;
	int pathNode = 0;

	Enemy(int x, int y, SDL_Renderer* r, SDL_Texture* t) : LOTile(x, y)
	{
		m_x = x;
		m_y = y;
		m_iSpeed = 4;
		m_rSrc = { 0, 0, 32, 32 };
		m_rSrc.w = m_rDst.w = 32;
		m_rSrc.h = m_rDst.h = 32;
		SetImage(r, t);
		UpdateDst();
	}
	~Enemy()
	{
		m_rSrc = { 32, 0, 32, 32 };
		m_rSrc.w = m_rDst.w = 32;
		m_rSrc.h = m_rDst.h = 32;
	}

	void MoveX(int m)
	{
		m_x += m * m_iSpeed;
		UpdateDst();
	}
	void MoveY(int m)
	{
		m_y += m * m_iSpeed;
		UpdateDst();
	}
	const SDL_Rect* GetSrc() { return &m_rSrc; }
	const SDL_Rect* GetDst() { return &m_rDst; }
	void OnFire()
	{
		m_rSrc.x = 32;
	}
	void Swimming()
	{
		m_rSrc.x = 64;
	}
	void AdvanceAnim()
	{
		m_iFrameCtr++;
		if (m_iFrameCtr == m_iFrameMax)
		{
			m_iFrameCtr = 0;
		}
		m_rSrc.x = 32 * m_iFrameCtr;
	}
	void SetIdle()
	{
		m_iFrameCtr = 0;
		m_rSrc.x = 32 * m_iFrameCtr;
	}
};

class Level : public LOTile
{
public:

	BGTile map[ROWS][COLS];

};
