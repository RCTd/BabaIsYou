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