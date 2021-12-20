#pragma once
#include "Object.h"
#include <list>

class You
{
private:
	std::list<object*> me;
	int nobj = 0;
	int dir;
public:
	You();
	~You();
	void addObj(object* o);
};

You::You()
{

}