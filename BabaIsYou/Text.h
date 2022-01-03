#pragma once
#include "Object.h"

class Text:public object
{
public:
	Text(const char* name, int x, int y) :object(name, x, y) { isPush = true; }
	bool find(int sign) { return true; }
private:

};
