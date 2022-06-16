#include "Misc.hpp"

#include "../Globals.hpp"

#include "../UI/pHelper.hpp"
#include "../SDK/Entity.hpp"

#include <array>

void NoWanted()
{
	if (!settings.nowanted)
		return;

	if (world.localplayer.playerinfo.wanted_level() != 0)
		world.localplayer.playerinfo.wanted_level(0);
}

void GodMode()
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

void Trigger()
{
	if (!settings.trigger)
		return;

	static Entity entity;
	static bool can_shoot = true;
	static bool already_shooting = false;

	int32_t id_value = proc.read<int32_t>(pointers.crosshair_value);
	if (id_value > 0 && id_value < 3) // 0 = Nothing, 1 = Hostile, 2 = Friendly, 3 = Dead/Invincible
		can_shoot = true;
	else
		can_shoot = false;


	if (can_shoot && !already_shooting)
	{
		entity.Update(proc.read<uintptr_t>(pointers.entity_aiming_at));
		entity.health(0.f);

		Key::Down::LMouse();
		already_shooting = true;
	}
	else if (!can_shoot && already_shooting)
	{
		Key::Up::LMouse();
		already_shooting = false;
	}
}

void RPLoop()
{
	if (!settings.rploop)
		return;

	world.localplayer.playerinfo.wanted_level(5);
	world.localplayer.playerinfo.wanted_level(0);
}

void BoostVehicle()
{
	static std::array<std::string, 4> modes = { "default", "race", "max", "fly" };
	static uint8_t curr_mode = 0;

	curr_mode++;
	if (curr_mode > modes.size() - 1)
		curr_mode = 0;

	switch (curr_mode)
	{
	case 0:
		world.localplayer.vehicle.gravity(9.8f);
		world.localplayer.vehicle.handling.traction_max(2.f);
		world.localplayer.vehicle.handling.traction_min(2.f);
		world.localplayer.vehicle.handling.acceleration(1.f);
		world.localplayer.vehicle.handling.collisiondamage(0.f);
		break;
	case 1:
		world.localplayer.vehicle.gravity(20.f);
		world.localplayer.vehicle.handling.traction_max(3.f);
		world.localplayer.vehicle.handling.traction_min(3.f);
		world.localplayer.vehicle.handling.collisiondamage(0.f);
		world.localplayer.vehicle.handling.acceleration(3.f);
		break;
	case 2:
		world.localplayer.vehicle.gravity(25.f);
		world.localplayer.vehicle.handling.traction_max(5.f);
		world.localplayer.vehicle.handling.traction_min(5.f);
		world.localplayer.vehicle.handling.collisiondamage(0.f);
		world.localplayer.vehicle.handling.acceleration(20.f);
		break;
	case 3:
		world.localplayer.vehicle.gravity(-10.f);
		world.localplayer.vehicle.handling.traction_max(2.f);
		world.localplayer.vehicle.handling.traction_min(2.f);
		world.localplayer.vehicle.handling.collisiondamage(0.f);
		world.localplayer.vehicle.handling.acceleration(2.f);
		break;
	}
	menu->notification.Add("Vehicle set to " + modes[curr_mode]);
}

void BoostPlayer()
{
	static std::array<std::string, 3> modes = { "default", "fast", "max" };
	static uint8_t curr_mode = 0;

	curr_mode++;
	if (curr_mode > modes.size() - 1)
		curr_mode = 0;

	switch (curr_mode)
	{
	case 0:
		world.localplayer.playerinfo.walk_mp(1);
		world.localplayer.playerinfo.swim_mp(1);
		settings.noclip_speed = 0.05f;

		if (!settings.noclip)
			world.localplayer.ragdoll(0);
		break;
	case 1:
		world.localplayer.playerinfo.walk_mp(2);
		world.localplayer.playerinfo.swim_mp(2);
		world.localplayer.ragdoll(1);
		settings.noclip_speed = 0.2f;
		break;
	case 2:
		world.localplayer.playerinfo.walk_mp(2500);
		world.localplayer.playerinfo.swim_mp(5);
		world.localplayer.ragdoll(1);
		settings.noclip_speed = 0.5f;
		break;
	}
	menu->notification.Add("Player set to " + modes[curr_mode]);
}

void Suicide()
{
	world.localplayer.health(0.f);
	menu->notification.Add("Player health set to 0");
}