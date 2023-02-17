#include "../globals.hpp"
#include "../pLib/pHake.hpp"

#include "RPLoop.hpp"



RPLoop::RPLoop(std::shared_ptr<pHake> phake) : pCheatLoop(phake)
{
	name_ = "RPLoop";
	thread_intervals_ = 1;
	active = &settings.rploop;
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
