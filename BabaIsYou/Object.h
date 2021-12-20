#pragma once
#include <string>
#include "TextureManager.h"
#define framespeed 2
class object {
private:
	int x, y;
	//std::string name;
	bool isYou = false, hasdir = false;
	std::string name;
	//// 0-up 1-right 2-down 3-left 
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	int frame = 0, direction = 0, step = 0;
	SDL_Color color;
public:
	int a;
	bool ismov = false;
	void init();
	void changeObjColor(int red, int green, int blue) {
		color.r = red;
		color.g = green;
		color.b = blue;
		SDL_SetTextureColorMod(objTexture, red, green, blue);
	}
	bool pushnext(int dir);
	void makeYou(bool a) { isYou = a ? a : !a; }
	object(const char* name, int x, int y);
	object(const char* name, int x, int y, int dir);
	~object();
	bool move(int dir);
	void changeTexture(int dir, int step);
	void setDirection(int dir) { direction = dir; }
	void incX() { x += framespeed; }
	void incY() { y += framespeed; }
	void decX() { x -= framespeed; }
	void decY() { y -= framespeed; }
	bool hasDir() { return hasdir; }
	int getStep() { step = (step < 3) ? step + 1 : 0; return step; }
	int getY() { return y; }
	int getX() { return x; }
	void update();
	void render();
};


/*
D\fr      0   1    2     3  sit
right:    0   1    2     3   31
up:       8   9   10    11    7
left:     16  17  18    19   15
down:     24  25  26    27   23

neighbor:
	noone:	0
	right:	1
	up:		2
	up-r	3
	left:	4
	left-r:	5
	left-u:	6
	l-u-r:	7
	down:	8
	down-r:	9
	down-u:	10
	d-u-r:	11
	down-l:	12
	d-l-r:	13
	d-l-u:	14
	all:	15

	 	     10
		  7   7   7 
	 14   6   2   3  11
  5  14   4   0   1  11  5
	 14  12   8   9  11
	     13  13  13
		     10 

with direction:
	baba
	keke
	me

depends on others:
	belt
	brick
	cliff
	cloud
	fence
	grass
	hedge
	ice
	wall
	water
	*/
