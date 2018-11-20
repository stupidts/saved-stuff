#ifndef _CLASSES_H_
#define _CLASSES_H_

#include <iostream>

#define ROWS 24
#define COLS 32


struct Sprite
{
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

	void SetBGTile(const char c)
	{
		m_cOutput = c;
		if (m_cOutput == '*') // * turns into
			m_cOutput = ' ';  // blank space
		if (m_cOutput == '+') // + in the file so it's easier to notice in a char mess
			m_cOutput = 'T';  // Door character
							  // vvv checks if the char is a Stone, Moss Stone, wood wall, roof tile, tree stump, full tree or a dungeon brick vvv
		if (m_cOutput == 'M' || m_cOutput == 'm' || m_cOutput == '=' || m_cOutput == 'H' || m_cOutput == 'O' || m_cOutput == '#' || m_cOutput == 'B') 
			m_bIsObstacle = true;
		if (m_cOutput == 'X') // is it a hazard?
			m_bIsHazard = true;
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

class Player : public LOTile
{
public:
	Player(int x, int y) : LOTile(x, y)
	{
		m_cOutput = '@'; // player char
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
		std::cout << "tl:" << std::to_string(tl) << ", dx:" << std::to_string(dx) << ", dy:" << std::to_string(dy) << std::endl;
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
		std::cout << "H AddDoor()" << std::endl;
		if (m_iNumDoors < 3)
		{
			std::cout << m_iNumDoors << std::endl;
			doors[m_iNumDoors].SetDoor(x, y, tl, dx, dy); // gets the coordinates from whatever universe it came from
			std::cout << "H AddDoor(), SetDoor()" << std::endl;
			m_iNumDoors++;
		}
	}
};
#endif