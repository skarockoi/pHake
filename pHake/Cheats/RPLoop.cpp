#include "../Globals.hpp"

#include "RPLoop.hpp"

RPLoop::RPLoop()
{
	thread_intervals = 1;
	menu->list.AddBool("RPloop", settings.rploop);
}

void RPLoop::execute()
{
	if (!settings.rploop)
		return;

	world.localplayer.playerinfo.wanted_level(5);
	world.localplayer.playerinfo.wanted_level(0);
}

void RPLoop::restore()
{
}
