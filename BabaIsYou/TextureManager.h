#pragma once

#include "Game.h"

class TextureManager
{
public:
	static SDL_Texture* LoadAnimatedTexture(const char* Name, int dir);
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};