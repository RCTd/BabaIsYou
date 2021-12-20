#pragma once

#include <SDL.h>
#include <SDL_image.h>

class TextureManager
{
public:
	static SDL_Texture* LoadAnimatedTexture(const char* Name, int dir);
	static SDL_Texture* LoadTexture(const char* fileName);
	//static SDL_Texture* LoadTexture(const char* fileName,bool);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};