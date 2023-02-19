#include "../globals.hpp"

#include "Suicide.hpp"

using namespace globals;

Suicide::Suicide() : pCheat()
{
	name_ = "Suicide";
}

void Suicide::Execute()
{
	world.localplayer.health(0.f);
	menu->notification.Add("Player health set to 0");
}

void Suicide::Restore()
{
}
