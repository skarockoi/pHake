#include "../globals.hpp"

#include "RPLoop.hpp"

using namespace globals;

RPLoop::RPLoop() : pCheatLoop()
{
	name_ = "RPLoop";
	thread_intervals_ = 1;
	active = &settings.rploop;
}

void RPLoop::Execute()
{
	if (!*active)
		return;

	world.localplayer.playerinfo.wanted_level(5);
	world.localplayer.playerinfo.wanted_level(0);
}

void RPLoop::Restore()
{
}
