#include "Game.h"

void Game::forground()
{
int i = 0;
	for (std::list<object*>::iterator it = world->me->begin(), it1 = it; i < world->me->size() && it != world->me->end(); it=it1, i++)
	{
 		it1 = it; it1++;
		if ((*it)->isPush || (*it)->isYou)
		{
			world->me->push_back((*it));
			world->me->erase(it);
		}
	}
}

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
	for (std::list<object*>::iterator it = world->me->begin(),it1=it;it != world->me->end(); it=it1)
	{
		++it1;
		if ((*it)->name == name)
		{
			(*it)->isPush = state;
		}
	}
}

void Game::checkLinks()
{
	for (std::list<object*>::iterator it = direct->me->begin(); it != direct->me->end(); ++it)
	{
		(*it)->changeTexture(-1, -1);
	}
}
void Game::makeYou(const char* name,bool state)
{
	for (std::list<object*>::iterator it = world->me->begin(),it1=it;it != world->me->end(); it=it1)
	{
		++it1;
		if ((*it)->name == name)
		{
			(*it)->isYou = state;
			addObj((*it));
		}
	}
}

void Game::Rules()
{
	for (std::list<object*>::iterator it = world->me->begin(); it != world->me->end(); ++it)
	{
		if ((*it)->name == "text_you")
		{

		}
	}
	stop("wall", true);
	makeYou("wall", true);
	push("rock", true);
	push("skull", true);
	forground();
}

void Game::thisIsthis(const char* name1, const char* name2)
{
	for (std::list<object*>::iterator it = world->me->begin(); it != world->me->end(); ++it)
	{
		if ((*it)->name == name1)
		{
			int x = (*it)->GetX(), y = (*it)->GetY();


		}
	}
}

/*to do:
make rules reader,make thisIsthis
 
 
 */
