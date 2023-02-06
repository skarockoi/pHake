#include "../globals.hpp"
#include "../pHake.hpp"

#include "RPLoop.hpp"

using namespace globals;

RPLoop::RPLoop(pHake& phake) : CheatLoop(phake)
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
