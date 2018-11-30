#pragma once
#include <iostream>
#ifndef _CLASSES_H_
#define _CLASSES_H_
#define ROWS 24
#define COLS 32
using namespace std;

struct Sprite
{
	//Will hold the SDL_Rect members
public:
	char m_cOutput;
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

	void SetBGTile(const char m_cOutput)
	{
		this->m_cOutput = m_cOutput;
		m_bIsHazard = false;
		m_bIsHazard = false;
	}
};


class LOTile : public Sprite
{
public:
	int m_x;
	int m_y;

	LOTile() {} // Def Constructor		
	LOTile(const int x, const int y)
	{
		m_x = x;
		m_y = y;
	}
};

class  Door : public LOTile
{
public:
	int m_iToLevel; //  Holds the value of the current level in the main, the one to change to/
	//  Holds the spawn coordinates of the player in the new level.
	int m_iDestX;   // X , MAX 32
	int m_iDestY;   // Y , MAX 24	

	Door()
	{
		m_cOutput = 'D';
	}

	void SetDoor(const int x, const int y, const int toLv, const int destX, const int destY)
	{
		m_x = x;
		m_y = y;
		m_iToLevel = toLv;
		m_iDestX = destX;
		m_iDestX = destY;

	}

};

class Level : public BGTile
{
private:
	int m_iNumDoors;

public:
	//Supposed to be private
	BGTile map[ROWS][COLS];
	Door doors[3];

	Level()
	{
		m_iNumDoors = 0;
	}

	void AddDoor(const int x, const int y, const int toLv, const int destX, const int destY)
	{
		if (m_iNumDoors < 3)
			doors[m_iNumDoors++].SetDoor(x, y, toLv, destX, destY);
		else if (m_iNumDoors > 3)
			cout << "Too many doors!." << endl;

	}

	int GetNumDoors()
	{
		return m_iNumDoors;
	}

};


class Player : LOTile
{
public:
	Player(int x, int y) : LOTile(x, y)
	{
		m_cOutput = '@';
	}

};


//BGTILE Class

#endif
/* Important note: x coordinate is player's COLUMN position and
   y coordinate is player's ROW position. Don't mix these up! */



   //class Player :
   //{
   //public:
   //	int m_x;
   //	int m_y;
   //	Player(int x, int y) : m_x(x), m_y(y) // Note the initializers for the properties and empty {}.
   //	{
   //		// Nothing needed in here.
   //	}
   //};

