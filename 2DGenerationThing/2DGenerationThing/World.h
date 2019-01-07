#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Sprite.h"
#include "Generation.h"
#include <iostream>
#define ROWS 24
#define COLS 32



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
		/*if (m_cOutput == '+') // + in the file so it's easier to notice in a char mess
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
		}*/

		//SetRect();
	}

	/*void SetRect()
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
	}*/
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