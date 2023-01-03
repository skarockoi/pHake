#include "../Globals.hpp"

#include "Suicide.hpp"

Suicide::Suicide()
{
}

void Suicide::Execute()
{
	world.localplayer.health(0.f);
	menu->notification.Add("Player health set to 0");
}

void Suicide::Restore()
{
}
