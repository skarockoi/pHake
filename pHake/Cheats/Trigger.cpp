#include "../Globals.hpp"

#include "Trigger.hpp"

#include "../SDK/NPC.hpp"
#include "../UI/pHelper.hpp"


Trigger::Trigger()
{
	thread_intervals_ = 1;
	menu->list.AddBool("Trigger", settings.trigger);
}

void Trigger::Execute()
{
	if (!settings.trigger)
		return;

	static bool can_shoot = true;
	static bool already_shooting = false;
	static NPC  entity;

	entity.Update(proc.read<uintptr_t>(pointers.entity_aiming_at));
	if (entity.base() == 0x0)
		can_shoot = false;
	else
		can_shoot = true;

	if (!proc.read<uint32_t>(pointers.is_player_aiming))
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