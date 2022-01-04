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
	for (std::list<object*>::iterator it = ob->me->begin();it != ob->me->end(); ++it)
	{
		if ((*it)->name == name)
			(*it)->isStop = state;
	}
}
void Game::win(const char* name, bool state)
{
	for (std::list<object*>::iterator it = ob->me->begin(); it != ob->me->end(); ++it)
	{
		if ((*it)->name == name)
			(*it)->isWin = state;
	}
}

void Game::push(const char* name, bool state)
{
	for (std::list<object*>::iterator it = ob->me->begin();it != ob->me->end(); ++it)
	{
		if ((*it)->name == name)
			(*it)->isPush = state;
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
	for (std::list<object*>::iterator it = ob->me->begin(),it1=it;it != ob->me->end(); it=it1)
	{
		++it1;
		if ((*it)->name == name)
		{
			if (state) {
				if (!(*it)->isYou)
					addObj(*it);
			}
			else
				removeObj(*it);
			(*it)->isYou = state;
		}
	}
}

bool Game::checkwin()
{
	for (std::list<object*>::iterator it = me->begin();it != me->end(); it++)
	{
		for (std::list<object*>::iterator it1 = objmap[(*it)->j][(*it)->i]->me->begin(); it1 != objmap[(*it)->j][(*it)->i]->me->end(); it1++)
			if ((*it1)->isWin)
				return true;
	}
	return false;
}

void Game::Rules()
{
	//make rules based on text_it
	std::string str="";
	for (std::list<object*>::iterator it = textatr->me->begin(); it != textatr->me->end(); ++it)
	{
		if ((*it)->name == "text_you")
		{
			if ((*it)->i > 1 && Map::objmap[(*it)->j][(*it)->i - 1]->find("text_is", 0))
				str = Map::objmap[(*it)->j][(*it)->i - 2]->ret();
			if (str != "")makeYou(str.c_str(), true); str = "";
			if ((*it)->j > 1 && Map::objmap[(*it)->j - 1][(*it)->i]->find("text_is", 0))
				str = Map::objmap[(*it)->j-2][(*it)->i]->ret();
			if (str != "")makeYou(str.c_str(), true);
		}else if ((*it)->name == "text_push")
		{
			if ((*it)->i > 1 && Map::objmap[(*it)->j][(*it)->i - 1]->find("text_is", 0))
				str = Map::objmap[(*it)->j][(*it)->i - 2]->ret();
			if (str != "")push(str.c_str(), true); str = "";
			if ((*it)->j > 1 && Map::objmap[(*it)->j - 1][(*it)->i]->find("text_is", 0))
				str = Map::objmap[(*it)->j - 2][(*it)->i]->ret();
			if (str != "")push(str.c_str(), true);
		}else if ((*it)->name == "text_stop")
		{
			if ((*it)->i > 1 && Map::objmap[(*it)->j][(*it)->i - 1]->find("text_is", 0))
				str = Map::objmap[(*it)->j][(*it)->i - 2]->ret();
			if (str != "")stop(str.c_str(), true); str = "";
			if ((*it)->j > 1 && Map::objmap[(*it)->j - 1][(*it)->i]->find("text_is", 0))
				str = Map::objmap[(*it)->j - 2][(*it)->i]->ret();
			if (str != "")stop(str.c_str(), true);
		}
		else if ((*it)->name == "text_win")
		{
			if ((*it)->i > 1 && Map::objmap[(*it)->j][(*it)->i - 1]->find("text_is", 0))
				str = Map::objmap[(*it)->j][(*it)->i - 2]->ret();
			if (str != "")win(str.c_str(), true); str = "";
			if ((*it)->j > 1 && Map::objmap[(*it)->j - 1][(*it)->i]->find("text_is", 0))
				str = Map::objmap[(*it)->j - 2][(*it)->i]->ret();
			if (str != "")win(str.c_str(), true);
		}
		if (active)
		{
			activelist->push_back(*it);
			highlight();
			active = false;
		}
	}
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

void Game::erase(std::string str)
{
	for (std::list<object*>::iterator it = ob->me->begin(); it != ob->me->end(); ++it)
	{
		if ((*it)->name == str.c_str())
		{
			(*it)->isYou = false;
			(*it)->isPush = false;
			(*it)->isStop = false;
			(*it)->ismov = false;
			(*it)->isWin = false;
		}
	}
	me->clear();
}

/*
thisisthis
rules from text_is
stack for undo?
make level selector?

*/