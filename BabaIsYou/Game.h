#pragma once
#include "Flags.h"
#include "Map.h"
#include <SDL_mixer.h>
class Game :public flags, public Map {
private:
	bool isRunning = false;
	int cnt = 0;
	int lvl=1;
	Mix_Music* gMusic = NULL;
	SDL_Window* window;
	SDL_Event event;
public:
	//object* player,*keke;
	static std::list<object*> *activelist;

	static SDL_Renderer* renderer;
	Game() :window(NULL), event({ 0 }) {}
	void init(const char* Windowtitle, int x, int y, int w, int h);
	void update();
	void events();
	void clear();
	void render();
	void close();
	inline bool getRunning() { return isRunning; }
	bool checkwin();

	void highlight();
	void Rules();
	void thisIsthis(const char* name1, const char* name2);
	void erase(std::string str);
	void destruct();
	void action(std::string name, std::string name2);
	void forground();
	void checkLinks();

};