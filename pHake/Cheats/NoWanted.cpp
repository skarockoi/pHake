#include "../Globals.hpp"

#include "NoWanted.hpp"

NoWanted::NoWanted()
{
	thread_intervals_ = 10;

	settings.nowanted = ini->Get<bool>("NoWanted", 0);
}

void NoWanted::Execute() {
	if (world.localplayer.playerinfo.wanted_level() != 0)
		world.localplayer.playerinfo.wanted_level(0);
}

void NoWanted::Restore()
{
	ini->Edit<bool>("NoWanted", settings.nowanted);

	if (*active)
		world.localplayer.playerinfo.wanted_level(0);
}