#include "Game.h"
#include "Map.h"
#include "Object.h"
#include "TextureManager.h"
#include "EntitySystem.h"
#include "Components.h"


object* player, * is;
Map* map;
SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& newPlayer(manager.addEntity());

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
	player = new object("baba", 0, 0);
	player->makeYou(true);
	is = new object("text_is", 0, 24);
	is->makeYou(true);
	map = new Map();

	newPlayer.addComponent<PositionComponent>();
}

void Game::update()
{
	player->update();
	is->update();
	manager.update();
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);
	map->DrawMap();
	player->render();
	is->render();
	//desen


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
				ismoving = true;
				break;
			case SDLK_DOWN:
				ismoving = true;
				break;
			case SDLK_LEFT:

				ismoving = true;
				break;
			case SDLK_RIGHT:
				ismoving = true;
				player->incX();
				break;
			}

	default:
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