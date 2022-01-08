#pragma once
#include "Flags.h"
#include "Map.h"
#include <SDL_mixer.h>
class Game :public flags, public Map {
private:
	bool isRunning = false;
	int lvl=1;
	SDL_Rect destRect, srcRect;
	Mix_Music* gMusic = NULL;
	SDL_Window* window;
	SDL_Event event;
public:
	static std::list<object*> *activelist;
	static SDL_Renderer* renderer;
	Game() :window(NULL), event({ 0 }) 
		{ srcRect.x = 0; srcRect.y = 0; srcRect.h = 24; destRect.x = 12 * 24;
		destRect.y = 10; destRect.w = 60; destRect.h = 30; srcRect.w = 48;}
	void init(const char* Windowtitle, int x, int y, int w, int h);
	void update();
	void events();
	void clear();
	void render();
	void close();
	inline bool getRunning() { return isRunning; }
	bool checkwin();

	bool checkMelt();

	void highlight();
	void Rules();
	void thisIsthis(const char* name1, const char* name2);
	void erase(std::string str);
	void destruct();
	void action(std::string name, std::string name2);
	void forground();
	void checkLinks();

};