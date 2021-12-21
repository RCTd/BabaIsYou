#pragma once
#include "Object.h"

class Directed:public object
{
public:
	Directed(const char* name, int x, int y, int dir) :object(name, x, y, dir) { orient = dir; };
	//~Directed();
	void changeTexture(int dir, int step);
	int neighbours(int i, int j);
	//int type = 0;
};
