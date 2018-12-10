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

class BGTile : public Sprite
{
public:
	bool m_bIsObstacle;
	bool m_bIsHazard;
	bool m_bIsDoor;

	BGTile()
	{
		m_bIsObstacle = false;
		m_bIsHazard = false;
		m_bIsDoor = false;
	}

	void SetBGTile(const char c, SDL_Texture* texture)
	{
		m_rSrc.w = m_rDst.w = 32;
		m_rSrc.h = m_rDst.h = 32;
		m_cOutput = c;
		if (m_cOutput == '+') // + in the file so it's easier to notice in a char mess
		{
			m_cOutput = 'Q';  // Door character
			m_bIsDoor = true;
		}				  // vvv checks if the char is a Stone, Moss Stone, wood wall, roof tile, tree stump, full tree or a dungeon brick vvv
		else if (m_cOutput == 'M' || m_cOutput == 'm' || m_cOutput == '=' || m_cOutput == 'H' || m_cOutput == 'O' || m_cOutput == '#' || m_cOutput == 'B')
			m_bIsObstacle = true;
		else if (m_cOutput == 'X') // is it a hazard?
			m_bIsHazard = true;
		else
		{
			m_bIsObstacle = false;
			m_bIsDoor = false;
			m_bIsHazard = false;
		}

		SetRect();
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

class Player : public LOTile
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

	Player(int x, int y, SDL_Renderer* r, SDL_Texture* t) : LOTile(x, y)
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


class Door : public LOTile
{
private:
	int m_iToLevel;
	int m_iDestX;
	int m_iDestY;
public:
	Door()
	{

	}

	void GetDoor(int* tl, int* dx, int* dy) // accesses the private variables from the outside cold harsh world
	{
		*tl = m_iToLevel;
		*dx = m_iDestX * 32;
		*dy = m_iDestY * 32;

	}

	void SetDoor(const int x, const int y, const int tl, const int dx, const int dy) // sets a doors location, file and destination
	{
		m_x = x;
		m_y = y;
		m_iToLevel = tl;
		m_iDestX = dx;
		m_iDestY = dy;
	}
};

class Level
{
public:
	int m_iNumDoors;
	Door doors[3];

	BGTile map[ROWS][COLS];

	Level()
	{
		m_iNumDoors = 0;
	}

	void AddDoor(const int x, const int y, const int tl, const int dx, const int dy) // makes a door...
	{
		if (m_iNumDoors < 3)
		{
			doors[m_iNumDoors].SetDoor(x, y, tl, dx, dy); // gets the coordinates from whatever universe it came from
			m_iNumDoors++;
		}
	}
};
