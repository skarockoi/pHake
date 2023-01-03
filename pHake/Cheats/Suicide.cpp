#include "../globals.hpp"

#include "Suicide.hpp"

using namespace globals;

Suicide::Suicide(pHake& phake) : Cheat(phake)
{
}

void Suicide::Execute()
{
	world.localplayer.health(0.f);
	phake->menu->notification.Add("Player health set to 0");
}

void Suicide::Restore()
{
}
