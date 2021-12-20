#pragma once
#include "Flags.h"
#include "Map.h"

class Game :public flags, public Map {
private:
	bool isRunning = false;
	int cnt = 0;

	SDL_Window* window;
	SDL_Event event;
public:
	object* player;

	static SDL_Renderer* renderer;
	Game() :window(NULL), event({ 0 }) {
		player = nullptr;
	}
	void init(const char* Windowtitle, int x, int y, int w, int h);
	void update();
	void events();
	void render();
	void close();
	inline bool getRunning() { return isRunning; }
};