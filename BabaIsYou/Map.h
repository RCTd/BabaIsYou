#pragma once
#include"List.h"

class Map :public List
{
public:
	static SDL_Color* hex2sdl(std::string input);
	std::list<int> colindexlist;
	std::list<std::string> colindexname;
	Map();
	~Map();

	void newobject(std::string str, int column, int row, int dir,int col);

	void LoadMap(int lvl);
	static List* objmap[16][28];
	static List* destroy;
protected:
	SDL_Rect src, dest;
	List* world;
	List* direct;
	List* textis,*ob;
};

