#pragma once	
#include "Object.h"

class Walker:public object
{
public:
	Walker(const char* name,int x,int y,int dir):object(name,x,y,dir){ this->hasdir = true; }
	//~Walker();
	void changeTexture(int dir, int step);
	//int type = 2;
private:

};
