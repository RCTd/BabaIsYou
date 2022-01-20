#include "Map.h"
#include "name.h"
#include "Text.h"
#include "Walker.h"
#include "Directed.h"
#include "Thing.h"
#include <fstream>

SDL_Color* Map::hex2sdl(std::string input)
{
	if (input[0] == '#')
		input.erase(0, 1);
	unsigned long value = stoul(input, nullptr, 16);
	SDL_Color color;
	color.a = (value >> 24) & 0xff;
	color.r = (value >> 16) & 0xff;
	color.g = (value >> 8) & 0xff;
	color.b = (value >> 0) & 0xff;
	return &color;
}
Map::Map()
{
	world = new List();
	direct = new List();
	textis = new List();
	destroy = new List();
	ob = new List();
}

Map::~Map()
{
	free(objmap);
	world->me->clear();
	direct->me->clear();
	textis->me->clear();
	ob->me->clear();
}

bool Map::LoadMap(int lvl)
{
	try {
		std::string str = "Lvl" + std::to_string(lvl) + ".txt";
		std::ifstream in(str);
		int arr[16][28], col;
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 28; j++) {
				in >> arr[i][j];
			}
		}
		int color[16][28];
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 28; j++) {
				in >> color[i][j];
			}
		}
		int pos, dir;
		for (int row = 0; row < 16; row++)
		{
			for (int column = 0; column < 28; column++)
			{
				if (!objmap[row][column])
					objmap[row][column] = new List();
				if (arr[row][column])
				{
					if (arr[row][column] > 1091 || arr[row][column] < 0)
						throw SDL_GetError();
					str = nameobj[arr[row][column]];
					pos = str.find(".") + 1;
					dir = atoi(str.substr(pos, 2).c_str());
					pos--;
					str = str.substr(0, pos);
					col = color[row][column] - 1094 >= 0 ? (color[row][column] - 1094) : 21;
					newobject(str, column, row, dir, col);
				}
			}
		}
	}
	catch (const char* error)
	{
		SDL_Log("Eroare in creare lvl %s", error);
		return 1;
	}
	return 0;
}


bool nonatribute(std::string name)
{
	if (name != "text_you" && name != "text_word" && name != "text_win" && name != "text_weak" && name != "text_up" && name != "text_tele" && name != "text_swap"
		&& name != "text_stop" && name != "text_sink" && name != "text_shut" && name != "text_shift" && name != "text_right" && name != "text_red" && name != "text_push" && name != "text_pull" && name != "text_open" && name != "text_is"
		&& name != "text_move" && name != "text_more" && name != "text_melt" && name != "text_left" && name != "text_hot" && name != "text_float" && name != "text_fall" && name != "text_down" && name != "text_defeat" && name != "text_blue")
		return true;
	else
		return false;
}

void Map::newobject(std::string str,int column,int row,int dir,int col)
{
	SDL_Color* c;
	object* obj;
	bool flag = false;
	if (str == "skull" || str == "ghost" || str == "statue" || str == "belt" || str == "hand")
		obj = new Walker(str.c_str(), column * 24, row * 24, dir);
	else
		if (str == "baba" || str == "keke" || str == "me")
			obj = new object(str.c_str(), column * 24, row * 24, dir);
		else
			if (str == "brick" || str == "cliff" || str == "cloud" || str == "fence" || str == "grass" || str == "hedge" || str == "ice" || str == "wall" || str == "water")
			{
				obj = new Directed(str.c_str(), column * 24, row * 24, dir);
				direct->addObj(obj);
			}
			else
				if (str.find("text") != std::string::npos)
				{
					obj = new Text(str.c_str(), column * 24, row * 24);
					flag = true;
				}
				else
					obj = new Thing(str.c_str(), column * 24, row * 24);
	
	obj->col = col;
	c = hex2sdl(hexcolor[obj->col]);
	obj->changeObjColor(c->r, c->g, c->b);
	objmap[row][column]->addObj(obj);
	world->addObj(obj);

	if (flag)
	{
		if (obj->name == "text_is")
			textis->addObj(obj);
		else
			if (nonatribute(obj->name))
				obj->isTextofObj = true;
			else
				obj->isatribute = true;
		flag = false;
	}
	else
	{
		colindexname.push_back(obj->name);
		colindexlist.push_back(obj->col);
		ob->addObj(obj);
	}
	c=nullptr;
	obj = nullptr;
	delete(c);
	delete(obj);
}

