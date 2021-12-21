#include "Map.h"
#include "name.h"
#include "Text.h"
#include "Walker.h"
#include "Directed.h"

Map::Map()
{
	world = new List();

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

void Map::LoadMap(int arr[16][28])
{
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
				str = name[arr[row][column] - 1093];
				pos = str.find(".") + 1;
				dir = atoi(str.substr(pos, 1).c_str());
				pos--;
				str = str.substr(0, pos);

				if (str == "baba" || str == "keke" || str == "me")
					obj = new Walker(str.c_str(), column * 24, row * 24, dir);
				else
				if(str == "brick" || str == "cliff" || str == "cloud" || str == "fence" || str == "grass" || str == "hedge" || str == "ice" || str == "wall" || str == "water")
					obj = new Directed(str.c_str(), column * 24, row * 24,dir);
				else
					obj = new Text(str.c_str(), column * 24, row * 24);
				objmap[row][column]->addObj(obj);
				world->addObj(obj);
			}
		}
	}
}
