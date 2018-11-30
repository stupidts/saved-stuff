#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#define SIZE 64
using namespace std;

class Projectile
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
	SDL_Rect m_rSrc;
	SDL_Rect m_rDst;
	SDL_Surface* m_image;
	SDL_Texture* m_texture;
	Projectile()
	{
		m_rSrc.x = m_rSrc.y = 0;
		m_rSrc.w = m_rDst.w = 64;
		m_rSrc.h = m_rDst.h = 64;
		m_image = IMG_Load("spaghetti.png");
	}
	Projectile(int x, int y, int speed)
	{
		m_x = x;
		m_y = y;
		m_iSpeed = speed;
		m_rSrc.x = m_rSrc.y = 0;
		m_rSrc.w = m_rDst.w = 64;
		m_rSrc.h = m_rDst.h = 64;
		UpdateDst();
	}
	//~Projectile()
	//{
	//	cout << "Deleted Projectile" << endl;
	//}
	void Init(SDL_Surface* img, SDL_Texture* txt)
	{
		m_image = img;
		m_texture = txt;
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
	void AdvanceAnim()
	{
		m_iFrameCtr++;
		if (m_iFrameCtr == m_iFrameMax)
		{
			m_iFrameCtr = 0;
		}
		m_rSrc.x = 44 * m_iFrameCtr;
	}
	void SpawnProjectile(int x, int y, int speed)
	{
		Projectile(x, y, speed);
	}
};
