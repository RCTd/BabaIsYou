#include "Game.h"
#include <cmath>

List::List()
{
	me = new std::list<object*>;
}
List::~List()
{
	me->clear();
}
void List::addObj(object* o)
{
	me->push_back(o);
}
void List::update()
{
	flags::andmov = false;
	for (std::list<object*>::iterator it = me->begin(); it != me->end(); ++it)
	{

		(*it)->update();
		flags::andmov = flags::andmov || (*it)->ismov;
	}
	flags::ismoving = flags::andmov;
}
void List::move(int dir)
{
	for (std::list<object*>::iterator it = me->begin(), it1 = it; (!me->empty()) && it != me->end(); it = it1)
	{
		++it1;
		(*it)->pushnext(dir);
	}
}
void List::render()
{
	for (std::list<object*>::iterator it = me->begin(); it != me->end(); ++it)
		(*it)->render();
}