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
	bool move(int);
	bool find(const char* name,int sign);
};
