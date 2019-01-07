#pragma once
#include "SDL.h"
#include "SDL_image.h"
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