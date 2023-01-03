#include "../globals.hpp"

#include "RPLoop.hpp"

using namespace globals;

RPLoop::RPLoop()
{
	thread_intervals_ = 1;

	settings.rploop = ini->Get<bool>("RpLoop", 0);
}

void RPLoop::Execute()
{
	if (!settings.rploop)
		return;

	world.localplayer.playerinfo.wanted_level(5);
	world.localplayer.playerinfo.wanted_level(0);
}

void RPLoop::Restore()
{
	ini->Edit<bool>("RpLoop", settings.rploop);
}
