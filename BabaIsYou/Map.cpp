#include "Map.h"
#include "name.h"
#include "Text.h"
#include "Walker.h"
#include "Directed.h"
#include "Thing.h"

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

	src.x = 0;
	src.y = 0;
	src.w = 24;
	src.h = 24;
	dest.x = 0;
	dest.y = 0;
	dest.w = 24;
	dest.h = 24;

}

Map::~Map()
{
	free(objmap);
}

void Map::LoadMap(int arr[16][28],int color[16][28])
{
	SDL_Color* c;
	object* obj;
	std::string str;
	int pos, dir;
	for (int row = 0; row < 16; row++)
	{
		for (int column = 0; column < 28; column++)
		{
			if (!objmap[row][column])
				objmap[row][column] = new List();
			if (arr[row][column])
			{
				str = nameobj[arr[row][column]];
				pos = str.find(".") + 1;
				dir = atoi(str.substr(pos, 2).c_str());
				pos--;
				str = str.substr(0, pos);
				if(str=="skull"|| str == "ghost" || str == "statue" || str == "belt" || str == "hand"  )
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
					obj = new Text(str.c_str(), column * 24, row * 24);
				else
					obj = new Thing(str.c_str(), column * 24, row * 24);

				obj->col = color[row][column] - 1094 >= 0 ? (color[row][column] - 1094) : 21;
				c = hex2sdl(hexcolor[obj->col]);
				obj->changeObjColor(c->r, c->g, c->b);
				objmap[row][column]->addObj(obj);
				world->addObj(obj);
			}
		}
	}
}

