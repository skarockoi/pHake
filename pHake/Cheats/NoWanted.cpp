#include "../Globals.hpp"

#include "NoWanted.hpp"

NoWanted::NoWanted()
{
	thread_intervals = 10;
	menu->list.AddBool("NoWanted", settings.nowanted);
}

void NoWanted::execute() {
	if (world.localplayer.playerinfo.wanted_level() != 0)
		world.localplayer.playerinfo.wanted_level(0);
}

void NoWanted::restore()
{
	if (settings.rploop)
		world.localplayer.playerinfo.wanted_level(0);
}