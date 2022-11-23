#include "../Globals.hpp"

#include "NoWanted.hpp"

NoWanted::NoWanted()
{
	thread_intervals_ = 10;
	menu->list.AddBool("NoWanted", settings.nowanted);
}

void NoWanted::Execute() {
	if (world.localplayer.playerinfo.wanted_level() != 0)
		world.localplayer.playerinfo.wanted_level(0);
}

void NoWanted::Restore()
{
	if (settings.rploop)
		world.localplayer.playerinfo.wanted_level(0);
}