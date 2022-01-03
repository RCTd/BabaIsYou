#include "Game.h"
#include <fstream>
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
std::list<object*> *Game::activelist = new std::list<object*>;
List* Map::objmap[16][28] = { nullptr };
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
				isRunning = true;
			}
		}
	}
	else
	{
		SDL_Log("INIT ERROR %s\n", SDL_GetError());
	}
	std::ifstream in("Lvl1.txt");
	int lvl[16][28];
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 28; j++) {
			in >> lvl[i][j];
		}
	}
	int lvlcolor[16][28];
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 28; j++) {
			in >> lvlcolor[i][j];
		}
	}
	LoadMap(lvl,lvlcolor);
	Rules();

	/*keke = new Directed("wall", 5*24, 6*24, 0);
	objmap[6][5]->addObj(keke);
	world->addObj(keke);
	push("wall",true);
	push("baba", true);*/
	//makeYou("keke",true);

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

				ismoving = true;
				break;
			}
			if (erasefg)
			{
				highlight();
				erasefg = false;
			}
			if (ismoving)
			{
				Rules();
				if (flags::tex) {
					checkLinks();
					flags::tex = false;
				}
			}
		}
		break;
	}
}
void Game::close()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

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
						/*erasefg = true;*/
					{
						erase(str);
						//makeYou(str.c_str(), 0);
					}
				}
				activelist->erase(it);
			}
	}
}