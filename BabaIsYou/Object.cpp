#include"Game.h"

object::object(const char* name, int x, int y)
{
	this->name = name;
	if (name == "baba" || name == "keke" || name == "me")
		this->hasdir = true;
	this->x = x;
	this->y = y;
	objTexture = TextureManager::LoadAnimatedTexture(name, 0);
	init();
}
object::object(const char* name, int x, int y, int dir)
{
	this->name = name;
	if (this->name == "baba" || this->name == "keke" || this->name == "me"/*||this->name=="brick"||this->name=="cliff"||this->name=="cloud"||this->name=="fence"||this->name=="grass"||this->name=="hedge"||this->name=="ice"||this->name=="wall"||this->name=="water"*/)
	{
		this->hasdir = true;
	}
	objTexture = TextureManager::LoadAnimatedTexture(name, dir);
	this->x = x;
	this->y = y;
	init();
}

void object::init()
{
	a = 0;
	srcRect.h = 24;
	srcRect.w = 24;
	srcRect.x = 0;
	srcRect.y = 0;
	destRect.x = x;
	destRect.y = y;
	destRect.w = 24;
	destRect.h = 24;
	color.r = 225;
	color.g = 225;
	color.b = 225;
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
	if (a > 0 && a < 24) {
		a += framespeed;
		if (x % 24 != 0 || y % 24 != 0)
		{
			switch (direction)
			{
			case (0):
				x += framespeed;
				break;
			case (16):
				x -= framespeed;
				break;
			case (8):
				y -= framespeed;
				break;
			case (24):
				y += framespeed;
				break;
			}
		}
	}
	else
	{
		ismov = false;
		a = 0;
	}
	frame++;
	if (floor(frame / 10) >= 3)
		frame = 0;
	srcRect.x = int(24 * floor(frame / 10));
	destRect.x = x;
	destRect.y = y;
}

bool object::pushnext(int dir)
{
	bool succes=true;
	int i = x / 24;
	int j = y / 24;
	switch (dir)
	{
	case 8:
		if (j>0&&!Map::objmap[j - 1][i]->me->empty())
			succes=(Map::objmap[j - 1][i]->move(dir));
		break;
	case 0:
		if (i<27&&!Map::objmap[j][i + 1]->me->empty())
			succes = Map::objmap[j][i + 1]->move(dir);
		break;
	case 24:
		if (j<15&&!Map::objmap[j + 1][i]->me->empty())
			succes = Map::objmap[j + 1][i]->move(dir);
		break;
	case 16:
		if (i>0&&!Map::objmap[j][i - 1]->me->empty())
			succes = Map::objmap[j][i - 1]->move(dir);
		break;
	}
	a = 2;
	ismov = true;
	setDirection(dir);
	changeTexture(dir, getStep());
	if (!succes||!move(dir))
		return false;
	return true;
}

void object::changeTexture(int dir, int step)
{
	if (hasDir())
	{
		objTexture = TextureManager::LoadAnimatedTexture(name.c_str(), dir + step);
		SDL_SetTextureColorMod(objTexture, color.r, color.g, color.b);
	}
}

void object::render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
bool object::move(int dir)
{
	int i = x / 24;
	int j = y / 24;
	switch (dir)
	{
	case 8:
		if (j>0)
		{
			Map::objmap[y / 24][x / 24]->me->remove(this);
			Map::objmap[y / 24 - 1][x / 24]->me->push_front(this);
			decY();
		}
		else
			return false;
		break;
	case 0:
		if (i<27)
		{
			Map::objmap[y / 24][x / 24]->me->remove(this);
			Map::objmap[y / 24][x / 24 + 1]->me->push_front(this);
			incX();
		}
		else
			return false;
		break;
	case 24:
		if (j<15)
		{
			Map::objmap[y / 24][x / 24]->me->remove(this);
			Map::objmap[y / 24 + 1][x / 24]->me->push_front(this);
			incY();
		}
		else
			return false;
		break;
	case 16:
		if (i>0)
		{
			Map::objmap[y / 24][x / 24]->me->remove(this);
			Map::objmap[y / 24][x / 24 - 1]->me->push_front(this);
			decX();
		}
		else
			return false;
		break;
	}
	return true;
}
