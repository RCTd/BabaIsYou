#pragma once
#include "Object.h"

class Text:public object
{
public:
	//Text();
	Text(const char* name, int x, int y) :object(name, x, y) { }
	//~Text();
	void changeTexture(int dir, int step);
	//int type = 1;
private:

};
