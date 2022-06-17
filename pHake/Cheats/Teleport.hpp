#ifndef _TELEPORT_HPP_
#define _TELEPORT_HPP_

#include "../Globals.hpp"

#include "../UI/pHelper.hpp"

namespace {
	bool IsPlayerMoving()
	{
		if (world.localplayer.speed_xyz().len() > 0.1)
			return true;
		return false;
	}

	bool IsVehicleMoving()
	{
		if (world.localplayer.vehicle.speed_xyz().len() > 0.1)
			return true;
		return false;

	}

	static void Move()
	{
		Key::Down::W();
		sleep(50);
		Key::Up::W();
	}
}
void TeleportToWaypoint()
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
#endif