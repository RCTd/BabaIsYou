#include "Object.h"
#include "TextureManager.h"

object::object(const char* name, int x, int y)
{
	this->x = x;
	this->y = y;
	objTexture = TextureManager::LoadAnimatedTexture(name, 0);
	srcRect.h = 24; destRect.x = x;
	srcRect.w = 24; destRect.y = y;
	srcRect.x = 0; destRect.w = srcRect.w;
	srcRect.y = 0; destRect.h = srcRect.h;
}
object::~object()
{
	if (objTexture != NULL)
	{
		SDL_DestroyTexture(objTexture);
		objTexture = NULL;
	}
}
void object::update()
{
	if (isYou)
	{
		if (x % 24 != 0)
			x += 2;
		else
			ismoving = false;
	}
	frame++;
	if (floor(frame / 10) >= 3)
		frame = 0;
	srcRect.h = 24;
	srcRect.w = 24;
	srcRect.x = 24 * floor(frame / 10);
	srcRect.y = 0;

	destRect.x = x;
	destRect.y = y;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

}

void object::render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}