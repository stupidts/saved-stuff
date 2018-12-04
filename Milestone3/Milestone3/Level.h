#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Player.h"
#define ROWS 24
#define COLS 32

struct Sprite
{
	char m_cOutput;
	SDL_Rect m_rSrc;
	SDL_Rect m_rDst;
	SDL_Texture* m_pTexture;
};

class BGTile : public Sprite
{
public:
	bool m_bIsObstacle;
	bool m_bIsHazard;

	BGTile()
	{
		m_bIsObstacle = false;
		m_bIsHazard = false;
	}

	void SetBGTile(const char c, SDL_Texture* texture)
	{
		m_cOutput = c;
		if (m_cOutput == '+') // + in the file so it's easier to notice in a char mess
			m_cOutput = 'D';  // Door character
							  // vvv checks if the char is a Stone, Moss Stone, wood wall, roof tile, tree stump, full tree or a dungeon brick vvv
		if (m_cOutput == 'M' || m_cOutput == 'm' || m_cOutput == '=' || m_cOutput == 'H' || m_cOutput == 'O' || m_cOutput == '#' || m_cOutput == 'B')
			m_bIsObstacle = true;
		if (m_cOutput == 'X') // is it a hazard?
			m_bIsHazard = true;

		//if (m_cOutput == 'M')
		//{
			m_pTexture = texture;
		//}
	}
};

class LOTile : public Sprite
{
public:
	int m_x;
	int m_y;
	LOTile() {}
	LOTile(const int m_x, const int m_y)
	{
		this->m_x = m_x;
		this->m_y = m_y;
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

	void GetDoor(int& tl, int& dx, int& dy) // accesses the private variables from the outside cold harsh world
	{
		tl = m_iToLevel;
		dx = m_iDestX;
		dy = m_iDestY;

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

class Level : public Door
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
