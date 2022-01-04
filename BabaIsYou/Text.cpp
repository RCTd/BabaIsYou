#include "Text.h"

//bool nonatribute(std::string name)
//{
//	if (name != "text_you" && name != "text_word" && name != "text_win" && name != "text_weak" && name != "text_up" && name != "text_tele" && name != "text_swap"
//		&& name != "text_stop" && name != "text_sink" && name != "text_shut" && name != "text_shift" && name != "text_right" && name != "text_red" && name != "text_push" && name != "text_pull" && name != "text_open" && name != "text_is"
//		&& name != "text_move" && name != "text_more" && name != "text_melt" && name != "text_left" && name != "text_hot" && name != "text_float" && name != "text_fall" && name != "text_down" && name != "text_defeat" && name != "text_blue")
//		return true;
//	else
//		return false;
//}
Text::Text(const char* name, int x, int y) :object(name, x, y)
{
	/*if (nonatribute(name))
	{
		isTextofObj = true;
	}*/
	isPush = true; 
}

void Text::changeTexture(int dir, int step)
{
	object::changeTexture(dir, -1);
}
