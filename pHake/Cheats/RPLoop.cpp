#include "../Globals.hpp"

#include "RPLoop.hpp"

RPLoop::RPLoop()
{
	thread_intervals_ = 1;
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
}