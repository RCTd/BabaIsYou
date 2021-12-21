#include "Game.h"
#include "Directed.h"

int Directed::neighbours(int i,int j)
{
	int d = 0;
	if (j > 0 && !Map::objmap[j - 1][i]->me->empty() && Map::objmap[j - 1][i]->find(this->name.c_str(),0))
	{
		d += 2;
	}
	if (i < 27 && !Map::objmap[j][i + 1]->me->empty() && Map::objmap[j][i + 1]->find(this->name.c_str(),0))
	{
		d ++;
	}
	if (j <15 && !Map::objmap[j + 1][i]->me->empty() && Map::objmap[j + 1][i]->find(this->name.c_str(),0))
	{
		d += 8;
	}
	if (i > 0 && !Map::objmap[j][i - 1]->me->empty() && Map::objmap[j][i - 1]->find(this->name.c_str(),0))
	{
		d += 4;
	}
	return d;
}

void Directed::changeTexture(int dir, int step)
{
	int d = 0;
	int i = GetX() / 24;
	int j = GetY() / 24;
	
	switch (dir)
	{
	case 8:
		d = neighbours(i, j - 1);
		if (j ==0)
			return;
		if (i > 0)
		{
			if (!Map::objmap[j][i - 1]->me->empty())
				Map::objmap[j][i - 1]->find(this->name.c_str(), -1);
			if (!Map::objmap[j - 1][i - 1]->me->empty())
				Map::objmap[j - 1][i - 1]->find(this->name.c_str(), 1);
		}
		if(i<27)
		{
			if (!Map::objmap[j][i + 1]->me->empty())
				Map::objmap[j][i + 1]->find(this->name.c_str(), -4);
			if (!Map::objmap[j - 1][i + 1]->me->empty())
				Map::objmap[j - 1][i + 1]->find(this->name.c_str(), 4);
		}
		if(j>0+1)
			if (!Map::objmap[j-2][i]->me->empty())
				Map::objmap[j-2][i]->find(this->name.c_str(), 8);
		break;
	case 0:
		d = neighbours(i + 1, j);
		if (i==27)
			return;
		if (j > 0)
		{
			if (!Map::objmap[j-1][i]->me->empty())
				Map::objmap[j-1][i]->find(this->name.c_str(), -8);
			if (!Map::objmap[j - 1][i + 1]->me->empty())
				Map::objmap[j - 1][i + 1]->find(this->name.c_str(), 8);
		}
		if (j < 15)
		{
			if (!Map::objmap[j+1][i]->me->empty())
				Map::objmap[j+1][i]->find(this->name.c_str(), -2);
			if (!Map::objmap[j + 1][i + 1]->me->empty())
				Map::objmap[j + 1][i + 1]->find(this->name.c_str(), 2);
		}
		if (i <27-1)
			if (!Map::objmap[j][i+2]->me->empty())
				Map::objmap[j][i+2]->find(this->name.c_str(), 4);
		break;
	case 24:
		d = neighbours(i, j + 1);
		if (j ==15)
			return;
		if (i > 0)
		{
			if (!Map::objmap[j][i - 1]->me->empty())
				Map::objmap[j][i - 1]->find(this->name.c_str(), -1);
			if (!Map::objmap[j + 1][i - 1]->me->empty())
				Map::objmap[j + 1][i - 1]->find(this->name.c_str(), 1);
		}
		if (i < 27)
		{
			if (!Map::objmap[j][i + 1]->me->empty())
				Map::objmap[j][i + 1]->find(this->name.c_str(), -4);
			if (!Map::objmap[j + 1][i + 1]->me->empty())
				Map::objmap[j + 1][i + 1]->find(this->name.c_str(), 4);
		}
		if (j <15-1)
			if (!Map::objmap[j + 2][i]->me->empty())
				Map::objmap[j + 2][i]->find(this->name.c_str(), 2);
		break;
	case 16:
		d = neighbours(i - 1, j);
		if (i == 0)
			return;
		if (j > 0)
		{
			if (!Map::objmap[j - 1][i]->me->empty())
				Map::objmap[j - 1][i]->find(this->name.c_str(), -8);
			if (!Map::objmap[j - 1][i + 1]->me->empty())
				Map::objmap[j - 1][i + 1]->find(this->name.c_str(), 8);
		}
		if (j < 15)
		{
			if (!Map::objmap[j + 1][i]->me->empty())
				Map::objmap[j + 1][i]->find(this->name.c_str(), -2);
			if (!Map::objmap[j + 1][i + 1]->me->empty())
				Map::objmap[j + 1][i + 1]->find(this->name.c_str(), 2);
		}
		if (i < 27 - 1)
			if (!Map::objmap[j][i + 2]->me->empty())
				Map::objmap[j][i + 2]->find(this->name.c_str(), 1);
		break;

	}
	orient = d;
	object::changeTexture(d, 0);
}