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
void List::removeObj(object* o)
{
	me->remove(o);
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
	//baba and rock is you, rock is push problem
	bool succes = true;
	for (std::list<object*>::iterator it = me->begin(), it1 = it; (!me->empty()) && it != me->end(); it = it1)
	{
		++it1;
		if((*it)->isYou&&((!flags::rec&&!(*it)->ismov)||(flags::rec&&(*it)->isStop)))
			succes &= (*it)->move(dir);
		else
			if((*it)->isPush&&flags::rec&&!(*it)->isYou)
				succes &= (*it)->move(dir);
			else
			if ((*it)->isStop)
				succes = false;
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
			if((*it)->find(sign))
				Game::activelist->push_front((*it));
			return true;
		}
	}
	return false;
}

std::string List::ret()
{
	for (std::list<object*>::iterator it = me->begin(); it != me->end(); ++it)
		if ((*it)->isTextofObj)
		{
			flags::active = true;
			Game::activelist->push_back(*it);
			std::string str = (*it)->name;
			str.erase(0, 5);
			return str;
		}
	return "";
}
