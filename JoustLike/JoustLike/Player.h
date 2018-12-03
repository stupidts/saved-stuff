#pragma once
#include "SDL.h"
#include "SDL_image.h"
#define SIZE 64

class Player
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
	int m_iJumpHeight = 10;
	bool m_bRight = true;
	SDL_Rect m_rSrc;
	SDL_Rect m_rDst;
	int m_iCurrProj = 0;
	Player()
	{
		m_x = 1024 / 2;
		m_y = 768 / 2;
		m_iSpeed = 4;
		m_rSrc.x = m_rSrc.y = 0;
		m_rSrc.w = m_rDst.w = 64;
		m_rSrc.h = m_rDst.h = 64;
		UpdateDst();
	}
	void MoveX(int m)
	{
		m_x += m * m_iSpeed; // m_x = m_x + ...
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
		m_rSrc.x = 64 * m_iFrameCtr;
	}
	void SetIdle()
	{
		m_iFrameCtr = 0;
		m_rSrc.x = 44 * m_iFrameCtr;
	}
};
