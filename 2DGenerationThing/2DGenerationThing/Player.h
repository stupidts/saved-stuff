#pragma once
#include "Sprite.h"
#include <vector>

class Player : public Sprite
{
private:
	void UpdateDst()
	{
		m_rDst.x = m_x;
		m_rDst.y = m_y;
	}
public:
	typedef std::vector<int> vector;
	double m_x;
	double m_y;
	double m_iSpeed;
	int m_iFrameCtr = 0;
	int m_iFrameMax = 1;
	bool m_bRight = true;
	SDL_Rect m_rSrc;
	SDL_Rect m_rDst;
	SDL_Texture* m_pTexture;

	float velocity = 2;
	bool m_bjumping = false;
	float m_fGravity = -10;
	float m_fJumpSpeed = 10;
	float m_fFallSpeed = 20;
	float m_fCurrJumpSpeed = 0;

	Player(double x, double y, SDL_Renderer* r, SDL_Texture* t)
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
	void MoveX(double m)
	{
		m_x += (m * m_iSpeed) / 10;
		UpdateDst();
	}
	void MoveY(double m)
	{
		m_y -= (m * m_iSpeed) / 10;
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