#include "Misc.hpp"

#include "../Globals.hpp"

#include "../UI/pHelper.hpp"
#include "../SDK/NPC.hpp"

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

void RPLoop()
{
	if (!settings.rploop)
		return;

	world.localplayer.playerinfo.wanted_level(5);
	world.localplayer.playerinfo.wanted_level(0);
}


static std::array<std::string, 4> vehicle_modes = { "default", "race", "max", "fly" };
static uint8_t curr_vehicle_mode = 0;

static Vehicle vehicle_defaults;

void BoostVehicle()
{
	if (vehicle_defaults.base() ^ world.localplayer.vehicle.base())
	{
		vehicle_defaults = world.localplayer.vehicle;
		curr_vehicle_mode = 0;
	}

	curr_vehicle_mode++;
	if (curr_vehicle_mode > vehicle_modes.size() - 1)
		curr_vehicle_mode = 0;

	switch (curr_vehicle_mode)
	{
	case 0:
		world.localplayer.vehicle.gravity(vehicle_defaults.gravity());
		world.localplayer.vehicle.handling.traction_max(vehicle_defaults.handling.traction_max());
		world.localplayer.vehicle.handling.traction_min(vehicle_defaults.handling.traction_min());
		world.localplayer.vehicle.handling.acceleration(vehicle_defaults.handling.acceleration());
		world.localplayer.vehicle.handling.collisiondamage(vehicle_defaults.handling.collisiondamage());
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
	menu->notification.Add("Vehicle set to " + vehicle_modes[curr_vehicle_mode]);
}

void RestoreVehicles()
{
	if (curr_vehicle_mode != 0)
	{
		world.localplayer.vehicle.gravity(vehicle_defaults.gravity());
		world.localplayer.vehicle.handling.traction_max(vehicle_defaults.handling.traction_max());
		world.localplayer.vehicle.handling.traction_min(vehicle_defaults.handling.traction_min());
		world.localplayer.vehicle.handling.acceleration(vehicle_defaults.handling.acceleration());
		world.localplayer.vehicle.handling.collisiondamage(vehicle_defaults.handling.collisiondamage());
	}
}


static std::array<std::string, 3> player_modes = { "default", "fast", "max" };
static uint8_t curr_player_mode = 0;

void BoostPlayer()
{
	curr_player_mode++;
	if (curr_player_mode > player_modes.size() - 1)
		curr_player_mode = 0;

	switch (curr_player_mode)
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
	menu->notification.Add("Player set to " + player_modes[curr_player_mode]);
}

void RestorePlayer()
{
	if (curr_player_mode != 0)
	{
		world.localplayer.playerinfo.walk_mp(1);
		world.localplayer.playerinfo.swim_mp(1);
		settings.noclip_speed = 0.05f;

		if (!settings.noclip)
			world.localplayer.ragdoll(0);
	}
}

void Suicide()
{
	world.localplayer.health(0.f);
	menu->notification.Add("Player health set to 0");
}