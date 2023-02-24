#include "../pLib/pUi/pOverlay.hpp"
#include "../SDK/World.hpp"
#include "../SDK/NPC.hpp"
#include "../pLib/pMemory/pProcess.hpp"
#include "../pLib/pHelper.hpp"

#include "Trigger.hpp"



Trigger::Trigger(std::shared_ptr<pOverlay> ui, std::shared_ptr<pProcess> process, std::shared_ptr<World> world, std::shared_ptr<Settings> settings)
{
	this->ui = ui;
	this->process = process;
	this->world = world;
	this->settings = settings;

	name_ = "Trigger";
	thread_intervals_ = 1;
	active = &settings->trigger;
}

void Trigger::Execute()
{
	if (!settings->trigger)
		return;

	static bool can_shoot = true;
	static bool already_shooting = false;
	static NPC  entity;

	entity.Update(process->read<uintptr_t>(settings->pointers.entity_aiming_at));
	if (entity.base() == 0x0)
		can_shoot = false;
	else
		can_shoot = true;

	if (!process->read<uint32_t>(settings->pointers.is_player_aiming))
		can_shoot = false;


	if (can_shoot && !already_shooting && entity.health() > 100)
	{
		if (entity.is_player())
		{
			Key::Down::LMouse();
			already_shooting = true;
		}
		else
			entity.health(0.f);
	}
	else if (!can_shoot && already_shooting)
	{
		Key::Up::LMouse();
		already_shooting = false;
	}
}

void Trigger::Restore()
{
}