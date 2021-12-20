#pragma once
#include "Object.h"
#include <list>

class List
{
	//private:
public:
	std::list<object*>* me;
public:
	List();
	~List();
	void render();
	void addObj(object* o);
	void update();
	void move(int);
};
