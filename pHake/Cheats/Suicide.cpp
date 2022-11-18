#include "../Globals.hpp"

#include "Suicide.hpp"

Suicide::Suicide()
{
	this->thread_intervals = 0;
}

void Suicide::execute()
{
	world.localplayer.health(0.f);
	menu->notification.Add("Player health set to 0");
}

void Suicide::restore()
{
}
