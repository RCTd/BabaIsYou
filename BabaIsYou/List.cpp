#include "Game.h"
#include "Directed.h"
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
bool List::move(int dir)
{
	bool succes = true;
	for (std::list<object*>::iterator it = me->begin(), it1 = it; (!me->empty()) && it != me->end(); it = it1)
	{
		++it1;
		if ((*it)->isStop)
			succes = false;
		else
			if((*it)->isPush||((*it)->isYou&&!(*it)->ismov))
				succes&=(*it)->move(dir);
	}
	return succes;
}
void List::render()
{
	for (std::list<object*>::iterator it = me->begin(); it != me->end(); ++it)
		(*it)->render();
}

bool List::find(const char* name,int sign)
{
	for (std::list<object*>::iterator it = me->begin(); it != me->end(); ++it)
	{
		if ((*it)->name == name)
		{
			if(sign<0)
				(*it)->orient ^= abs(sign);
			else
				(*it)->orient |= sign;
			(*it)->object::changeTexture((*it)->orient, 0);
			return true;
			break;
		}
	}
	return false;
}