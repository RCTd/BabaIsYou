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
	//object* player,*keke;
	static std::list<object*> *activelist;

	static SDL_Renderer* renderer;
	Game() :window(NULL), event({ 0 }) {}
	void init(const char* Windowtitle, int x, int y, int w, int h);
	void update();
	void events();
	void render();
	void close();
	inline bool getRunning() { return isRunning; }

	void highlight();
	void Rules();
	void thisIsthis(const char* name1, const char* name2);
	void erase(std::string str);
	void makeYou(const char* name, bool state);
	void forground();
	void stop(const char* name,bool state);
	void win(const char* name, bool state);
	void push(const char* name, bool state);
	void checkLinks();

};