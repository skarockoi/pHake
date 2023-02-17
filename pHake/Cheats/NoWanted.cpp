#include "../globals.hpp"
#include "../pLib/pHake.hpp"

#include "NoWanted.hpp"

NoWanted::NoWanted(std::shared_ptr<pHake> phake) : pCheatLoop(phake)
{
	name_ = "NoWanted";
	thread_intervals_ = 10;
	active = &settings.nowanted;
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