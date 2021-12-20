#pragma once
#include <SDL.h>
#include <SDL_image.h>


class Game {
private:
	bool isRunning = false;
	int cnt = 0;

	SDL_Window* window;
	SDL_Event event;
public:

	static SDL_Renderer* renderer;
	Game() :window(NULL), event({ 0 }) {}
	//functii
	void init(const char* Windowtitle, int x, int y, int w, int h);
	void update();
	void events();
	void render();
	void close();
	inline bool getRunning() { return isRunning; }
};