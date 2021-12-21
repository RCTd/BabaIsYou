#include "Game.h"
#include <fstream>

SDL_Renderer* Game::renderer = nullptr;
bool flags::ismoving = false;
bool flags::andmov = true;
bool flags::remove = false;
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
	LoadMap(lvl);
	player = (*objmap[7][9]->me->begin());
	//player = (*objmap[11][16]->me->begin());

	player->changeObjColor(255, 20, 150);
	addObj(player);

	ismoving = false;
	andmov = true;
}

void Game::update()
{
	world->update();
	//List::update();
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);

	world->render();
	List::render();
	SDL_RenderPresent(renderer);
}
void Game::events()
{
	SDL_PollEvent(&event);
	/*if(remove!=ismoving)
		std::cout << ismoving << "\n";
	remove = ismoving;*/
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (!ismoving)
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

