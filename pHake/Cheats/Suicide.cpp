#include "../globals.hpp"
#include "../pLib/pHake.hpp"

#include "Suicide.hpp"



Suicide::Suicide(std::shared_ptr<pHake> phake) : pCheat(phake)
{
	name_ = "Suicide";
}

void Suicide::Execute()
{
	world.localplayer.health(0.f);
	phake->menu->notification.Add("Player health set to 0");
}

void Suicide::Restore()
{
}
