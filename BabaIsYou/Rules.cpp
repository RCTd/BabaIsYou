#include "Game.h"

void Game::forground()
{
int i = 0;
	for (std::list<object*>::iterator it = world->me->begin(), it1 = it; i < world->me->size() && it != world->me->end(); it=it1, i++)
	{
 		it1++;
		if ((*it)->isPush || (*it)->isYou)
		{
			world->me->push_back((*it));
			world->me->erase(it);
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

void Game::action(std::string name,std::string name2)
{
	flags::active = false;
	for (std::list<object*>::iterator it = ob->me->begin(),it1=it;it != ob->me->end(); it=it1)
	{
		++it1;
		if ((*it)->name == name)
		{
			if (name2 == "text_push")
				(*it)->isPush = true;
			else
				if (name2 == "text_stop")
					(*it)->isStop = true;
				else
					if (name2 == "text_win")
						(*it)->isWin = true;
					else
						if (name2 == "text_defeat")
							(*it)->isdefeat = true;
						else
							if (name2 == "text_sink")
								(*it)->issink = true;
							else
								if (name2 == "text_you") {
									(*it)->isYou = true;
									addObj(*it);
								}
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
	std::string str="",str2="";
	activelist->clear();
	for (std::list<object*>::iterator it = textis->me->begin(); it != textis->me->end(); ++it)
	{
		if ((*it)->i > 0 && (*it)->i < 27)
		{
			activelist->push_front(*it);
			str = Map::objmap[(*it)->j][(*it)->i - 1]->ret();
			if (str != "")
				if (!flags::active) {
					str2 = Map::objmap[(*it)->j][(*it)->i + 1]->ret();
					if (str2 != "")
					{
						if (!flags::active)
							thisIsthis(str.c_str(), str2.c_str());
						else
							action(str, str2);
						goto jmp;
					}
					else
						activelist->remove(*activelist->begin());
				}else
					activelist->remove(*activelist->begin());
			activelist->remove(*activelist->begin());
		}
		jmp:
		if ((*it)->j > 0 && (*it)->j < 15)
		{
			activelist->push_front(*it);
			str = Map::objmap[(*it)->j - 1][(*it)->i]->ret();
			if (str != "")
				if (!flags::active) {
					str2 = Map::objmap[(*it)->j+1][(*it)->i]->ret();
					if (str2 != "")
					{
						if (!flags::active)
							thisIsthis(str.c_str(), str2.c_str());
						else
							action(str, str2);
						goto jmp1;
					}
					else
						activelist->remove(*activelist->begin());
				}
				else
					activelist->remove(*activelist->begin());
			activelist->erase(activelist->begin());
		}
		jmp1:
		active = true;
		highlight();
		active = false;
	}
	forground();
}

void Game::thisIsthis(const char* name1, const char* name2)
{
	for (std::list<object*>::iterator it = ob->me->begin(),it1=it; it != ob->me->end(); it=it1)
	{
		++it1;
		if ((*it)->name == name1)
		{
			int x = (*it)->i, y = (*it)->j,dir=(*it)->direction;
			destroy->addObj(*it);
			destruct();
			Map::newobject(name2, x, y, dir, flags::colindex);
		}
	}
	checkLinks();
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
			(*it)->isdefeat = false;
			(*it)->issink = false;
			(*it)->isActive = false;
		}
	}
	me->clear();
}

void Game::destruct()
{
	for (std::list<object*>::iterator it = destroy->me->begin(); it != destroy->me->end(); ++it)
	{
		objmap[(*it)->j][(*it)->i]->me->remove(*it);
		world->me->remove(*it);
		direct->me->remove(*it);
		activelist->remove(*it);
		textis->me->remove(*it);
		ob->me->remove(*it);
	}
	destroy->me->clear();
	checkLinks();
}

/*
thisisthis
stack for undo?
make level selector?

*/