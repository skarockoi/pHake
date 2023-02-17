#include "../globals.hpp"
#include "../pLib/pHake.hpp"

#include "GodMode.hpp"

GodMode::GodMode(std::shared_ptr<pHake> phake) : pCheatLoop(phake)
{
	name_ = "GodMode";
	thread_intervals_ = 100;
	active = &settings.godmode;
}

void GodMode::Execute()
{
	if (*active)
	{
		if (!world.localplayer.god())
			world.localplayer.god(1);

		if (!world.localplayer.vehicle.god())
			world.localplayer.vehicle.god(1);
	}
	else
	{
		if (world.localplayer.god())
			world.localplayer.god(0);
		

		if (world.localplayer.vehicle.god())
			world.localplayer.vehicle.god(0);
	}
}

void GodMode::Restore()
{
	if (world.localplayer.god())
		world.localplayer.god(false);
}