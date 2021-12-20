#include "Map.h"
#include "TextureManager.h"
#include <string>

int lvl1[16][28] = {
	{0,0,0,0,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 },
	{0,0,0,0,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 },
	{0,0,0,0,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 },
	{0,0,0,0,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 },
	{0,0,0,0,0,0,0,0 ,1,1,1,1 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 },
	{0,0,0,0,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 },
	{0,0,0,0,0,0,0,0 ,0,0,0,0 ,2,2,2,2 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 },
	{0,0,0,0,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 },
	{0,0,0,0,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 },
	{0,0,0,0,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 },
	{0,0,0,0,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 },
	{0,0,0,0,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 },
	{0,0,0,0,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 },
	{0,0,0,0,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 },
	{0,0,0,0,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 },
	{0,0,0,0,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0 }
};


Map::Map()
{
	std::string str = "baba";
	str = "sprites/" + str + "_0_1" + ".png";
	const char* asset = str.c_str();
	dirt = TextureManager::LoadTexture(asset);
	grass = TextureManager::LoadTexture("sprites/wall_0_1.png");
	water = TextureManager::LoadTexture("sprites/text_baba.png");

	LoadMap(lvl1);

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

}

void Map::LoadMap(int arr[16][28])
{
	for (int row = 0; row < 16; row++)
	{
		for (int column = 0; column < 28; column++)
		{
			map[row][column] = arr[row][column];
		}
	}
}

void Map::DrawMap()
{
	int type = 0;
	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 25; column++)
		{
			type = map[row][column];

			dest.x = column * 24;
			dest.y = row * 24;
			switch (type)
			{
			case 0:
			{
				TextureManager::Draw(water, src, dest);
				break;
			}
			case 1:
			{
				TextureManager::Draw(grass, src, dest);
				break;
			}
			case 2:
			{
				TextureManager::Draw(dirt, src, dest);
				break;
			}
			default:
				TextureManager::Draw(water, src, dest);
				break;
			}
		}
	}
}