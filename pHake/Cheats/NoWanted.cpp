#include "../globals.hpp"
#include "../pHake.hpp"

#include "NoWanted.hpp"

using namespace globals;



NoWanted::NoWanted(std::shared_ptr<pHake> phake) : CheatLoop(phake)
{
	thread_intervals_ = 10;
}

void NoWanted::Execute() {
	if (world.localplayer.playerinfo.wanted_level() != 0)
		world.localplayer.playerinfo.wanted_level(0);
}

void NoWanted::Restore()
{

	if (*active)
		world.localplayer.playerinfo.wanted_level(0);
}