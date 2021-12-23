#include "Game.h"

//Screen dimension constants
const int SCREEN_WIDTH = 672;
const int SCREEN_HEIGHT = 24 * 16;

int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int fameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	Game* game = new Game();
	game->init("Baba is You", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT);

	while (game->getRunning())
	{
		frameStart = SDL_GetTicks();

		game->events();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (fameDelay > frameTime)
			SDL_Delay(fameDelay - frameTime);
	}
	game->close();
	return 0;
}