#include "TextureManager.h"
#include "Game.h"	
#include <string>

SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	// sent with nullptr
	SDL_RenderCopy(Game::renderer, tex, nullptr, &dest);
}
SDL_Texture* TextureManager::LoadAnimatedTexture(const char* Name, int dir)
{
	SDL_RenderClear(Game::renderer);

	SDL_Texture* image_sum = SDL_CreateTexture(Game::renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 24 * 3, 24);
	SDL_SetRenderTarget(Game::renderer, image_sum);

	SDL_Texture* image;
	SDL_Rect image_rect;
	image_rect.y = 0;
	image_rect.w = 24;
	image_rect.h = 24;
	std::string path;
	for (int i = 0; i < 3; i++)
	{
		path = std::to_string(i + 1);
		path = "Sprites/" + std::string(Name) + "_" + std::to_string(dir) + "_" + path + ".png";
		image = LoadTexture(path.c_str());
		image_rect.x = 24 * i;
		SDL_RenderCopy(Game::renderer, image, NULL, &image_rect);
	}
	SDL_SetRenderTarget(Game::renderer, NULL);
	return image_sum;
}