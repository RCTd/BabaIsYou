#pragma once
#include "Object.h"

class Thing :public object
{
public:
	Thing(const char* name, int x, int y) :object(name, x, y) {  };
	void changeTexture(int dir, int step);
};
