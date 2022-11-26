#include "../Globals.hpp"

#include "Teleport.hpp"

#include "../UI/pHelper.hpp"

Teleport::Teleport()
{
	this->thread_intervals_ = 0;
}

void Teleport::Execute()
{
	vec3 waypoint = proc.read<vec3>(pointers.waypoint);

	if (waypoint.x == 64000 && waypoint.y == 64000) {
		menu->notification.Add("No Waypoint set");
		return;
	}

	if (world.localplayer.in_vehicle())
	{
		if (IsVehicleMoving())
		{
			menu->notification.Add("Don't move");
			return;
		}

		waypoint.z = -210.f;
		world.localplayer.vehicle.position.xyz(waypoint);
		Move();

		goto success;
	}

	if (settings.noclip)
	{
		waypoint.z = 300.f;
		world.localplayer.position.xyz(waypoint);
		Move();

		goto success;
	}

	if (IsPlayerMoving())
	{
		menu->notification.Add("Don't move");
		return;
	}

	waypoint.z = -210.f;
	world.localplayer.position.xyz(waypoint);
	Move();

	goto success;

success:
	menu->notification.Add("Teleported to Waypoint");
	return;
}

void Teleport::Restore()
{
}

bool Teleport::IsPlayerMoving()
{
	if (world.localplayer.speed_xyz().len() > 0.1)
		return true;
	return false;
}

bool Teleport::IsVehicleMoving()
{
	if (world.localplayer.vehicle.speed_xyz().len() > 0.1)
		return true;
	return false;
}

void Teleport::Move()
{
	Key::Down::W();
	sleep(50);
	Key::Up::W();
}