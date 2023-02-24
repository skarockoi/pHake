#include "../pLib/pUi/pOverlay.hpp"
#include "../SDK/World.hpp"

#include "RPLoop.hpp"

RPLoop::RPLoop(std::shared_ptr<pOverlay> ui, std::shared_ptr<World> world, std::shared_ptr<Settings> settings)
{
	this->ui = ui;
	this->world = world;

	name_ = "RPLoop";
	thread_intervals_ = 1;
	active = &settings->rploop;
}

void RPLoop::Execute()
{
	if (!*active)
		return;

	world->localplayer.playerinfo.wanted_level(5);
	world->localplayer.playerinfo.wanted_level(0);
}

void RPLoop::Restore()
{
}
