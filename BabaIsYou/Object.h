#pragma once
#include <string>
#include "TextureManager.h"
#define framespeed 2
class object {
public:
	std::string name;
private:
	int x, y;
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	int frame , step = 0;
	SDL_Color color;
public:
	int i, j,col=0;
	int a, direction = 0,orient=0;
	bool isYou = false;
	bool isPush = false;
	bool isStop = false;
	bool ismov = false;
	bool isWin = false;
	bool isActive = false;
	bool isdirected = false;
	bool isdefeat = false;
	bool issink = false;
	bool isTextofObj = false;
	bool isatribute = false;
	bool ishot = false;
	bool ismelt = false;
	void init();
	void changeObjColor(int red, int green, int blue) {
		color.r = red;
		color.g = green;
		color.b = blue;
		SDL_SetTextureColorMod(objTexture, color.r, color.g, color.b);
	}
	bool pushnext(int dir);
	object(const char* name, int x, int y);
	object(const char* name, int x, int y, int dir);
	~object();
	bool move(int dir);
	virtual void changeTexture(int dir, int step);
	virtual bool find(int sign) { return false; }
	void incX() { x += framespeed; i ++; }
	void incY() { y += framespeed; j ++; }
	void decX() { x -= framespeed; i --; }
	void decY() { y -= framespeed; j --; }
	int GetX() { return x; }
	int GetY() { return y; }
	int getStep() { step = (step < 3) ? step + 1 : 0; return step; }
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

     dlur
	 0000

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

/*atributes:
text_you
text_word
text_win
text_weak
text_up
text_tele
text_swap
text_stop
text_sink
text_shut
text_shift
text_right
text_red
text_push
text_pull
text_open
text_move
text_more
text_melt
text_left
text_hot
text_float
text_fall
text_down
text_defeat
text_blue
*/