#pragma once
#include"List.h"

class Map :public List
{
public:
	static SDL_Color* hex2sdl(std::string input);
	Map();
	~Map();

	void LoadMap(int lvl);
	static List* objmap[16][28];
protected:
	SDL_Rect src, dest;
	List* world;
	List* direct;
	List* textis,*textatr,*textob,*ob;
};

