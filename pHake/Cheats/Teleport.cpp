#include "../globals.hpp"
#include "../pHake.hpp"

#include "Teleport.hpp"

#include "../UI/pHelper.hpp"



Teleport::Teleport(std::shared_ptr<pHake> phake) : Cheat(phake)
{
	name_ = "Tp to Waypoint";
}

void Teleport::Execute()
{
	vec3 waypoint = phake->process->read<vec3>(pointers.waypoint);

	if (waypoint.x == 64000 && waypoint.y == 64000) {
		phake->menu->notification.Add("No Waypoint set");
		return;
	}

	if (world.localplayer.in_vehicle())
	{
		if (IsVehicleMoving())
		{
			phake->menu->notification.Add("Don't move");
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
		phake->menu->notification.Add("Don't move");
		return;
	}

	waypoint.z = -210.f;
	world.localplayer.position.xyz(waypoint);
	Move();

	goto success;

success:
	phake->menu->notification.Add("Teleported to Waypoint");
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