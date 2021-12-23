#pragma once
#include "Object.h"

class Text:public object
{
public:
	Text(const char* name, int x, int y) :object(name, x, y) { isPush = true; }
	void changeTexture(int dir, int step);
	void rule(){}
private:

};
