#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Level.h"
#include <iostream>
#include <fstream>
#include <string>
#define ROWS 24
#define COLS 32
#define FPS 60
using namespace std;

class Game
{
private:
	bool m_bRunning;
	bool m_bMenu;
	bool m_bGotTick;
	bool m_bUpPressed;
	bool m_bDownPressed;
	bool m_bLeftPressed;
	bool m_bRightPressed;
	bool m_bShoot;
	int m_iFPS;
	int m_iTickCtr = 0;
	int m_iTickMax = 8;
	int pathX[100];
	int pathY[100];
	char pathChar[100];
	int pathMarker = 0; //used for the arrays
	int ps, pe; //path start, path end, counting these to check for 0 or duplicates
	int nodeX[50];
	int nodeY[50];
	int nodeCount = 0;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Surface* m_sEnemy;
	SDL_Texture* m_tEnemy;
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
	void update(Level& l, Enemy& p, int* currLevel, SDL_Texture* t);
	void handleEvents();
	void render(Level& l, Enemy& p);
	void clean();

	SDL_Renderer* GetRenderer()
	{
		return m_pRenderer;
	}

	bool Menu(const char* choice, SDL_Renderer* g, SDL_Texture* texture)
	{
		//not in use yet until the base game works
	}

	bool BuildMap(Level& l, const char* n, SDL_Renderer* g, SDL_Texture* texture) // Passing 2D array to function.
	{
		cout << "BuildMap(); " << n << endl;
		ifstream inFile(n);
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
			cout << "Built map" << endl;
			return 0;
		}
		return 1;
	}

	bool BuildPath(Level& l, const char* n)
	{
		ifstream inFile(n);
		if (inFile.is_open())
		{
			char temp;
			for (int row = 0; row < ROWS; row++)
			{
				for (int col = 0; col < COLS; col++)
				{
					inFile >> temp;
					l.map[row][col].m_cOutput = temp;
					l.map[row][col].SetPath(temp, col, row);
					if (l.map[row][col].pathX != 0 || l.map[row][col].pathY != 0)
					{
						cout << "Set path for: " << temp << " " << l.map[row][col].pathX << " " << l.map[row][col].pathY << endl;
						pathChar[pathMarker] = temp;
						pathX[pathMarker] = l.map[row][col].pathX;
						pathY[pathMarker] = l.map[row][col].pathY;
						pathMarker++;
					}
				}
			}
			inFile.close();
			cout << "Built path! " << pathMarker << " path tiles!" << endl;
			GeneratePathway(l);
			return 0;
		}
		return 1;
	}

	void PrintMap(Level& l)
	{
		for (int row = 0; row < ROWS; row++)
		{
			for (int col = 0; col < COLS; col++)
			{
				std::cout << l.map[row][col].m_cOutput;
			}
			std::cout << std::endl;
		}
	}

	void GeneratePathway(Level& l)
	{
		//here to put a null end to the array
		if (pathChar[pathMarker + 1] != 'S' || pathChar[pathMarker + 1] != '#' || pathChar[pathMarker + 1] != 'E')
			pathChar[pathMarker + 1] = 'n';

		for (int i = 0; i < 100; i++)
		{
			if (pathChar[i] == 'S')
			{
				ps++;
			}
			else if (pathChar[i] == 'E')
			{
				pe++;
			}
			else if (pathChar[i] == 'n')
			{
				cout << "End path check!" << endl;
				break;
			}
		}

		if (ps < 1)
		{
			cout << "~Did NOT find a path start!~: " << ps << endl; 
			return;
		}
		else if (ps == 1)
		{
			cout << "Found a path start!: " << ps << endl;
		}
		else
		{
			cout << "~Found too many path starts!~: " << ps << endl; 
			return;
		}
		if (pe < 1)
		{
			cout << "~Did NOT find a path end!~: " << pe << endl; 
			return;
		}
		else if (pe == 1)
		{
			cout << "Found a path end!: " << pe << endl;
		}
		else
		{
			cout << "~Found too many path ends!~: " << pe << endl; 
			return;
		}

		//time to check the pathing layout
		//get enemy start point
		for (int i = 0; i < pathMarker; i++)
		{
			if (pathChar[i] == 'S')
			{
				nodeX[nodeCount] = pathX[i];
				nodeY[nodeCount] = pathY[i];
				cout << "pathX[i] " << pathX[i] << endl;
				cout << "pathY[i] " << pathY[i] << endl;
				break;
			}
		}

		PrintMap(l);

		bool right = true, left = true, up = true, down = true;
		bool doneNodes = false;
		int e = 0;
		int tempNodeCount = 0;
		while (!doneNodes && e < 5)
		{
			for (int i = 1; i < COLS; i++)
			{
				//cout << "check right" << endl;
				if (nodeX[nodeCount] + i < 0)
				{
					//cout << "x + i: " << nodeX[nodeCount] + i << endl;
					right = false;
					break;
				}
				//cout << l.map[nodeY[nodeCount]][nodeX[nodeCount] + i].m_cOutput << endl;
				if (l.map[nodeY[nodeCount]][nodeX[nodeCount] + i].m_cOutput == '#')
				{
					//cout << "Checking to the right: x " << l.map[nodeY[nodeCount]][nodeX[nodeCount] + i].pathX << " | y " << l.map[nodeY[nodeCount]][nodeX[nodeCount] + i].pathY << endl;
					
					l.map[nodeY[nodeCount]][nodeX[nodeCount] + i - 1].m_cOutput = '%';
					//cout << nodeX[nodeCount] << " " << nodeY[nodeCount] << " " << nodeCount << endl;
					right = true;
					left = false;
					up = false;
					down = false;
				}
				else if (l.map[nodeY[nodeCount]][nodeX[nodeCount] + i].m_cOutput == 'E')
				{
					l.map[nodeY[nodeCount]][nodeX[nodeCount] + i - 1].m_cOutput = '%';
					l.map[nodeY[nodeCount]][nodeX[nodeCount] + i].m_cOutput = '%';
					doneNodes = true;
					break;
				}
				else
				{
					//cout << "x + i: else" << endl;
					if (right)
					{
						tempNodeCount = nodeCount;
						nodeCount++;
						nodeX[nodeCount] = nodeX[tempNodeCount] + i - 1;
						nodeY[nodeCount] = nodeY[tempNodeCount];
						right = false;
						//cout << "right is true" << endl;
					}
					//cout << i << endl;
					//cout << nodeX[nodeCount] << " " << nodeY[nodeCount] << " " << nodeCount << endl;
					break;
				}
			}
			for (int i = 1; i < COLS; i++)
			{
				//cout << "check left" << endl;
				//cout << nodeX[nodeCount] << " " << nodeY[nodeCount] << " " << nodeCount << endl;
				if (nodeX[nodeCount] - i < 0)
				{
					//cout << "x - i: " << nodeX[nodeCount] - i << endl;
					left = false;
					break;
				}
				//cout << l.map[nodeY[nodeCount]][nodeX[nodeCount] - i].m_cOutput << endl;
				if (l.map[nodeY[nodeCount]][nodeX[nodeCount] - i].m_cOutput == '#')
				{
					//cout << "Checking to the left: " << l.map[nodeY[nodeCount]][nodeX[nodeCount] - i].pathX << " | y " << l.map[nodeY[nodeCount]][nodeX[nodeCount] - i].pathY << endl;
					
					l.map[nodeY[nodeCount]][nodeX[nodeCount] - i + 1].m_cOutput = '%';
					//cout << nodeX[nodeCount] << " " << nodeY[nodeCount] << " " << nodeCount << endl;
					right = false;
					left = true;
					up = false;
					down = false;
				}
				else if (l.map[nodeY[nodeCount]][nodeX[nodeCount] - i].m_cOutput == 'E')
				{
					l.map[nodeY[nodeCount]][nodeX[nodeCount] - i + 1].m_cOutput = '%';
					l.map[nodeY[nodeCount]][nodeX[nodeCount] - i].m_cOutput = '%';
					doneNodes = true;
					break;
				}
				else
				{
					//cout << "x - i: else" << endl;
					if (left)
					{
						tempNodeCount = nodeCount;
						nodeCount++;
						nodeX[nodeCount] = nodeX[tempNodeCount] - i + 1;
						nodeY[nodeCount] = nodeY[tempNodeCount];
						left = false;
						//cout << "left is true" << endl;
					}
					break;
				}
			}
			for (int i = 1; i < ROWS; i++)
			{
				//cout << "check up" << endl;
				//cout << nodeY[nodeCount] << endl;
				if (nodeY[nodeCount] - i < 0)
				{
					//cout << "y - i: " << nodeY[nodeCount] - i << endl;
					up = false;
					break;
				}
				//cout << l.map[nodeY[nodeCount] - i][nodeX[nodeCount]].m_cOutput << endl;
				if (l.map[nodeY[nodeCount] - i][nodeX[nodeCount]].m_cOutput == '#')
				{
					//cout << "Checking to the up: x " << l.map[nodeY[nodeCount] - i][nodeX[nodeCount]].pathX << " | y " << l.map[nodeY[nodeCount] - i][nodeX[nodeCount]].pathY << endl;
					
					l.map[nodeY[nodeCount] - i + 1][nodeX[nodeCount]].m_cOutput = '%';
					//cout << nodeX[nodeCount] << " " << nodeY[nodeCount] << " " << nodeCount << endl;
					right = false;
					left = false;
					up = true;
					down = false;
				}
				else if (l.map[nodeY[nodeCount] - i][nodeX[nodeCount]].m_cOutput == 'E')
				{
					l.map[nodeY[nodeCount] - i + 1][nodeX[nodeCount]].m_cOutput = '%';
					l.map[nodeY[nodeCount] - i][nodeX[nodeCount]].m_cOutput = '%';
					doneNodes = true;
					break;
				}
				else
				{
					//cout << "y - i: else" << endl;
					if (up)
					{
						tempNodeCount = nodeCount;
						nodeCount++;
						nodeX[nodeCount] = nodeX[tempNodeCount];
						nodeY[nodeCount] = nodeY[tempNodeCount] - i + 1;
						up = false;
						//cout << "up is true" << endl;
					}
					break;
				}
			}
			for (int i = 1; i < ROWS; i++)
			{
				//cout << "check down" << endl;
				if (nodeY[nodeCount] + i < 0)
				{
					//cout << "y - i: " << nodeY[nodeCount] - i << endl;
					down = false;
					break;
				}
				//cout << l.map[nodeY[nodeCount] + i][nodeX[nodeCount]].m_cOutput << endl;
				if (l.map[nodeY[nodeCount] + i][nodeX[nodeCount]].m_cOutput == '#')
				{
					//cout << "Checking to the down: " << l.map[nodeY[nodeCount] + i][nodeX[nodeCount]].pathX << " | y " << l.map[nodeY[nodeCount] + i][nodeX[nodeCount]].pathY << endl;

					l.map[nodeY[nodeCount] + i - 1][nodeX[nodeCount]].m_cOutput = '%';
					//cout << nodeX[nodeCount] << " " << nodeY[nodeCount] << " " << nodeCount << endl;
					right = false;
					left = false;
					up = false;
					down = true;
				}
				else if (l.map[nodeY[nodeCount] + i][nodeX[nodeCount]].m_cOutput == 'E')
				{
					l.map[nodeY[nodeCount] + i - 1][nodeX[nodeCount]].m_cOutput = '%';
					l.map[nodeY[nodeCount] + i][nodeX[nodeCount]].m_cOutput = '%';
					doneNodes = true;
					break;
				}
				else
				{
					//cout << "y - i: else" << endl;
					if (down)
					{
						tempNodeCount = nodeCount;
						nodeCount++;
						nodeX[nodeCount] = nodeX[tempNodeCount];
						nodeY[nodeCount] = nodeY[tempNodeCount] + i - 1;
						down = false;
						//cout << "down is true" << endl;
					}
					break;
				}
			}

			//PrintMap(l);
			//e++;
		}
		cout << "Exit loop" << endl;


		//now take the new points and use them somehow


		for (int i = 0; i < 50; i++)
		{
			if (nodeX[i] != 0 && nodeY[i] != 0)
				cout << "Point " << i << ": " << nodeX[i] << " " << nodeY[i] << endl;
		}

		//make the enemies spawn on the startX and startY

		//make the enemies move from nodeXY[0] to nodeXY[1] ......... until they hit final point which does some more complicated stuff
	}
};
