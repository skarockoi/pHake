#include "../pLib/pUi/pOverlay.hpp"
#include "../SDK/World.hpp"

#include "Suicide.hpp"


Suicide::Suicide(std::shared_ptr<pOverlay> ui, std::shared_ptr<World> world)
{
	this->ui = ui;
	this->world = world;

	name_ = "Suicide";
}

void Suicide::Execute()
{
	world->localplayer.health(0.f);
	ui->notification.Add("Player health set to 0");
}

void Suicide::Restore()
{
}
