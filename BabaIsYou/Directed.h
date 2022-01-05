#pragma once
#include "Object.h"

class Directed:public object
{
public:
	Directed(const char* name, int x, int y, int dir) :object(name, x, y, dir) { orient = 0; isdirected = true; };
	void changeTexture(int dir, int step);
	int neighbours(int i, int j,int dir);
	bool find(int sign);
};
