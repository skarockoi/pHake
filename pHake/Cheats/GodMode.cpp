#include "../Globals.hpp"

#include "GodMode.hpp"

GodMode::GodMode()
{
	thread_intervals = 100;
	menu->list.AddBool("GodMode", settings.godmode);
}

void GodMode::execute()
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

void GodMode::restore()
{
	if (settings.godmode)
		world.localplayer.god(false);
}