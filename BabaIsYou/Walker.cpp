#include "Walker.h"

void Walker::changeTexture(int dir, int step)
{
	object::changeTexture(dir, step<0?step:0);
}