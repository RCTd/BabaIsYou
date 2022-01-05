#include "Game.h"
#include "Directed.h"
#include "Text.h"
#include "name.h"

object* keke;
SDL_Renderer* Game::renderer = nullptr;
bool flags::ismoving = false;
bool flags::andmov = true;
bool flags::remove = false;
bool flags::rec = false;
bool flags::tex = false;
bool flags::active = false;
bool flags::erasefg = false;
bool flags::win = false;
bool flags::defeat = false;
bool flags::sink = false;
std::list<object*> *Game::activelist = new std::list<object*>;
List* Map::objmap[16][28] = { nullptr };
List* Map::destroy=new List;
void Game::init(const char* Windowtitle, int x, int y, int w, int h)
{
	if (!SDL_Init(SDL_INIT_EVERYTHING) && IMG_Init(IMG_INIT_PNG))
	{
		window = SDL_CreateWindow(Windowtitle, x, y, w, h, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			SDL_Log("Window Create ERROR %s\n", SDL_GetError());
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				SDL_Log("Renderer Create ERROR %s\n", SDL_GetError());
			}
			else
			{
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
				}
				else
					isRunning = true;
			}
		}
	}
	else
	{
		SDL_Log("INIT ERROR %s\n", SDL_GetError());
	}
	
	gMusic = Mix_LoadMUS("Music/baba.ogg");
	if (gMusic == NULL)
	{
		SDL_Log("Failed to load beat music!SDL_mixer Error : % s\n", Mix_GetError());
	}
	//Mix_PlayMusic(gMusic, -1);
	LoadMap(lvl);
	Rules();

	checkLinks();
	ismoving = false;
	andmov = true;
}

void Game::update()
{
	world->update();
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);

	world->render();
	SDL_RenderPresent(renderer);
}
void Game::events()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (!ismoving)
		{
 			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
				List::move(8);
				ismoving = true;
				break;
			case SDLK_DOWN:
				List::move(24);
				ismoving = true;
				break;
			case SDLK_LEFT:
				List::move(16);
				ismoving = true;
				break;
			case SDLK_RIGHT:
				List::move(0);
				ismoving = true;
				break;
			case SDLK_SPACE:
				// create wait
				ismoving = true;
				break;
			case SDLK_r:
				clear();
				LoadMap(lvl);
				checkLinks();
				Rules();
			}
			if (erasefg)
			{
				highlight();
				erasefg = false;
			}
			if (ismoving)
			{
				if (!destroy->me->empty())
					destruct();
				Rules();
				if (flags::tex) {
					checkLinks();
					flags::tex = false;
				}
				if (checkwin())
				{
					lvl >= 8 ? lvl = 1:lvl++;
					clear();
					LoadMap(lvl);
					checkLinks();
					Rules();
				}
			}
		}
		break;
	}
}
void Game::clear()
{
	Map::List::me->clear();
	world->me->clear();
	direct->me->clear();
	activelist->clear();
	textis->me->clear();
	textatr->me->clear();
	textob->me->clear();
	ob->me->clear();
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 28; j++)
			objmap[i][j]->me->clear();
	flags::ismoving = false;
	flags::andmov = true;
	flags::remove = false;
	flags::rec = false;
	flags::tex = false;
	flags::active = false;
	flags::erasefg = false;
}

void Game::close()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
	Mix_FreeMusic(gMusic);
	gMusic = NULL;
	activelist->clear();
	IMG_Quit();
	SDL_Quit();
}

void Game::highlight()
{
	SDL_Color* c = new SDL_Color;
	for (std::list<object*>::iterator it = activelist->begin(),it1=it; it != activelist->end(); it=it1)
	{
		it1++;
		if (!(*it)->isActive)
		{
			(*it)->isActive=true;
			(*it)->col += 7;
			c = hex2sdl(hexcolor[(*it)->col]);
			(*it)->changeObjColor(c->r, c->g, c->b);
		}
		else
			if (!active)
			{
				(*it)->isActive = false;
				(*it)->col -= 7;
				c = hex2sdl(hexcolor[(*it)->col]);
				(*it)->changeObjColor(c->r, c->g, c->b);
				if ((*it)->isTextofObj)
				{
					std::string str = (*it)->name;
					str.erase(0, 5);
					if (str != "")
					{
						erase(str);
					}
				}
				activelist->erase(it);
			}
	}
}