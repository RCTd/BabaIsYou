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
				return true;
			return true;
		}
	}
	return false;
}
bool name(std::string name)
{
	if (name != "text_you" && name != "text_word" && name != "text_win" && name != "text_weak" && name != "text_up" && name != "text_tele" && name != "text_swap"
		&& name != "text_stop" && name != "text_sink" && name != "text_shut" && name != "text_shift" && name != "text_right" && name != "text_red" && name != "text_push" && name != "text_pull" && name != "text_open"&& name!="text_is"
		&& name != "text_move" && name != "text_more" && name != "text_melt" && name != "text_left" && name != "text_hot" && name != "text_float" && name != "text_fall" && name != "text_down" && name != "text_defeat" && name != "text_blue")
		return true;
	else
		return false;
}
std::string List::ret()
{
	for (std::list<object*>::iterator it = me->begin(); it != me->end(); ++it)
		if (name((*it)->name) && (*it)->name.find("text") != std::string::npos)
		{
			flags::active = true;
			std::string str = (*it)->name;
			str.erase(0, 5);
			return str;
		}
	return "";
}
