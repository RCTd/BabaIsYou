#pragma once
#include <string>
#include "Game.h"
class object {
private:
	int x, y;
	//std::string name;
	bool isYou = false;
	//// 0-up 1-right 2-down 3-left -1-noDirection
	//int direction;
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	int frame = 0;

public:
	//object():x(0),y(0),name(""), isYou(false), direction(-1) {}
	//object(int x, int y, std::string name );
	void makeYou(bool a) { isYou = a ? a : !a; }
	object(const char* name, int x, int y);
	~object();
	void incX() { x += 2; }
	void update();
	void render();
};