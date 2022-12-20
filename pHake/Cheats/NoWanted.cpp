#include "../Globals.hpp"

#include "NoWanted.hpp"

NoWanted::NoWanted()
{
	thread_intervals_ = 10;
}

void NoWanted::Execute() {
	if (world.localplayer.playerinfo.wanted_level() != 0)
		world.localplayer.playerinfo.wanted_level(0);
}

void NoWanted::Restore()
{
	world.localplayer.playerinfo.wanted_level(0);
}