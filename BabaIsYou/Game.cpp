#include "Game.h"
#include <fstream>

//object* keke;
SDL_Renderer* Game::renderer = nullptr;
bool flags::ismoving = false;
bool flags::andmov = true;
bool flags::remove = false;
bool flags::rec = false;
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
	std::ifstream in("Lvl5.txt");
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
	checkLinks();

	/*keke = new object("keke", 9*24, 6*24, 8);
	objmap[6][9]->addObj(keke);
	world->addObj(keke);*/

	stop("wall", true);
	makeYou("baba",true);
	push("rock", true);
	push("skull", true);
	//makeYou("keke",true);
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
	List::render();
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

