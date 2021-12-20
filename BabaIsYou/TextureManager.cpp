//#include "TextureManager.h"
#include"Game.h"
#include <string>


SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);
	SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0, 0, 0));
	//if (tempSurface)
	/*else
		SDL_Log("tempS Create ERROR");*/
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return tex;
}

//SDL_Texture* TextureManager::LoadTexture(const char* fileName,bool)
//{
//	SDL_Surface* tempSurface = IMG_Load(fileName);
//	SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0, 0, 0));
//	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
//	SDL_FreeSurface(tempSurface);
//	return tex;
//}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	// sent with nullptr
	SDL_RenderCopy(Game::renderer, tex, nullptr, &dest);
}
SDL_Texture* TextureManager::LoadAnimatedTexture(const char* Name, int dir)
{
	SDL_Surface* surf = SDL_CreateRGBSurface(0, 24 * 3, 24, 32, 0, 0, 0, 0);
	SDL_RenderClear(Game::renderer);
	SDL_Texture* image = nullptr;
	SDL_Rect image_rect;
	SDL_Surface* loadedSurface;
	image_rect.y = 0;
	image_rect.w = 24;
	image_rect.h = 24;
	std::string path;
	for (int i = 0; i < 3; i++)
	{
		path = std::to_string(i + 1);
		path = "Sprites/" + std::string(Name) + "_" + std::to_string(dir) + "_" + path + ".png";
		loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL)
		{
			printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		}
		image_rect.x = 24 * i;
		SDL_BlitSurface(loadedSurface, NULL, surf, &image_rect);
	}
	SDL_FreeSurface(loadedSurface);
	SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 0, 0, 0));
	image = SDL_CreateTextureFromSurface(Game::renderer, surf);
	return image;
}