#pragma once
#include "Object.h"

class Text:public object
{
public:
	Text(const char* name, int x, int y);
	bool find(int sign) { return true; }
	void changeTexture(int dir, int step);
private:

};
