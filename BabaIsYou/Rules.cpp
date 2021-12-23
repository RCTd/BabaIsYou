#include "Game.h"

void Game::stop(const char* name,bool state)
{
	for (std::list<object*>::iterator it = world->me->begin();it != world->me->end(); ++it)
	{
		if ((*it)->name == name)
			(*it)->isStop = state;
	}
}

void Game::push(const char* name, bool state)
{
	for (std::list<object*>::iterator it = world->me->begin(); it != world->me->end(); ++it)
	{
		if ((*it)->name == name)
			(*it)->isPush = state;
	}
}

void Game::checkLinks()
{
	for (std::list<object*>::iterator it = world->me->begin(); it != world->me->end(); ++it)
	{
		(*it)->changeTexture(-1, -1);
	}
}
void Game::makeYou(const char* name,bool state)
{
	for (std::list<object*>::iterator it = world->me->begin(); it != world->me->end(); ++it)
	{
		if ((*it)->name == name)
		{
			(*it)->isYou = state;
			addObj((*it));
			(*it)->changeObjColor(255, 20, 150);
		}
	}
}

void Game::Rules()
{
	for (std::list<object*>::iterator it = world->me->begin(); it != world->me->end(); ++it)
	{
		
	}
}

void Game::thisIsthis(const char* name1, const char* name2)
{
	for (std::list<object*>::iterator it = world->me->begin(); it != world->me->end(); ++it)
	{
		if ((*it)->name == name1)
		{
			int x = (*it)->GetX(), y = (*it)->GetY();

			(*it)->name = name2;
			(*it)->changeTexture(0, -1);

		}
	}
}