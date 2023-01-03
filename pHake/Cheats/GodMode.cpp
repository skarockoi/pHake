#include "../globals.hpp"

#include "GodMode.hpp"

using namespace globals;

GodMode::GodMode()
{
	name_ = "GodMode";
	thread_intervals_ = 100;
	active = &settings.godmode;

	settings.godmode = ini->Get<bool>("Godmode", 0);
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
	ini->Edit<bool>("Godmode", settings.godmode);

	if (world.localplayer.god())
		world.localplayer.god(false);
}