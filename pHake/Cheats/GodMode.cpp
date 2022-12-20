#include "../Globals.hpp"

#include "GodMode.hpp"

GodMode::GodMode()
{
	thread_intervals_ = 100;
}

void GodMode::Execute()
{

	if (settings.godmode)
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
	world.localplayer.god(false);
}